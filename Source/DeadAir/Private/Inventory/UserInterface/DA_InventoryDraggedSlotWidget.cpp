// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/UserInterface/DA_InventoryDraggedSlotWidget.h"

#include "Inventory/DA_InventoryComponent.h"
#include "Inventory/DA_InventoryItem.h"

void UDA_InventoryDraggedSlotWidget::SetData(const FDA_InventorySlot NewData, const float InCellSize)
{
	// CopyItem = DuplicateObject(NewData.Item, NewData.Item->GetOuter());
	// CopyItem->OnConstruct();
	SlotData = NewData;
	CellSize = InCellSize;

	OnDataReceived();
	SetSlotSize(CellSize);

	if (!SlotData.Item->OnItemRotated.IsBoundToObject(this))
	{
		SlotData.Item->OnItemRotated.AddUObject(this, &ThisClass::OnItemRotated);
	}
}

