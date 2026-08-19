// CopyRight © Dead Air Game. All Rights Reserved.


#include "Core/DA_PlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "MiscUtils.h"
#include "Core/DA_Character.h"
#include "Inventory/DA_InventoryComponent.h"
#include "Inventory/DA_InventoryItem.h"
#include "UserInterface/Inventory/DA_InventoryWidget.h"

DEFINE_LOG_CATEGORY_STATIC(X_PlayerController, Log, All)

void ADA_PlayerController::XPrintInventory()
{
	if (ensure(InventoryComponent != nullptr))
	{
		InventoryComponent->PrintInventoryContent();
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
	
	// Create inventory widget
	{
		ENSURE_KISMET(InventoryWidgetClass)
		
		InventoryWidget = CreateWidget<UDA_InventoryWidget>(this, InventoryWidgetClass);
		if (InventoryWidget)
		{
			InventoryComponent = GetPawn<ADA_Character>()->GetComponentByClass<UDA_InventoryComponent>();
			
			InventoryWidget->SetInventory(InventoryComponent.Get());
			InventoryWidget->AddToViewport();
			
			SetUIMode(true);
		}
	}
}

void ADA_PlayerController::SetUIMode(bool bUIMode)
{
	bShowMouseCursor = bUIMode;

	ResetIgnoreLookInput();
	ResetIgnoreMoveInput();

	if (bUIMode)
	{
		SetInputMode(FInputModeGameAndUI());
		UE_LOG(X_PlayerController, Log, TEXT("Input mode set to GameAndUI"))
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
		UE_LOG(X_PlayerController, Log, TEXT("Input mode set to GameOnly"))
	}
}

