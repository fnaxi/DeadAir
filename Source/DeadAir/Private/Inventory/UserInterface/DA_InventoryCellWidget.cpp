// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/UserInterface/DA_InventoryCellWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/GridSlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Inventory/DA_InventoryItem.h"
#include "Inventory/UserInterface/DA_InventorySlotWidget.h"
#include "Inventory/UserInterface/DA_InventoryDraggedSlotWidget.h"
#include "Inventory/UserInterface/DA_InventoryGridWidget.h"
#include "Inventory/UserInterface/DA_InventorySlot_DragDropOperation.h"

void UDA_InventoryCellWidget::SetData(const FDA_Point2D& NewCoordinates, const float NewSize, UDA_InventoryGridWidget* NewParentWidget)
{
	Coordinates = NewCoordinates;
	CellSize = NewSize;
	ParentWidget = NewParentWidget;

	OnDataReceived();
	  
    SetCellSize(NewSize);
    SetCellColor(DefaultCellColor);
}

void UDA_InventoryCellWidget::SetCellSize(float Size)
{
	UCanvasPanelSlot* CanvasSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CellCanvas);
	if (CanvasSlot)
	{
		CanvasSlot->SetSize(FVector2D(Size));
	}
}

void UDA_InventoryCellWidget::SetCellColor(const FSlateBrush& Brush)
{
	Background->SetBrush(Brush);
}

void UDA_InventoryCellWidget::OnDataReceived()
{
	// TODO(DA): add console var to disable debug coords
	//CoordinatesText->SetText( FText::FromString(TEXT("")) );
	CoordinatesText->SetText( FText::FromString(FString::Printf(TEXT("(%i, %i)"), Coordinates.X, Coordinates.Y)) );
}

void UDA_InventoryCellWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);

	// TODO(DA): duplicates UDA_InventoryCellWidget::NativeOnDrop
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
		Cell->SetCellColor(Cell->DefaultCellColor); // TODO(DA): make ResetCellsToDefaultColor() method
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
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	// reset all grid cells to their default color
	for (UDA_InventoryCellWidget* Cell : ParentWidget->CellsWidgets)
	{
		Cell->SetCellColor(Cell->DefaultCellColor);
	}

	UDA_InventorySlot_DragDropOperation* Operation = Cast<UDA_InventorySlot_DragDropOperation>(InOperation);
	check(Operation && Operation->SlotWidget && Operation->SlotWidget->ParentWidget)

	UDA_InventoryDraggedSlotWidget* DraggedWidget = Cast<UDA_InventoryDraggedSlotWidget>(Operation->DefaultDragVisual);
	check(DraggedWidget)

	UDA_InventoryItem* Item = DraggedWidget->SlotData.Item;
	check(Item)

	UDA_InventoryComponent* Inventory = Item->GetOwnerInventory();
	check(Inventory)
	
	Inventory->MoveItem(DraggedWidget->SlotData, Coordinates);
	
	for (UDA_InventorySlotWidget* SlotWidget : Operation->SlotWidget->ParentWidget->SlotsWidgets)
	{
		if (UGridSlot* GridSlot = UWidgetLayoutLibrary::SlotAsGridSlot(SlotWidget))
		{
			GridSlot->SetLayer(1);
		}
	}

	if (Inventory->DoesItemFit(Item->GetSizeInCells(), Coordinates))
	{
		Item->SetStartCoordinates(Coordinates);
	}
	
	Inventory->Slots.Add(DraggedWidget->SlotData);
	Inventory->HandleInventoryUpdate();
	
	return true;
}

