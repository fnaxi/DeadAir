// CopyRight © Dead Air Game. All Rights Reserved.


#include "Player/DA_PlayerController.h"

#include "CommonUIExtensions.h"
#include "UserInterface/Inventory/DA_InventoryWidget.h"
#include "DA_GameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "DA_MiscUtils.h"

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

	ENSURE_KISMET(InventoryWidgetClass)
	UCommonUIExtensions::PushContentToLayer_ForPlayer(GetLocalPlayer(), DeadAirGameplayTags::Layer_GameMenu, InventoryWidgetClass);

	SetUIMode(true);
}

void ADA_PlayerController::SetUIMode(bool bUIMode)
{
	bShowMouseCursor = bUIMode;

	ResetIgnoreLookInput();
	ResetIgnoreMoveInput();

	if (bUIMode)
	{
		SetInputMode(FInputModeGameAndUI());
		UE_LOG(LogPlayerController, Log, TEXT("Input mode set to GameAndUI"))
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
		UE_LOG(LogPlayerController, Log, TEXT("Input mode set to GameOnly"))
	}
}

