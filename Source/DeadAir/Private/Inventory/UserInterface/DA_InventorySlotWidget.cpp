// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/UserInterface/DA_InventorySlotWidget.h"

#include "Inventory/UserInterface/DA_InventoryCellWidget.h"

void UDA_InventorySlotWidget::SetData(const FDA_InventorySlot& NewData, UDA_InventoryGridWidget* NewParentWidget)
{
	SlotData = NewData;
	ParentWidget = NewParentWidget;
	OnDataReceived();
}

void UDA_InventorySlotWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
}

void UDA_InventorySlotWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
}

void UDA_InventorySlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

bool UDA_InventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool bDroppedSomething = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	bDroppedSomething |= true;

	return bDroppedSomething;
}
