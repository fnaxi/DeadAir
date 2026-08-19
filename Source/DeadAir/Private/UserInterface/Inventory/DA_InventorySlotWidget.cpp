// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventorySlotWidget.h"

#include "MiscUtils.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/GridSlot.h"
#include "Components/SizeBox.h"
#include "Inventory/DA_InventoryItem.h"
#include "UserInterface/Inventory/DA_InventoryDraggedSlotWidget.h"
#include "UserInterface/Inventory/DA_InventoryGridWidget.h"
#include "UserInterface/Inventory/DA_InventorySlot_DragDropOperation.h"

void UDA_InventorySlotWidget::SetData(const FDA_InventorySlot& InSlotData, UDA_InventoryGridWidget* InGrid, const float InSize)
{
	check(InGrid != nullptr);
	
	SlotData = InSlotData;
	Grid = InGrid;

	SetSlotSize(InSize);
}

void UDA_InventorySlotWidget::SetSlotSize(const float Size) const
{
	const FIntPoint ItemSize = SlotData.Item->Size;
	
	Box->SetWidthOverride(ItemSize.X * Size);
	Box->SetHeightOverride(ItemSize.Y * Size);
}

void UDA_InventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UE_LOG(X_Inventory, Verbose, TEXT("%s: Drag&Drop was detected for %s item"), *SlotData.Item->GetOwnerInventory()->GetOwner()->GetName(), *SlotData.Item.GetName())

	ENSURE_KISMET(DraggedSlotWidgetClass)
	if (UDA_InventoryDraggedSlotWidget* DraggedWidget = CreateWidget<UDA_InventoryDraggedSlotWidget>(GetOwningPlayer(), DraggedSlotWidgetClass))
	{
		DraggedWidget->SetData(SlotData, SlotData.Item->GetOwnerInventory()->GetCellSize());

		if (UDA_InventorySlot_DragDropOperation* DragDropOperation = NewObject<UDA_InventorySlot_DragDropOperation>(this))
		{
			DragDropOperation->Payload = this;
			DragDropOperation->DefaultDragVisual = DraggedWidget;

			// todo: Encapsulate
			for (UDA_InventorySlotWidget* SlotWidget : Grid->GetSlotWidgets())
			{
				if (UGridSlot* GridSlot = UWidgetLayoutLibrary::SlotAsGridSlot(SlotWidget))
				{
					GridSlot->SetLayer(-1);
				}
			}

			OutOperation = DragDropOperation;
		}
	}
}

void UDA_InventorySlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	UE_LOG(X_Inventory, Verbose, TEXT("%s: Drag&Drop was canceled"), *SlotData.Item->GetOwnerInventory()->GetOwner()->GetName())
	DropItem();
}

bool UDA_InventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UE_LOG(X_Inventory, Verbose, TEXT("%s: Drag&Drop operation has ended"), *SlotData.Item->GetOwnerInventory()->GetOwner()->GetName())
	DropItem();
	return true;
}

FReply UDA_InventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

void UDA_InventorySlotWidget::DropItem() const
{
	// todo: Encapsulate
	for (UDA_InventorySlotWidget* SlotWidget : Grid->GetSlotWidgets())
	{
		if (UGridSlot* GridSlot = UWidgetLayoutLibrary::SlotAsGridSlot(SlotWidget))
		{
			GridSlot->SetLayer(1);
		}
	}

	if (UDA_InventoryComponent* Inventory = SlotData.Item->GetOwnerInventory())
	{
		Inventory->AddItem(SlotData);
	}
}

