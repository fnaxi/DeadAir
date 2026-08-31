// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryCellWidget.h"

#include "DA_LogChannels.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Inventory/DA_InventoryItem.h"
#include "UserInterface/Inventory/DA_InventoryItemWidget.h"
#include "UserInterface/Inventory/DA_InventoryDraggedItemWidget.h"
#include "UserInterface/Inventory/DA_InventoryGridWidget.h"
#include "UserInterface/Inventory/DA_InventoryItem_DragDropOperation.h"

void UDA_InventoryCellWidget::InitializeCell(const FIntPoint& InCoordinates, UDA_InventoryGridWidget* InGrid, const float InSize)
{
	Coordinates = InCoordinates;
	Grid = InGrid;
	check(Grid.IsValid());

	CoordinatesText->SetText(FText::FromString(FString::Printf(TEXT("(%i;%i)"), Coordinates.X, Coordinates.Y)));

	constexpr bool bUseDebugCoordinates = false;
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
	
	if (!InOperation || !InOperation->IsA<UDA_InventoryItem_DragDropOperation>()) return;

	Grid->ResetCellsToDefaultColor();
	
	const UDA_InventoryDraggedItemWidget* DraggedSlot = CastChecked<UDA_InventoryDraggedItemWidget>(InOperation->DefaultDragVisual);

	const UDA_InventoryItem* Item = DraggedSlot->GetItem();
	for (const FIntPoint& Element : Item->GetSizeInCells())
	{
		FIntPoint TargetCoordinates = Item->GetCoordinatesFromHover(Coordinates);
		FIntPoint TargetCell = Element + TargetCoordinates;
		
		const int32 Index = Grid->GetCellIndex(TargetCell);
		if (Index >= 0 && Index < Grid->GetCellWidgets().Num()) // Only change cell color if its within grid boundaries
		{
			if (Item->GetOwnerInventory()->DoesItemFit(Item->GetSizeInCells(), TargetCoordinates, Item))
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

	if (!InOperation || !InOperation->IsA<UDA_InventoryItem_DragDropOperation>()) return false;

	Grid->ResetCellsToDefaultColor();
	
	const UDA_InventoryDraggedItemWidget* DraggedWidget = CastChecked<UDA_InventoryDraggedItemWidget>(InOperation->DefaultDragVisual);
	const UDA_InventoryItem* Item = DraggedWidget->GetItem();

	UDA_InventoryComponent* Inventory = Item->GetOwnerInventory();
	if (ensure(Inventory != nullptr))
	{
		Inventory->MoveItem(Item, Item->GetCoordinatesFromHover(Coordinates));
	}
	
	return true;
}

