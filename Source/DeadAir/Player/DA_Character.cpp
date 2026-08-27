// CopyRight © Dead Air Game. All Rights Reserved.


#include "Player/DA_Character.h"

#include "AbilitySystemComponent.h"
#include "DA_LogChannels.h"
#include "DA_MiscUtils.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "AbilitySystem/DA_AbilitySet.h"
#include "AbilitySystem/DA_AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/AssetManager.h"
#include "Inventory/DA_InventoryComponent.h"
#include "Inventory/DA_InventoryItemDefinition.h"

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
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	const IAssetRegistry& AssetRegistry = AssetRegistryModule.Get();

	FARFilter Filter;
	Filter.ClassPaths.Add(UDA_InventoryItemDefinition::StaticClass()->GetClassPathName());
	Filter.bRecursiveClasses = true;

	TArray<FAssetData> FoundAssets;
	AssetRegistry.GetAssets(Filter, FoundAssets);

	UDA_InventoryItemDefinition* ItemDefinition = nullptr;
	for (const FAssetData& AssetData : FoundAssets)
	{
		if (AssetData.AssetName.ToString() == ItemName)
		{
			ItemDefinition = Cast<UDA_InventoryItemDefinition>(AssetData.GetAsset());
			break;
		}
	}

	if (!IsValid(ItemDefinition))
	{
		UE_LOG(X_Inventory, Warning, TEXT("%s: Can't find item definition with name: %s!"), *GetName(), *ItemName);
		return;
	}

	InventoryComponent->AddNewItem(ItemDefinition);
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
		
		EnhancedInput->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ThisClass::LookWithMouse);
		EnhancedInput->BindAction(StickLookAction, ETriggerEvent::Triggered, this, &ThisClass::LookWithStick);

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

void ADA_Character::LookWithMouse(const FInputActionValue& InputValue)
{
	const FVector2D LookInput = InputValue.Get<FVector2D>();
	if (GetController())
	{
		AddControllerPitchInput(LookInput.Y * 0.25);
		AddControllerYawInput(LookInput.X * 0.25);
	}
}

void ADA_Character::LookWithStick(const FInputActionValue& InputValue)
{
	const FVector2D LookInput = InputValue.Get<FVector2D>();
	if (GetController())
	{
		AddControllerPitchInput(LookInput.Y * 0.8f);
		AddControllerYawInput(LookInput.X * 0.8f);
	}
}

