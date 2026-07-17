// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/UserInterface/DA_InventoryGridWidget.h"

#include "Inventory/UserInterface/DA_InventoryCellWidget.h"
#include "Inventory/DA_InventoryComponent.h"
#include "Inventory/UserInterface/DA_InventorySlotWidget.h"

void UDA_InventoryGridWidget::SetData(UDA_InventoryComponent* NewInventory)
{
	Inventory = NewInventory;

	// TODO(DA): moved from UDA_InventoryComponent::BeginPlay
	Inventory->Initialize();
	
	OnPrePopulateData();
	NativeOnDataReceived();
	OnDataReceived();
}

void UDA_InventoryGridWidget::NativeOnDataReceived()
{
	if (!Inventory->OnInventoryUpdated.IsBoundToObject(this))
	{
		Inventory->OnInventoryUpdated.AddUObject(this, &ThisClass::NativeOnInventoryUpdated);
	}

	CellsWidgets.Empty();
	SlotsWidgets.Empty();

	for (const FDA_Point2D& Coordinates : Inventory->Cells)
	{
		UDA_InventoryCellWidget* CellWidget = CreateWidget<UDA_InventoryCellWidget>(GetOwningPlayer(), CellWidgetClass);
		check(CellWidget != nullptr);

		CellsWidgets.Add(CellWidget);
		CellWidget->SetData(Coordinates, Inventory->CellSize, this);
		CellWidget->SetCellSize(Inventory->CellSize);
		CellWidget->SetCellColor(CellWidget->DefaultCellColor);

		OnCellCreated(CellWidget);
	}

	for (const FDA_InventorySlot& Data : Inventory->Slots)
	{
		UDA_InventorySlotWidget* SlotWidget = CreateWidget<UDA_InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		check(SlotWidget != nullptr);

		SlotsWidgets.Add(SlotWidget);
		SlotWidget->SetData(Data, this);
		SlotWidget->SetSlotSize(Inventory->CellSize);

		OnSlotCreated(SlotWidget);
	}
}

void UDA_InventoryGridWidget::NativeOnInventoryUpdated()
{
	for (UDA_InventorySlotWidget* SlotWidget : SlotsWidgets)
	{
		OnSlotRemoved(SlotWidget);
	}

	SlotsWidgets.Empty();

	for (const FDA_InventorySlot& Data : Inventory->Slots)
	{
		UDA_InventorySlotWidget* SlotWidget = CreateWidget<UDA_InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		check(SlotWidget != nullptr);

		SlotsWidgets.Add(SlotWidget);
		SlotWidget->SetData(Data, this);
		SlotWidget->SetSlotSize(Inventory->CellSize);
		OnSlotCreated(SlotWidget);
	}
	
	OnInventoryUpdated();
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
