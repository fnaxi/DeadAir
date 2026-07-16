// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/UserInterface/DA_InventoryCellWidget.h"

#include "Inventory/DA_InventoryItem.h"
#include "Inventory/UserInterface/DA_InventorySlotWidget.h"
#include "Inventory/UserInterface/DA_InventoryDraggedSlotWidget.h"
#include "Inventory/UserInterface/DA_InventoryGridWidget.h"
#include "Inventory/UserInterface/DA_InventorySlot_DragDropOperation.h"

UDA_InventoryCellWidget::UDA_InventoryCellWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UDA_InventoryCellWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	UDA_InventorySlot_DragDropOperation* Operation = Cast<UDA_InventorySlot_DragDropOperation>(InOperation);
	check(Operation != nullptr);

	UDA_InventoryDraggedSlotWidget* DraggedSlot = Cast<UDA_InventoryDraggedSlotWidget>(Operation->DefaultDragVisual);
	check(DraggedSlot != nullptr);

	// reset all grid cells to their default color
	for (UDA_InventoryCellWidget* Cell : ParentWidget->CellsWidgets)
	{
		Cell->SetCellColor(Cell->DefaultCellColor);
	}

	TArray<FDA_Point2D> ItemSizeInCells = DraggedSlot->SlotData.Item->GetSizeInCells();

	if (DraggedSlot->SlotData.Item->GetOwnerInventory()->DoesItemFit(ItemSizeInCells, Coordinates))
	{
		// Dragged item can be placed, set cells color to valid color ...
		// (starting from current cell coordinates to `coordinates+item size` ...)
		for (FDA_Point2D& Element : ItemSizeInCells)
		{
			FDA_Point2D TargetCell = Element + Coordinates;
			const int32 Index = ParentWidget->GetCellIndex(TargetCell);

			if (Index >= 0 && Index < ParentWidget->CellsWidgets.Num())
			{
				// Only change cell color if its within grid boundaries
				ParentWidget->CellsWidgets[Index]->SetCellColor(ValidCellPlacementColor);
			}

			//UE_LOG(LogTemp, Warning, TEXT("Element (%d,%d). TargetCell (%d,%d). Index (%d)"), Element.X, Element.Y, TargetCell.X, TargetCell.Y, Index);
		}
	}
	else
	{
		// Dragged item cannot be placed, set cells color to invalid color ...
		// (starting from current cell coordinates to `coordinates+item size` ...)
		for (FDA_Point2D& Element : ItemSizeInCells)
		{
			FDA_Point2D TargetCell = Element + Coordinates;
			const int32 Index = ParentWidget->GetCellIndex(TargetCell);

			if (Index >= 0 && Index < ParentWidget->CellsWidgets.Num())
			{
				// Only change cell color if its within grid boundaries
				ParentWidget->CellsWidgets[Index]->SetCellColor(InvalidCellPlacementColor);
			}

			//UE_LOG(LogTemp, Warning, TEXT("Element (%d,%d). TargetCell (%d,%d). Index (%d)"), Element.X, Element.Y, TargetCell.X, TargetCell.Y, Index);
		}
	}
}

void UDA_InventoryCellWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	// reset all grid cells to their default color
	for (UDA_InventoryCellWidget* Cell : ParentWidget->CellsWidgets)
	{
		Cell->SetCellColor(Cell->DefaultCellColor);
	}
}

void UDA_InventoryCellWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	// reset all grid cells to their default color
	for (UDA_InventoryCellWidget* Cell : ParentWidget->CellsWidgets)
	{
		Cell->SetCellColor(Cell->DefaultCellColor);
	}
}

bool UDA_InventoryCellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	bool bDroppedSomething = Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	// reset all grid cells to their default color
	for (UDA_InventoryCellWidget* Cell : ParentWidget->CellsWidgets)
	{
		Cell->SetCellColor(Cell->DefaultCellColor);
	}

	UDA_InventorySlot_DragDropOperation* Operation = Cast<UDA_InventorySlot_DragDropOperation>(InOperation);
	check(Operation != nullptr);

	UDA_InventoryDraggedSlotWidget* DraggedSlot = Cast<UDA_InventoryDraggedSlotWidget>(Operation->DefaultDragVisual);
	check(DraggedSlot != nullptr);

	DraggedSlot->SlotData.Item->GetOwnerInventory()->MoveItem(DraggedSlot->SlotData, Coordinates);

	bDroppedSomething |= true;

	return bDroppedSomething;
}

void UDA_InventoryCellWidget::SetData(const FDA_Point2D& NewCoordinates, const float NewSize, UDA_InventoryGridWidget* NewParentWidget)
{
	Coordinates = NewCoordinates;
	CellSize = NewSize;
	ParentWidget = NewParentWidget;

	OnDataReceived();
	  
    SetCellSize(NewSize);
    SetCellColor(DefaultCellColor);
}

