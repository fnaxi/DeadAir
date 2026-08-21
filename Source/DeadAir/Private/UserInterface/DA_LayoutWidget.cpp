// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/DA_LayoutWidget.h"

#include "MiscUtils.h"
#include "UserInterface/Inventory/DA_InventoryWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"

void UDA_LayoutWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ENSURE_KISMET(InventoryWidgetClass)
	if (UCommonActivatableWidget* InventoryWidget = GameLayer_Stack->AddWidget(InventoryWidgetClass))
	{
		InventoryWidget->AddToViewport();
		InventoryWidget->ActivateWidget();
	}
}

