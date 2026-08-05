// CopyRight © Dead Air Game. All Rights Reserved.


#include "Core/DA_PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "MiscUtils.h"
#include "Core/DA_Character.h"
#include "Inventory/DA_InventoryComponent.h"
#include "UserInterface/Inventory/DA_InventoryWidget.h"
#include "UserInterface/Inventory/DA_InventoryGridWidget.h"

void ADA_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	// Setup input
	if (IsLocalPlayerController())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(MappingContext, 0);
		}
	}
	
	// Initialize inventory system
	DA_ENSURE_ASSET(InventoryWidgetClass)
	{
		InventoryWidget = CreateWidget<UDA_InventoryWidget>(this, InventoryWidgetClass);
		if (InventoryWidget)
		{
			InventoryWidget->AddToViewport();
			SetUIMode(true);
			
			if (InventoryWidget->Grid)
			{
				InventoryWidget->Grid->SetData(GetInventoryComponent()); // TODO(DA): SetOwningInventory()???
			}
		}
	}
}

UDA_InventoryComponent* ADA_PlayerController::GetInventoryComponent() const
{
	return GetPawn<ADA_Character>()->GetComponentByClass<UDA_InventoryComponent>();
}

void ADA_PlayerController::SetUIMode(bool bUIMode)
{
	bShowMouseCursor = bUIMode;

	ResetIgnoreLookInput();
	SetIgnoreLookInput(bUIMode);
	SetIgnoreMoveInput(bUIMode);

	if (bUIMode)
	{
		SetInputMode(FInputModeGameAndUI());
	}
	else
	{
		SetInputMode(FInputModeGameOnly());	
	}
}

