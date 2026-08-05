// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/UserInterface/DA_InventoryGridWidget.h"

#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Inventory/UserInterface/DA_InventoryCellWidget.h"
#include "Inventory/DA_InventoryComponent.h"
#include "Inventory/DA_InventoryItem.h"
#include "Inventory/UserInterface/DA_InventorySlotWidget.h"

void UDA_InventoryGridWidget::SetData(UDA_InventoryComponent* NewInventory)
{
	Inventory = NewInventory;

	// TODO(DA): moved from UDA_InventoryComponent::BeginPlay
	Inventory->Initialize();
	
	OnPrePopulateData();
	OnDataReceived();
}

int32 UDA_InventoryGridWidget::GetCellIndex(const FDA_Point2D& InCoordinates)
{
	for (int32 Index = 0; Index < CellsWidgets.Num(); Index++)
	{
		if (CellsWidgets[Index]->Coordinates == InCoordinates)
		{
			return Index;
		}
	}

	return INDEX_NONE;
}

void UDA_InventoryGridWidget::OnDataReceived()
{
	if (!Inventory->OnInventoryUpdated.IsBoundToObject(this))
	{
		Inventory->OnInventoryUpdated.AddUObject(this, &ThisClass::OnInventoryUpdated);
	}

	CellsWidgets.Empty();
	SlotsWidgets.Empty();

	for (const FDA_Point2D& Coordinates : Inventory->Cells)
	{
		UDA_InventoryCellWidget* CellWidget = CreateWidget<UDA_InventoryCellWidget>(GetOwningPlayer(), CellWidgetClass);
		check(CellWidget)

		CellsWidgets.Add(CellWidget);
		CellWidget->SetData(Coordinates, Inventory->CellSize, this);
		CellWidget->SetCellSize(Inventory->CellSize);
		CellWidget->SetCellColor(CellWidget->DefaultCellColor);

		OnCellCreated(CellWidget);
	}

	for (const FDA_InventorySlot& Data : Inventory->Slots)
	{
		UDA_InventorySlotWidget* SlotWidget = CreateWidget<UDA_InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		check(SlotWidget != nullptr)

		SlotsWidgets.Add(SlotWidget);
		SlotWidget->SetData(Data, this);
		SlotWidget->SetSlotSize(Inventory->CellSize);

		OnSlotCreated(SlotWidget);
	}
}

void UDA_InventoryGridWidget::OnPrePopulateData()
{
	if (!Grid) return;

	Grid->ClearChildren();
}

void UDA_InventoryGridWidget::OnCellCreated(UDA_InventoryCellWidget* Widget)
{
	if (!Widget || !Grid) return;

	UGridSlot* GridSlot = Grid->AddChildToGrid(Widget, Widget->Coordinates.Y, Widget->Coordinates.X);
	if (GridSlot)
	{
		GridSlot->SetRowSpan(1);
		GridSlot->SetColumnSpan(1);

		// TODO(DA): Already 0 by default but can be left for clarity
		// GridSlot->SetLayer(0);
	}
}

void UDA_InventoryGridWidget::OnSlotCreated(UDA_InventorySlotWidget* Widget)
{
	if (!Widget || !Grid) return;

	if (UDA_InventoryItem* Item = Widget->SlotData.Item)
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
	for (UDA_InventorySlotWidget* SlotWidget : SlotsWidgets)
	{
		OnSlotRemoved(SlotWidget);
	}

	SlotsWidgets.Empty();

	for (const FDA_InventorySlot& Data : Inventory->Slots)
	{
		UDA_InventorySlotWidget* SlotWidget = CreateWidget<UDA_InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		check(SlotWidget)

		SlotsWidgets.Add(SlotWidget);
		SlotWidget->SetData(Data, this);
		SlotWidget->SetSlotSize(Inventory->CellSize);
		OnSlotCreated(SlotWidget);
	}
}

