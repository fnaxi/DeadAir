// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryGridWidget.h"

#include "DA_LogChannels.h"
#include "DA_MiscUtils.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "UserInterface/Inventory/DA_InventoryCellWidget.h"
#include "Inventory/DA_InventoryComponent.h"
#include "Inventory/DA_InventoryItem.h"
#include "UserInterface/Inventory/DA_InventoryItemWidget.h"

int32 UDA_InventoryGridWidget::GetCellIndex(const FIntPoint& InCoordinates) const
{
	for (int32 Index = 0; Index < CellWidgets.Num(); Index++)
	{
		if (CellWidgets[Index]->GetCoordinates() == InCoordinates)
		{
			return Index;
		}
	}

	return INDEX_NONE;
}

void UDA_InventoryGridWidget::ResetCellsToDefaultColor()
{
	for (const UDA_InventoryCellWidget* CellWidget : CellWidgets)
	{
		CellWidget->SetCellColor(CellWidget->GetDefaultCellColor());
	}
}

void UDA_InventoryGridWidget::ChangeItemsLayer(const int32 Layer)
{
	for (UDA_InventoryItemWidget* ItemWidget : ItemWidgets)
	{
		if (UGridSlot* GridSlot = UWidgetLayoutLibrary::SlotAsGridSlot(ItemWidget))
		{
			GridSlot->SetLayer(Layer);
		}
	}
}

void UDA_InventoryGridWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	Inventory = GetOwningPlayer()->GetPawn()->GetComponentByClass<UDA_InventoryComponent>();
	checkf(Inventory.IsValid(), TEXT("The pawn does not have the inventory component!"));
	
	Inventory->OnInventoryUpdated.AddUObject(this, &ThisClass::OnInventoryUpdated);

	Grid->ClearChildren();
	
	CreateCells();
	CreateItems();
}

void UDA_InventoryGridWidget::CreateCells()
{
	CellWidgets.Empty();
	for (const FIntPoint& Coordinates : Inventory->GetCells())
	{
		ENSURE_KISMET(CellWidgetClass)

		UDA_InventoryCellWidget* CellWidget = CreateWidget<UDA_InventoryCellWidget>(GetOwningPlayer(), CellWidgetClass);
		check(CellWidget != nullptr);

		CellWidgets.Add(CellWidget);
		CellWidget->InitializeCell(Coordinates, this, Inventory->GetCellSize());

		OnCellCreated(CellWidget);
	}
}

void UDA_InventoryGridWidget::CreateItems()
{
	ItemWidgets.Empty();
	for (UDA_InventoryItem* Item : Inventory->GetItems())
	{
		ENSURE_KISMET(ItemWidgetClass)
		
		UDA_InventoryItemWidget* ItemWidget = CreateWidget<UDA_InventoryItemWidget>(GetOwningPlayer(), ItemWidgetClass);
		check(ItemWidget != nullptr);

		ItemWidgets.Add(ItemWidget);
		
		ItemWidget->InitializeSlot(Item, Inventory->GetCellSize());
		ItemWidget->OnBeginDrag.BindLambda( [this]() { ChangeItemsLayer(-1); } );
		ItemWidget->OnEndDrag.BindLambda( [this]() { ChangeItemsLayer(1); } );
		
		OnItemCreated(ItemWidget);
	}
}

void UDA_InventoryGridWidget::OnCellCreated(UDA_InventoryCellWidget* Widget) const
{
	if (!Widget || !Grid) return;

	if (UGridSlot* GridSlot = Grid->AddChildToGrid(Widget, Widget->GetCoordinates().Y, Widget->GetCoordinates().X))
	{
		GridSlot->SetRowSpan(1);
		GridSlot->SetColumnSpan(1);
	}
}

void UDA_InventoryGridWidget::OnItemCreated(UDA_InventoryItemWidget* Widget) const
{
	if (!Widget || !Grid) return;

	if (const UDA_InventoryItem* Item = Widget->GetItem())
	{
		if (UGridSlot* GridSlot = Grid->AddChildToGrid(Widget, Item->GetStartCoordinates().Y, Item->GetStartCoordinates().X))
		{
			GridSlot->SetColumnSpan(Item->GetSize().X);
			GridSlot->SetRowSpan(Item->GetSize().Y);
			GridSlot->SetLayer(1);
		}
	}
}

void UDA_InventoryGridWidget::OnItemRemoved(UDA_InventoryItemWidget* Widget) const
{
	if (!Widget || !Grid) return;

	Grid->RemoveChild(Widget);
}

void UDA_InventoryGridWidget::OnInventoryUpdated()
{
	for (UDA_InventoryItemWidget* ItemWidget : ItemWidgets)
	{
		OnItemRemoved(ItemWidget);
	}

	CreateItems();
}

