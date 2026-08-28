// CopyRight © Dead Air Game. All Rights Reserved.


#include "Player/DA_Character.h"

#include "AbilitySystemComponent.h"
#include "DA_MiscUtils.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AbilitySystem/DA_AbilitySet.h"
#include "AbilitySystem/DA_AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Input/DA_InputComponent.h"
#include "Inventory/DA_InventoryComponent.h"
#include "DA_GameplayTags.h"

// Sets default values
ADA_Character::ADA_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetMesh());

	Hand = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hand"));
	Hand->SetupAttachment(Camera);
	
	InventoryComponent = CreateDefaultSubobject<UDA_InventoryComponent>(TEXT("Inventory"));
	AbilitySystemComponent = CreateDefaultSubobject<UDA_AbilitySystemComponent>(TEXT("AbilitySystem"));
}

void ADA_Character::XAddInventoryItem(const FString& ItemName)
{
	InventoryComponent->AddNewItemByName(ItemName);
}

void ADA_Character::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	InventoryComponent->Initialize();
}

UAbilitySystemComponent* ADA_Character::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent.Get();
}

// Called when the game starts or when spawned
void ADA_Character::BeginPlay()
{
	Super::BeginPlay();

	AbilitySystemComponent->InitAbilityActorInfo(GetLocalViewingPlayerController(), this); //@TODO: Character?

	ENSURE_KISMET(AbilitySet)
	AbilitySet->GiveToAbilitySystem(AbilitySystemComponent.Get(), nullptr);
}

void ADA_Character::Input_AbilityInputTagPressed(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagPressed(InputTag);
}

void ADA_Character::Input_AbilityInputTagReleased(FGameplayTag InputTag)
{
	AbilitySystemComponent->AbilityInputTagReleased(InputTag);
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
	
	const APlayerController* PlayerController = GetController<APlayerController>();
	check(PlayerController);

	const ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(PlayerController->GetLocalPlayer());
	check(LocalPlayer);
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->ClearAllMappings();
	
	UDA_InputComponent* DeadAirInputComponent = Cast<UDA_InputComponent>(PlayerInputComponent);
	if (ensureMsgf(DeadAirInputComponent, TEXT("Unexpected Input Component class! The Gameplay Abilities will not be bound to their inputs. Change the input component to UDA_InputComponent or a subclass of it.")))
	{
		ENSURE_KISMET(InputConfig)
		
		// Add the key mappings that may have been set by the player
		DeadAirInputComponent->AddInputMappings(InputConfig, Subsystem);

		// This is where we actually bind and input action to a gameplay tag, which means that Gameplay Ability Blueprints will
		// be triggered directly by these input actions Triggered events. 
		TArray<uint32> BindHandles;
		DeadAirInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::Input_AbilityInputTagPressed, &ThisClass::Input_AbilityInputTagReleased, /*out*/ BindHandles);

		DeadAirInputComponent->BindNativeAction(InputConfig, DeadAirGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move, false);
		DeadAirInputComponent->BindNativeAction(InputConfig, DeadAirGameplayTags::InputTag_Look_Mouse, ETriggerEvent::Triggered, this, &ThisClass::Input_LookMouse, false);
		DeadAirInputComponent->BindNativeAction(InputConfig, DeadAirGameplayTags::InputTag_Look_Stick, ETriggerEvent::Triggered, this, &ThisClass::Input_LookStick, false);

		DeadAirInputComponent->BindNativeAction(InputConfig, DeadAirGameplayTags::InputTag_Jump, ETriggerEvent::Started, this, &Super::Jump, false);
		DeadAirInputComponent->BindNativeAction(InputConfig, DeadAirGameplayTags::InputTag_Jump, ETriggerEvent::Completed, this, &Super::StopJumping, false);
	}
}

void ADA_Character::Input_Move(const FInputActionValue& InputValue)
{
	const FVector2D MoveInput = InputValue.Get<FVector2D>();
	if (GetController())
	{
		if (MoveInput.X != 0.0f)
		{
			AddMovementInput(GetActorRightVector(), MoveInput.X, false);
		}
		
		if (MoveInput.Y != 0.0f)
		{
			AddMovementInput(GetActorForwardVector(), MoveInput.Y, false);
		}
	}
}

void ADA_Character::Input_LookMouse(const FInputActionValue& InputValue)
{
	const FVector2D LookInput = InputValue.Get<FVector2D>();
	constexpr float LookSensitivity = 0.25f;
	
	if (LookInput.X != 0.0f)
	{
		AddControllerYawInput(LookInput.X * LookSensitivity);
	}

	if (LookInput.Y != 0.0f)
	{
		AddControllerPitchInput(LookInput.Y * LookSensitivity);
	}
}

void ADA_Character::Input_LookStick(const FInputActionValue& InputValue)
{
	const FVector2D LookInput = InputValue.Get<FVector2D>();
	constexpr float LookSensitivity = 0.8f;
	
	const UWorld* World = GetWorld();
	check(World);
		
	if (LookInput.X != 0.0f)
	{
		AddControllerYawInput(LookInput.X * LookSensitivity * (World->GetDeltaSeconds() * 100.f));
	}

	if (LookInput.Y != 0.0f)
	{
		AddControllerPitchInput(LookInput.Y * LookSensitivity * (World->GetDeltaSeconds() * 100.f));
	}
}

