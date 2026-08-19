// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryDraggedSlotWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/SizeBox.h"
#include "Inventory/DA_InventoryComponent.h"
#include "Inventory/DA_InventoryItem.h"

void UDA_InventoryDraggedSlotWidget::SetData(const FDA_InventorySlot& InData, const float InCellSize)
{
	// CopyItem = DuplicateObject(NewData.Item, NewData.Item->GetOuter());
	// CopyItem->OnConstruct();
	SlotData = InData;
	CellSize = InCellSize;

	SetSlotSize(CellSize);

	// todo: Fix crash here or remove. we don't need rotation anyway
	/*if (!SlotData.Item->OnItemRotated.IsBoundToObject(this))
	{
		SlotData.Item->OnItemRotated.AddUObject(this, &ThisClass::OnItemRotated);
	}*/
}

void UDA_InventoryDraggedSlotWidget::SetSlotSize(const float Size) const
{
	const FVector2D NewSize = FVector2D(SlotData.Item->Size.X * Size, SlotData.Item->Size.Y * Size);

	Box->SetWidthOverride(NewSize.X);
	Box->SetHeightOverride(NewSize.Y);
}

void UDA_InventoryDraggedSlotWidget::OnItemRotated()
{
	if (SlotData.Item->CanRotate())
	{
		SlotData.Item->Rotate();

		const FVector2D OldSize = FVector2D(Box->GetWidthOverride(), Box->GetHeightOverride());
		
		Box->SetWidthOverride(OldSize.Y);
		Box->SetHeightOverride(OldSize.X);
	}
}

