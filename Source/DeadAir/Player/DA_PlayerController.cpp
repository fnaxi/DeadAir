// CopyRight © Dead Air Game. All Rights Reserved.


#include "Player/DA_PlayerController.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputSubsystems.h"
#include "DA_MiscUtils.h"
#include "EnhancedInputComponent.h"
#include "Player/DA_Character.h"
#include "AbilitySystem/Abilities/DA_GameplayAbility_OpenInventory.h"

void ADA_PlayerController::OpenInventory()
{
	const ADA_Character* DeadAirCharacter = CastChecked<ADA_Character>(GetPawn());

	//@TODO: Activate abilities with gameplay tag
	if (UAbilitySystemComponent* AbilitySystem = DeadAirCharacter->GetAbilitySystemComponent())
	{
		AbilitySystem->TryActivateAbilityByClass(ToggleInventoryAbilityClass);
	}
}

void ADA_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Setup input
	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			ENSURE_KISMET(MappingContext)
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
}

void ADA_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInput->BindAction(InventoryAction, ETriggerEvent::Started, this, &ADA_PlayerController::OpenInventory);
	}
}

