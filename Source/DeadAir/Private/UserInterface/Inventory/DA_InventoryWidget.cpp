// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryWidget.h"

#include "UserInterface/Inventory/DA_InventoryGridWidget.h"

void UDA_InventoryWidget::SetInventory(UDA_InventoryComponent* Inventory) const
{
	Grid->SetData(Inventory);
}

