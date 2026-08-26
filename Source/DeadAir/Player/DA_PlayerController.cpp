// CopyRight © Dead Air Game. All Rights Reserved.


#include "Player/DA_PlayerController.h"

#include "CommonUIExtensions.h"
#include "UserInterface/Inventory/DA_InventoryWidget.h"
#include "DA_GameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "DA_MiscUtils.h"
#include "EnhancedInputComponent.h"

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
		EnhancedInput->BindAction(InventoryAction, ETriggerEvent::Started, this, &ADA_PlayerController::ToggleInventory);
	}
}

void ADA_PlayerController::ToggleInventory()
{
	if (InventoryWidget.IsValid())
	{
		UCommonUIExtensions::PopContentFromLayer(InventoryWidget.Get());
		InventoryWidget.Reset();
	}
	else
	{
		ENSURE_KISMET(InventoryWidgetClass)
		InventoryWidget = UCommonUIExtensions::PushContentToLayer_ForPlayer(GetLocalPlayer(), DeadAirGameplayTags::Layer_GameMenu, InventoryWidgetClass);
	}
}

