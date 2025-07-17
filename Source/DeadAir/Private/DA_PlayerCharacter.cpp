// CopyRight Dead Air Game. All Rights Reserved.


#include "DA_PlayerCharacter.h"

#include "DA_CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/CapsuleComponent.h"
#include "Inventory/DA_InventoryComponent.h"

// Sets default values
ADA_PlayerCharacter::ADA_PlayerCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UDA_CharacterMovementComponent>(CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
#if !UE_BUILD_SHIPPING
	PrimaryActorTick.bCanEverTick = true;
#else
	PrimaryActorTick.bCanEverTick = false;
#endif

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());
	Camera->bUsePawnControlRotation = true;
	
	HUDHands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HUDHands"));
	HUDHands->SetupAttachment(Camera);
	HUDHands->CastShadow = false;

	HUDGun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	HUDGun->SetupAttachment(HUDHands);
	HUDGun->CastShadow = false;

	InventoryComponent = CreateDefaultSubobject<UDA_InventoryComponent>("InventoryComponent");
}

// Called when the game starts or when spawned
void ADA_PlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	check(MappingContext);
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	check(HUDHands);
	check(HUDGun);
	HUDGun->AttachToComponent(HUDHands, FAttachmentTransformRules::SnapToTargetNotIncludingScale, GunSocketName);
	HUDGun->HideBoneByName(ScopeBoneName, PBO_None);
	HUDGun->HideBoneByName(GrenadeLauncherBoneName, PBO_None);
	HUDGun->HideBoneByName(SilencerBoneName, PBO_None);
}

void ADA_PlayerCharacter::XNoClip(float InFlySpeed)
{
#if !UE_BUILD_SHIPPING
	bNoClip = !bNoClip;
	if (bNoClip)
	{
		GetCharacterMovement()->SetMovementMode(MOVE_None);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->MaxFlySpeed = FMath::Clamp(InFlySpeed, 0.0f, 10000.0f);
	}
	else
	{
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
#endif
}

// Called every frame
void ADA_PlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if !UE_BUILD_SHIPPING
	if (bNoClip && IsValid(GetController()))
	{
		const FRotator CamRot = GetControlRotation();
		const FVector Forward = FRotationMatrix(CamRot).GetScaledAxis(EAxis::X);
		const FVector Right = FRotationMatrix(CamRot).GetScaledAxis(EAxis::Y);

		FVector Direction = Forward * FlyMoveInput.Y + Right * FlyMoveInput.X;
		if (bFlyMoveUp)   Direction += FVector::UpVector;
		if (bFlyMoveDown) Direction += FVector::DownVector;

		if (!Direction.IsNearlyZero())
		{
			const float FlySpeed = GetCharacterMovement()->MaxFlySpeed * (bWantsToSprint ? 2.25f : 1.0f);
			AddActorWorldOffset(Direction.GetSafeNormal() * FlySpeed * DeltaTime, true);
		}
	}
#endif
}

// Called to bind functionality to input
void ADA_PlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ADA_PlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ADA_PlayerCharacter::Look);
		
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		
		EnhancedInputComponent->BindAction(CrouchInputAction, ETriggerEvent::Triggered, this, &ADA_PlayerCharacter::StartCrouch);
		EnhancedInputComponent->BindAction(CrouchInputAction, ETriggerEvent::Completed, this, &ADA_PlayerCharacter::StopCrouch);
		
		EnhancedInputComponent->BindAction(SprintInputAction, ETriggerEvent::Triggered, this, &ADA_PlayerCharacter::StartSprinting);
		EnhancedInputComponent->BindAction(SprintInputAction, ETriggerEvent::Completed, this, &ADA_PlayerCharacter::StopSprinting);

		// No clip mode
#if !UE_BUILD_SHIPPING
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Completed, this, &ADA_PlayerCharacter::StopMove);
		
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Triggered, this, &ADA_PlayerCharacter::StartFlyUp);
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &ADA_PlayerCharacter::StopFlyUp);

		EnhancedInputComponent->BindAction(CrouchInputAction, ETriggerEvent::Triggered, this, &ADA_PlayerCharacter::StartFlyDown);
		EnhancedInputComponent->BindAction(CrouchInputAction, ETriggerEvent::Completed, this, &ADA_PlayerCharacter::StopFlyDown);
#endif
	}
}

bool ADA_PlayerCharacter::IsSprinting() const
{
#if !UE_BUILD_SHIPPING
	const bool bCanSprint = bIsMovingForward && !GetVelocity().IsZero() && !bNoClip;
#else
	const bool bCanSprint = bIsMovingForward && !GetVelocity().IsZero();
#endif
	
	return bWantsToSprint && bCanSprint;
}

void ADA_PlayerCharacter::Move(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();
	if (IsValid(GetController()))
	{
		AddMovementInput(GetActorForwardVector(), InputVector.Y, false);
		bIsMovingForward = InputVector.Y > 0.0f;
		
		AddMovementInput(GetActorRightVector(), InputVector.X, false);
	}
#if !UE_BUILD_SHIPPING
	FlyMoveInput = InputVector;
#endif
}

#if !UE_BUILD_SHIPPING
void ADA_PlayerCharacter::StopMove(const FInputActionValue& InputValue)
{
	FlyMoveInput = FVector2D::ZeroVector;
}
#endif

void ADA_PlayerCharacter::Look(const FInputActionValue& InputValue)
{
	FVector2D InputVector = InputValue.Get<FVector2D>();
	if (IsValid(GetController()))
	{
		AddControllerPitchInput(InputVector.Y);
		AddControllerYawInput(InputVector.X);
	}
}

void ADA_PlayerCharacter::StartCrouch(const FInputActionValue& InputValue)
{
	ACharacter::Crouch();
}

void ADA_PlayerCharacter::StopCrouch(const FInputActionValue& InputValue)
{
	ACharacter::UnCrouch();
}

void ADA_PlayerCharacter::StartSprinting()
{
	bWantsToSprint = true;
	// TODO: stop firing
}

void ADA_PlayerCharacter::StopSprinting()
{
	bWantsToSprint = false;
}

