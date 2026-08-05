// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventorySlotWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridSlot.h"
#include "Inventory/DA_InventoryItem.h"
#include "UserInterface/Inventory/DA_InventoryDraggedSlotWidget.h"
#include "UserInterface/Inventory/DA_InventoryGridWidget.h"
#include "UserInterface/Inventory/DA_InventorySlot_DragDropOperation.h"

void UDA_InventorySlotWidget::SetData(const FDA_InventorySlot& NewData, UDA_InventoryGridWidget* NewParentWidget)
{
	SlotData = NewData;
	ParentWidget = NewParentWidget;
}

void UDA_InventorySlotWidget::SetSlotSize(float Size)
{
	if (UCanvasPanelSlot* Panel = UWidgetLayoutLibrary::SlotAsCanvasSlot(SlotCanvas))
	{
		const FDA_Point2D ItemSize = SlotData.Item->Size;
		
		Panel->SetSize(FVector2D(ItemSize.X, ItemSize.Y) * Size);
	}
}

void UDA_InventorySlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	// TODO(DA): check DraggedSlotWidgetClass
	if (UDA_InventoryDraggedSlotWidget* DraggedWidget = CreateWidget<UDA_InventoryDraggedSlotWidget>(GetOwningPlayer(), DraggedSlotWidgetClass))
	{
		DraggedWidget->SetData(SlotData, SlotData.Item->GetOwnerInventory()->CellSize); // TODO(DA): GetOwnerInventory()

		if (UDA_InventorySlot_DragDropOperation* DragDropOperation = NewObject<UDA_InventorySlot_DragDropOperation>(this))
		{
			// TODO(DA): Move to constructor
			DragDropOperation->SlotWidget = this;
			DragDropOperation->DefaultDragVisual = DraggedWidget;
			DragDropOperation->Pivot = EDragPivot::MouseDown;
			
			// TODO(DA): GetOwnerInventory()
			SlotData.Item->GetOwnerInventory()->Slots.Remove(SlotData);

			for (UDA_InventorySlotWidget* SlotWidget : ParentWidget->SlotsWidgets)
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

	for (UDA_InventorySlotWidget* SlotWidget : ParentWidget->SlotsWidgets)
	{
		if (UGridSlot* GridSlot = UWidgetLayoutLibrary::SlotAsGridSlot(SlotWidget))
		{
			GridSlot->SetLayer(1);
		}
	}

	if (UDA_InventoryComponent* Inventory = SlotData.Item->GetOwnerInventory())
	{
		Inventory->Slots.Add(SlotData);

		// Inventory->HandleInventoryUpdate();
	}

	// TODO(DA): Copies NativeOnDrop()
}

bool UDA_InventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	//bool bDroppedSomething = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	for (UDA_InventorySlotWidget* SlotWidget : ParentWidget->SlotsWidgets)
	{
		if (UGridSlot* GridSlot = UWidgetLayoutLibrary::SlotAsGridSlot(SlotWidget))
		{
			GridSlot->SetLayer(1);
		}
	}

	if (UDA_InventoryComponent* Inventory = SlotData.Item->GetOwnerInventory())
	{
		Inventory->Slots.Add(SlotData);
		
		// Inventory->HandleInventoryUpdate();
	}

	// TODO(DA): Revisit this
	// bDroppedSomething |= true;
	return true;
}

FReply UDA_InventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply; // TODO(DA): Revisit this
}

