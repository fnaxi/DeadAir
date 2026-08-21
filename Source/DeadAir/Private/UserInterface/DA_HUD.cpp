// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/DA_HUD.h"

#include "MiscUtils.h"
#include "UserInterface/DA_LayoutWidget.h"
#include "UserInterface/Inventory/DA_InventoryWidget.h"

void ADA_HUD::BeginPlay()
{
	Super::BeginPlay();

	ENSURE_KISMET(LayoutWidgetClass)
	
	LayoutWidget = CreateWidget<UDA_LayoutWidget>(GetOwningPlayerController(), LayoutWidgetClass);
	if (LayoutWidget)
	{
		LayoutWidget->AddToViewport();
	}
}

