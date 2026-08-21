// CopyRight © Dead Air Game. All Rights Reserved.


#include "UserInterface/Inventory/DA_InventoryGridWidget.h"

#include "MiscUtils.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "UserInterface/Inventory/DA_InventoryCellWidget.h"
#include "Inventory/DA_InventoryComponent.h"
#include "Inventory/DA_InventoryItem.h"
#include "UserInterface/Inventory/DA_InventorySlotWidget.h"

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
	for (const UDA_InventoryCellWidget* Cell : CellWidgets)
	{
		Cell->SetCellColor(Cell->GetDefaultCellColor());
	}
}

void UDA_InventoryGridWidget::ChangeSlotsLayer(int32 Layer)
{
	for (UDA_InventorySlotWidget* SlotWidget : SlotWidgets)
	{
		if (UGridSlot* GridSlot = UWidgetLayoutLibrary::SlotAsGridSlot(SlotWidget))
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
	
	Inventory->Initialize();
	Inventory->OnInventoryUpdated.AddUObject(this, &ThisClass::OnInventoryUpdated);

	Grid->ClearChildren();
	
	CreateCells();
	CreateSlots();
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
			GridSlot->SetColumnSpan(Item->GetSize().X);
			GridSlot->SetRowSpan(Item->GetSize().Y);
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

	CreateSlots();
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
		CellWidget->SetData(Coordinates, this, Inventory->GetCellSize());

		OnCellCreated(CellWidget);
	}
}

void UDA_InventoryGridWidget::CreateSlots()
{
	SlotWidgets.Empty();
	for (const FDA_InventorySlot& Data : Inventory->GetSlots())
	{
		ENSURE_KISMET(SlotWidgetClass)
		
		UDA_InventorySlotWidget* SlotWidget = CreateWidget<UDA_InventorySlotWidget>(GetOwningPlayer(), SlotWidgetClass);
		check(SlotWidget != nullptr);

		SlotWidgets.Add(SlotWidget);
		SlotWidget->SetData(Data, Inventory->GetCellSize());
		SlotWidget->Grid = this; // todo: Use parent widget instead
		
		OnSlotCreated(SlotWidget);
	}
}

