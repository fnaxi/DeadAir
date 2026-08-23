// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventorySlotWidget.h"

#include "DA_LogChannels.h"
#include "DA_MiscUtils.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Inventory/DA_InventoryItem.h"
#include "UserInterface/Inventory/DA_InventorySlotTooltip.h"
#include "UserInterface/Inventory/DA_InventoryDraggedSlotWidget.h"
#include "UserInterface/Inventory/DA_InventoryGridWidget.h"
#include "UserInterface/Inventory/DA_InventorySlot_DragDropOperation.h"

void UDA_InventorySlotWidget::SetData(const FDA_InventorySlot& InSlotData, const float InSize)
{
	Super::SetData(InSlotData, InSize);

	ENSURE_KISMET(TooltipClass)
	if (UDA_InventorySlotTooltip* Widget = CreateWidget<UDA_InventorySlotTooltip>(GetOwningPlayer(), TooltipClass))
	{
		Widget->SetData(SlotData);
		SetToolTip(Widget);
	}
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

			Grid->ChangeSlotsLayer(-1);
			
			OutOperation = DragDropOperation;
		}
	}
}

void UDA_InventorySlotWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	UE_LOG(X_Inventory, Verbose, TEXT("%s: Drag&Drop was canceled"), *SlotData.Item->GetOwnerInventory()->GetOwner()->GetName())
	Grid->ChangeSlotsLayer(1);
}

bool UDA_InventorySlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UE_LOG(X_Inventory, Verbose, TEXT("%s: Drag&Drop operation has ended"), *SlotData.Item->GetOwnerInventory()->GetOwner()->GetName())
	Grid->ChangeSlotsLayer(1);
	
	return true;
}

FReply UDA_InventorySlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

