// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryDraggedSlotWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Inventory/DA_InventoryComponent.h"
#include "Inventory/DA_InventoryItem.h"

void UDA_InventoryDraggedSlotWidget::SetData(const FDA_InventorySlot NewData, const float InCellSize)
{
	// CopyItem = DuplicateObject(NewData.Item, NewData.Item->GetOuter());
	// CopyItem->OnConstruct();
	SlotData = NewData;
	CellSize = InCellSize;

	SetSlotSize(CellSize);

	if (!SlotData.Item->OnItemRotated.IsBoundToObject(this))
	{
		SlotData.Item->OnItemRotated.AddUObject(this, &ThisClass::OnItemRotated);
	}
}

void UDA_InventoryDraggedSlotWidget::SetSlotSize(float Size)
{
	const FVector2D NewSize = FVector2D(SlotData.Item->Size.X * Size, SlotData.Item->Size.Y * Size);

	if (UCanvasPanelSlot* Panel = UWidgetLayoutLibrary::SlotAsCanvasSlot(SlotCanvas))
	{
		Panel->SetSize(NewSize);
	}
}

void UDA_InventoryDraggedSlotWidget::OnItemRotated()
{
	if (SlotData.Item->CanRotate())
	{
		SlotData.Item->Rotate();
		
		if (UCanvasPanelSlot* Panel = UWidgetLayoutLibrary::SlotAsCanvasSlot(SlotCanvas))
		{
			Panel->SetSize( FVector2D(Panel->GetSize().Y, Panel->GetSize().X) );
		}
	}
}

