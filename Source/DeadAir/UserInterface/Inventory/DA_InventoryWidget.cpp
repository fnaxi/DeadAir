// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryWidget.h"

#include "DA_InventoryGridWidget.h"
#include "DA_MiscUtils.h"
#include "Input/CommonUIInputTypes.h"

void UDA_InventoryWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	ENSURE_KISMET(!CloseInventoryInputAction.IsNull());
	RegisterUIActionBinding(FBindUIActionArgs(CloseInventoryInputAction, true, FSimpleDelegate::CreateUObject(this, &ThisClass::CloseInventory)));
}

void UDA_InventoryWidget::CloseInventory()
{
	DeactivateWidget();
}

