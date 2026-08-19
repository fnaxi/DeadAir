// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryGridWidget.h"

#include "MiscUtils.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "UserInterface/Inventory/DA_InventoryCellWidget.h"
#include "Inventory/DA_InventoryComponent.h"
#include "Inventory/DA_InventoryItem.h"
#include "UserInterface/Inventory/DA_InventorySlotWidget.h"

void UDA_InventoryGridWidget::SetData(UDA_InventoryComponent* InInventory)
{
	Inventory = InInventory;
	check(Inventory != nullptr);
	
	Inventory->Initialize();
	Inventory->OnInventoryUpdated.AddUObject(this, &ThisClass::OnInventoryUpdated);

	Grid->ClearChildren();
	
	CellWidgets.Empty();
	for (const FIntPoint& Coordinates : Inventory->GetCells())
	{
		ENSURE_KISMET(CellWidgetClass)

		UDA_InventoryCellWidget* CellWidget = CreateWidget<UDA_InventoryCellWidget>(GetOwningPlayer(), CellWidgetClass);
		check(CellWidget != nullptr);

		CellWidgets.Add(CellWidget);
		CellWidget->SetData(Coordinates, this, Inventory->GetCellSize());

		OnCellCreated(CellWidget);
	}
	
	SlotWidgets.Empty();
	for (const FDA_InventorySlot& Data : Inventory->GetSlots())
	{
		ENSURE_KISMET(SlotWidgetClass)
		
		UDA_InventorySlotWidget* SlotWidget = CreateWidget<UDA_InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		check(SlotWidget != nullptr);

		SlotWidgets.Add(SlotWidget);
		SlotWidget->SetData(Data, this, Inventory->GetCellSize());

		OnSlotCreated(SlotWidget);
	}
}

int32 UDA_InventoryGridWidget::GetCellIndex(const FIntPoint& InCoordinates)
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
	for (const UDA_InventoryCellWidget* Cell : CellWidgets)
	{
		Cell->SetCellColor(Cell->GetDefaultCellColor());
	}
}

void UDA_InventoryGridWidget::OnCellCreated(UDA_InventoryCellWidget* Widget)
{
	if (!Widget || !Grid) return;

	if (UGridSlot* GridSlot = Grid->AddChildToGrid(Widget, Widget->GetCoordinates().Y, Widget->GetCoordinates().X))
	{
		GridSlot->SetRowSpan(1);
		GridSlot->SetColumnSpan(1);
	}
}

void UDA_InventoryGridWidget::OnSlotCreated(UDA_InventorySlotWidget* Widget)
{
	if (!Widget || !Grid) return;

	if (const UDA_InventoryItem* Item = Widget->GetSlotData().Item)
	{
		if (UGridSlot* GridSlot = Grid->AddChildToGrid(Widget, Item->GetStartCoordinates().Y, Item->GetStartCoordinates().X))
		{
			GridSlot->SetColumnSpan(Item->Size.X);
			GridSlot->SetRowSpan(Item->Size.Y);
			GridSlot->SetLayer(1);
		}
	}
}

void UDA_InventoryGridWidget::OnSlotRemoved(UDA_InventorySlotWidget* Widget)
{
	if (!Widget || !Grid) return;

	Grid->RemoveChild(Widget);
}

void UDA_InventoryGridWidget::OnInventoryUpdated()
{
	for (UDA_InventorySlotWidget* SlotWidget : SlotWidgets)
	{
		OnSlotRemoved(SlotWidget);
	}

	SlotWidgets.Empty();

	ENSURE_KISMET(SlotWidgetClass)
	for (const FDA_InventorySlot& Data : Inventory->GetSlots())
	{
		UDA_InventorySlotWidget* SlotWidget = CreateWidget<UDA_InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		if (SlotWidget != nullptr)
		{
			check(SlotWidget);

			SlotWidgets.Add(SlotWidget);
		
			SlotWidget->SetData(Data, this, Inventory->GetCellSize());
		
			OnSlotCreated(SlotWidget);
		}
	}
}

