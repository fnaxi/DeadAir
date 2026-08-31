// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryItemWidget.h"

#include "DA_LogChannels.h"
#include "DA_MiscUtils.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Inventory/DA_InventoryItem.h"
#include "UserInterface/Inventory/DA_InventoryItemTooltip.h"
#include "UserInterface/Inventory/DA_InventoryDraggedItemWidget.h"
#include "UserInterface/Inventory/DA_InventoryGridWidget.h"
#include "UserInterface/Inventory/DA_InventoryItem_DragDropOperation.h"

void UDA_InventoryItemWidget::InitializeSlot(UDA_InventoryItem* InItem, const float InSize)
{
	Super::InitializeSlot(InItem, InSize);

	ENSURE_KISMET(TooltipClass)
	if (UDA_InventoryItemTooltip* Widget = CreateWidget<UDA_InventoryItemTooltip>(GetOwningPlayer(), TooltipClass))
	{
		Widget->InitializeTooltip(Item);
		SetToolTip(Widget);
	}
}

void UDA_InventoryItemWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	UE_LOG(X_Inventory, Verbose, TEXT("%s: Drag&Drop was detected for %s item"), *Item->GetOwnerInventory()->GetOwner()->GetName(), *Item.GetName())

	ENSURE_KISMET(DraggedItemWidgetClass)
	if (UDA_InventoryDraggedItemWidget* DraggedWidget = CreateWidget<UDA_InventoryDraggedItemWidget>(GetOwningPlayer(), DraggedItemWidgetClass))
	{
		DraggedWidget->InitializeSlot(Item, Item->GetOwnerInventory()->GetCellSize());

		if (UDA_InventoryItem_DragDropOperation* DragDropOperation = NewObject<UDA_InventoryItem_DragDropOperation>(this))
		{
			DragDropOperation->Payload = this;
			DragDropOperation->DefaultDragVisual = DraggedWidget;

			OnBeginDrag.Execute();
			
			OutOperation = DragDropOperation;
		}
	}
}

void UDA_InventoryItemWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	UE_LOG(X_Inventory, Verbose, TEXT("%s: Drag&Drop operation was canceled"), *Item->GetOwnerInventory()->GetOwner()->GetName())
	OnEndDrag.Execute();
}

bool UDA_InventoryItemWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UE_LOG(X_Inventory, Verbose, TEXT("%s: Drag&Drop operation has ended"), *Item->GetOwnerInventory()->GetOwner()->GetName())
	return true;
}

FReply UDA_InventoryItemWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
}

