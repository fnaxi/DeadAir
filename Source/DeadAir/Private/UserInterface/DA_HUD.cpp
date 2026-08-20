// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/DA_HUD.h"

#include "MiscUtils.h"
#include "UserInterface/DA_GameWidget.h"
#include "UserInterface/Inventory/DA_InventoryWidget.h"

void ADA_HUD::BeginPlay()
{
	Super::BeginPlay();

	ENSURE_KISMET(GameWidgetClass)
	
	GameWidget = CreateWidget<UDA_GameWidget>(GetOwningPlayerController(), GameWidgetClass);
	if (GameWidget)
	{
		GameWidget->AddToViewport();
	}
}

