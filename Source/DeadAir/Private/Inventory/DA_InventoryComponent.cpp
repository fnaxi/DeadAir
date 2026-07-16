// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/DA_InventoryComponent.h"

#include "Inventory/DA_InventoryItem.h"

UDA_InventoryComponent::UDA_InventoryComponent()
{
	GridSize = FDA_Point2D(10, 10);
	CellSize = 70.0f;
}

UDA_InventoryComponent::UDA_InventoryComponent(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	GridSize = FDA_Point2D(10, 10);
	CellSize = 70.0f;
}

void UDA_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// TODO(DA): Moved to ADA_InventoryGridWidget::SetData()
	// Initialize();
}

bool UDA_InventoryComponent::IsWithinBoundaries(const FDA_Point2D& Coordinates)
{
	if (Coordinates.X >= 0 && Coordinates.Y >= 0 && Coordinates.X < GridSize.X && Coordinates.Y < GridSize.Y)
	{
		return true;
	}

	return false;
}

void UDA_InventoryComponent::Initialize()
{                                                                      
	Cells.Empty();

	for (int32 X = 0; X < GridSize.X; X++)
	{
		for (int32 Y = 0; Y < GridSize.Y; Y++)
		{
			Cells.Add(FDA_Point2D(X, Y));
		}
	}

	Slots.Empty();
}

bool UDA_InventoryComponent::IsFree(const FDA_Point2D& Coordinates)
{
	if (!IsWithinBoundaries(Coordinates))
	{
		// the cell at these coordinates is outside the grid.
		return false;
	}

	for (const FDA_InventorySlot& Slot: Slots)
	{
		for (const FDA_Point2D& Cell: Slot.Item->GetSizeInCells())
		{
			if (Slot.Item->GetStartCoordinates().X + Cell.X == Coordinates.X &&
				Slot.Item->GetStartCoordinates().Y + Cell.Y == Coordinates.Y)
			{
				// the cell at these coordinates is not empty.
				return false;
			}
		}
	}

	return true;
}

bool UDA_InventoryComponent::DoesItemFit(TArray<FDA_Point2D> const& SizeInCells, const FDA_Point2D& Coordinates)
{
	for (const FDA_Point2D& Cell: SizeInCells)
	{																													
		if (!IsFree(FDA_Point2D(Coordinates.X + Cell.X, Coordinates.Y + Cell.Y))) 
		{
			// Item does not fit because the cell at these coordinates is occupied.
			return false;
		}
	}

	return true;
}

FDA_Point2D UDA_InventoryComponent::GetFreeCell()
{
	for (const FDA_Point2D& Coordinates: Cells)
	{
		if (IsFree(Coordinates))
		{
			return Coordinates;
		}
	}

	return FDA_Point2D(-1, -1);
}

FDA_Point2D UDA_InventoryComponent::GetFreeCellThatFitsItem(TArray<FDA_Point2D> const& SizeInCells)
{
	for (const FDA_Point2D& Coordinates: Cells)
	{
		if (IsFree(Coordinates))
		{
			if (DoesItemFit(SizeInCells, Coordinates))
			{
				return Coordinates;
			}
		}
	}

	return FDA_Point2D(-1, -1);
}

bool UDA_InventoryComponent::AddItem(const TSubclassOf<UDA_InventoryItem> ItemClass, const int32 Quantity)
{
	UDA_InventoryItem* ItemInstance = CreateItem(ItemClass);
	const FDA_Point2D Coordinates = GetFreeCellThatFitsItem(ItemInstance->GetSizeInCells());

	if (Coordinates.IsValid())
	{
		ItemInstance->SetStartCoordinates(Coordinates);

		const FDA_InventorySlot Data = FDA_InventorySlot(ItemInstance, Quantity);
		Slots.Add(Data);

		HandleInventoryUpdate();

		return true;
	}

	if (ItemInstance->CanRotate())
	{
		ItemInstance->Rotate();

		const FDA_Point2D RotatedCoordinates = GetFreeCellThatFitsItem(ItemInstance->GetSizeInCells());

		if (RotatedCoordinates.IsValid())
		{
			ItemInstance->SetStartCoordinates(RotatedCoordinates);

			const FDA_InventorySlot Data = FDA_InventorySlot(ItemInstance, Quantity);
			Slots.Add(Data);

			HandleInventoryUpdate();

			return true;
		}

		return false;
	}

	return false;
}

bool UDA_InventoryComponent::RemoveItem(int32 UniqueId, int32 Quantity)
{
	return true;
}

void UDA_InventoryComponent::MoveItem(const FDA_InventorySlot& Slot, const FDA_Point2D& Destination)
{
	for (const FDA_InventorySlot& Element : Slots)
	{
		if (Element == Slot)
		{
			if (DoesItemFit(Element.Item->GetSizeInCells(), Destination))
			{
				Element.Item->SetStartCoordinates(Destination);
				HandleInventoryUpdate();
				return;
			}
		}
	}
}

UDA_InventoryItem* UDA_InventoryComponent::CreateItem(const TSubclassOf<UDA_InventoryItem> ItemClass)
{
	UDA_InventoryItem* ItemInstance = NewObject<UDA_InventoryItem>(GetOwner(), ItemClass);
	check(ItemInstance != nullptr);

	ItemInstance->OnConstruct();
	ItemInstance->SetOwningInventory(this);

	return ItemInstance;
}

void UDA_InventoryComponent::HandleInventoryUpdate()
{
	OnInventoryUpdated.Broadcast();
}

