// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryCellWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/GridSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Inventory/DA_InventoryItem.h"
#include "UserInterface/Inventory/DA_InventorySlotWidget.h"
#include "UserInterface/Inventory/DA_InventoryDraggedSlotWidget.h"
#include "UserInterface/Inventory/DA_InventoryGridWidget.h"
#include "UserInterface/Inventory/DA_InventorySlot_DragDropOperation.h"

void UDA_InventoryCellWidget::SetData(const FIntPoint& InCoordinates, UDA_InventoryGridWidget* InParentWidget, const float InSize)
{
	Coordinates = InCoordinates;
	Grid = InParentWidget;
	check(Grid.IsValid());

	CoordinatesText->SetText(FText::FromString(FString::Printf(TEXT("(%i;%i)"), Coordinates.X, Coordinates.Y)));
	if (!bUseDebugCoordinates)
	{
		CoordinatesText->SetVisibility(ESlateVisibility::Hidden);
	}
	
    SetCellSize(InSize);
    SetCellColor(DefaultCellColor);
}

void UDA_InventoryCellWidget::SetCellSize(float Size) const
{
	Box->SetWidthOverride(Size);
	Box->SetHeightOverride(Size);
}

void UDA_InventoryCellWidget::SetCellColor(const FSlateBrush& Brush) const
{
	Background->SetBrush(Brush);
}

void UDA_InventoryCellWidget::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
	
	if (!InOperation || !InOperation->IsA<UDA_InventorySlot_DragDropOperation>()) return;

	Grid->ResetCellsToDefaultColor();
	
	const UDA_InventoryDraggedSlotWidget* DraggedSlot = Cast<UDA_InventoryDraggedSlotWidget>(InOperation->DefaultDragVisual);
	check(DraggedSlot != nullptr);

	const UDA_InventoryItem* Item = DraggedSlot->SlotData.Item;
	for (const FIntPoint& Element : Item->GetSizeInCells())
	{
		FIntPoint TargetCell = Element + Coordinates;
		const int32 Index = Grid->GetCellIndex(TargetCell);

		if (Index >= 0 && Index < Grid->GetCellWidgets().Num()) // Only change cell color if its within grid boundaries
		{
			if (Item->GetOwnerInventory()->DoesItemFit(Item->GetSizeInCells(), Coordinates, Item))
			{
				Grid->GetCellWidgets()[Index]->SetCellColor(ValidCellPlacementColor);
				UE_LOG(X_Inventory, VeryVerbose, TEXT("Item fits in %s coordinates"), *Coordinates.ToString())
			}
			else
			{
				Grid->GetCellWidgets()[Index]->SetCellColor(InvalidCellPlacementColor);
				UE_LOG(X_Inventory, VeryVerbose, TEXT("Item can't be fit in %s coordinates"), *Coordinates.ToString())
			}
		}
	}
}

void UDA_InventoryCellWidget::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);

	Grid->ResetCellsToDefaultColor();
}

void UDA_InventoryCellWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	Grid->ResetCellsToDefaultColor();
}

bool UDA_InventoryCellWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	if (!InOperation || !InOperation->IsA<UDA_InventorySlot_DragDropOperation>()) return false;

	const UDA_InventorySlotWidget* Payload = Cast<UDA_InventorySlotWidget>(InOperation->Payload);
	check(Payload != nullptr);

	Grid->ResetCellsToDefaultColor();
	
	// todo: Encapsulate
	for (UDA_InventorySlotWidget* SlotWidget : Payload->Grid->GetSlotWidgets())
	{
		if (UGridSlot* GridSlot = UWidgetLayoutLibrary::SlotAsGridSlot(SlotWidget))
		{
			GridSlot->SetLayer(1);
		}
	}
	
	const UDA_InventoryDraggedSlotWidget* DraggedWidget = Cast<UDA_InventoryDraggedSlotWidget>(InOperation->DefaultDragVisual);
	check(DraggedWidget != nullptr);

	const FDA_InventorySlot SlotData = DraggedWidget->SlotData;

	UDA_InventoryComponent* Inventory = SlotData.Item->GetOwnerInventory();
	if( ensure(Inventory) )
	{
		Inventory->MoveItem(DraggedWidget->SlotData, Coordinates);
	}
	
	return true;
}

