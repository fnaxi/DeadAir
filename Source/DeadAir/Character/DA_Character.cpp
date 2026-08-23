// CopyRight © Dead Air Game. All Rights Reserved.


#include "Character/DA_Character.h"

#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Camera/CameraComponent.h"
#include "Inventory/DA_InventoryComponent.h"

// Sets default values
ADA_Character::ADA_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh());

	Hand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hand"));
	Hand->SetupAttachment(Camera);
	
	Inventory = CreateDefaultSubobject<UDA_InventoryComponent>(TEXT("InventoryComponent"));
}

void ADA_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (ensure(Inventory != nullptr))
	{
		Inventory->Initialize();
	}
}

// Called when the game starts or when spawned
void ADA_Character::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADA_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADA_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);

		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &Super::Jump);
		EnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &Super::StopJumping);
	}
}

void ADA_Character::Move(const FInputActionValue& InputValue)
{
	const FVector2D MoveInput = InputValue.Get<FVector2D>();
	if (GetController())
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.Y, false);
		AddMovementInput(GetActorRightVector(), MoveInput.X, false);
	}
}

void ADA_Character::Look(const FInputActionValue& InputValue)
{
	const FVector2D LookInput = InputValue.Get<FVector2D>();
	if (GetController())
	{
		AddControllerPitchInput(LookInput.Y * 0.25);
		AddControllerYawInput(LookInput.X * 0.25);
	}
}

