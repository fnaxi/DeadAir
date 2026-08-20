// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/DA_InventoryComponent.h"

#include "MiscUtils.h"
#include "Inventory/DA_InventoryItem.h"

DEFINE_LOG_CATEGORY(X_Inventory)

// Sets default values
UDA_InventoryComponent::UDA_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UDA_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

bool UDA_InventoryComponent::IsWithinBoundaries(const FIntPoint& Coordinates) const
{
	if (Coordinates.X >= 0 && Coordinates.Y >= 0 && Coordinates.X < GridSize.X && Coordinates.Y < GridSize.Y)
	{
		return true;
	}

	return false;
}

void UDA_InventoryComponent::Initialize()
{
	Slots.Empty();
	Cells.Empty();

	for (int32 X = 0; X < GridSize.X; X++)
	{
		for (int32 Y = 0; Y < GridSize.Y; Y++)
		{
			Cells.Add(FIntPoint(X, Y));
		}
	}

	OnInventoryInitialized.Broadcast();
	UE_LOG(X_Inventory, Log, TEXT("%s: Initialized inventory"), *GetOwner()->GetName())
}

bool UDA_InventoryComponent::IsFree(const FIntPoint& Coordinates, const UDA_InventoryItem* ItemToIgnore)
{
	if (!IsWithinBoundaries(Coordinates))
	{
		// The cell at these coordinates is outside the grid
		return false;
	}

	for (const FDA_InventorySlot& Slot : GetSlots())
	{
		if (ItemToIgnore && Slot.Item == ItemToIgnore) continue;
		
		for (const FIntPoint& Cell : Slot.Item->GetSizeInCells())
		{
			if (Slot.Item->GetStartCoordinates().X + Cell.X == Coordinates.X &&
				Slot.Item->GetStartCoordinates().Y + Cell.Y == Coordinates.Y)
			{
				// The cell at these coordinates is not empty.
				return false;
			}
		}
	}

	return true;
}

bool UDA_InventoryComponent::DoesItemFit(TArray<FIntPoint> const& SizeInCells, const FIntPoint& Coordinates, const UDA_InventoryItem* ItemToIgnore)
{
	for (const FIntPoint& Cell : SizeInCells)
	{
		const FIntPoint TargetCell = Coordinates + Cell;
		if (!IsFree(TargetCell, ItemToIgnore)) 
		{
			// Item does not fit because the cell at these coordinates is occupied.
			return false;
		}
	}

	return true;
}

FIntPoint UDA_InventoryComponent::GetFreeCell()
{
	for (const FIntPoint& Coordinates : Cells)
	{
		if (IsFree(Coordinates)) // todo: Replace with predicate
		{
			return Coordinates;
		}
	}

	return FIntPoint(-1, -1);
}

FIntPoint UDA_InventoryComponent::GetFreeCellThatFitsItem(TArray<FIntPoint> const& SizeInCells)
{
	for (const FIntPoint& Coordinates : Cells)
	{
		if (IsFree(Coordinates))
		{
			if (DoesItemFit(SizeInCells, Coordinates))
			{
				return Coordinates;
			}
		}
	}

	return FIntPoint(-1, -1);
}

bool UDA_InventoryComponent::AddItem(const FDA_InventorySlot& Slot)
{
	Slots.Add(Slot);
	UE_LOG(X_Inventory, Verbose, TEXT("%s: Added %i item(s) of type %s"), *GetOwner()->GetName(), Slot.Quantity, *Slot.Item->GetName())
	
	HandleInventoryUpdate();
	
	return true;
}

bool UDA_InventoryComponent::AddNewItem(TSubclassOf<UDA_InventoryItem> ItemClass, UDA_InventoryItemDataAsset* DataAsset, int32 Quantity)
{
	UDA_InventoryItem* Item = CreateItem(ItemClass, DataAsset);
	
	const FIntPoint Coordinates = GetFreeCellThatFitsItem(Item->GetSizeInCells());
	if (AreCoordinatesValid(Coordinates))
	{
		Item->SetStartCoordinates(Coordinates);

		const FDA_InventorySlot Data = FDA_InventorySlot(Item, Quantity);
		return AddItem(Data);
	}

	return false;
}

bool UDA_InventoryComponent::RemoveItem(const FDA_InventorySlot& Slot)
{
	Slots.Remove(Slot);
	UE_LOG(X_Inventory, Verbose, TEXT("%s: Removed %s item"), *GetOwner()->GetName(), *Slot.Item->GetName())
	
	return true;
}

bool UDA_InventoryComponent::MoveItem(const FDA_InventorySlot& InSlot, const FIntPoint& Destination)
{	
	for (const FDA_InventorySlot& Slot : Slots)
	{
		if (Slot != InSlot) continue;
		
		if (DoesItemFit(Slot.Item->GetSizeInCells(), Destination, Slot.Item))
		{
			Slot.Item->SetStartCoordinates(Destination);
			UE_LOG(X_Inventory, Log, TEXT("%s: Moved %s item to %s coordinates"), *GetOwner()->GetName(), *Slot.Item.GetName(), *Destination.ToString())
			
			HandleInventoryUpdate();
			return true;
		}
	}

	UE_LOG(X_Inventory, Warning, TEXT("%s: Item %s can't be moved to %s coordinates!"), *GetOwner()->GetName(), *InSlot.Item.GetName(), *Destination.ToString())
	return false;
}
UDA_InventoryItem* UDA_InventoryComponent::CreateItem(const TSubclassOf<UDA_InventoryItem>& ItemClass, UDA_InventoryItemDataAsset* DataAsset)
{
	if (!ensure(ItemClass)) return nullptr;
	
	UDA_InventoryItem* Item = NewObject<UDA_InventoryItem>(GetOwner(), ItemClass);
	if (Item != nullptr)
	{
		Item->SetOwningInventory(this);
		Item->SetDataAsset(DataAsset);
	}
	
	return Item;
}

void UDA_InventoryComponent::HandleInventoryUpdate()
{
	OnInventoryUpdated.Broadcast();
	UE_LOG(X_Inventory, Verbose, TEXT("%s: Inventory was updated"), *GetOwner()->GetName())
}

void UDA_InventoryComponent::PrintInventoryContent()
{
	UE_LOG(X_Inventory, Log, TEXT("%s: Inventory content:"), *GetOwner()->GetName())

	for (FDA_InventorySlot Slot : Slots)
	{
		UE_LOG(X_Inventory, Log, TEXT("%s: %s (Size: %s) (Coordinates: %s)"),
			*GetOwner()->GetName(), *Slot.Item.GetName(), *Slot.Item.Get()->GetSize().ToString(), *Slot.Item.Get()->GetStartCoordinates().ToString())
		
		DEBUG_MESSAGE(10.f, FColor::Green,
			FString::Printf(TEXT("%s (Size: %s) (Coordinates: %s)"),
			*Slot.Item.GetName(), *Slot.Item.Get()->GetSize().ToString(), *Slot.Item.Get()->GetStartCoordinates().ToString()))
	}
	
	DEBUG_MESSAGE( 10.f, FColor::Green, FString::Printf(TEXT("%s: Inventory content:"), *GetOwner()->GetName()) )
}

