// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/DA_InventoryComponent.h"

#include "DA_InventoryItemDefinition.h"
#include "DA_LogChannels.h"
#include "Inventory/DA_InventoryItem.h"

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
	
	for (int32 Y = 0; Y < GridSize.Y; Y++)
	{
		for (int32 X = 0; X < GridSize.X; X++)
		{
			Cells.Add(FIntPoint(X, Y));
		}
	}

	OnInventoryInitialized.Broadcast();
	UE_LOG(X_Inventory, Log, TEXT("%s: Initialized inventory"), *GetOwner()->GetName())
}

bool UDA_InventoryComponent::IsFree(const FIntPoint& Coordinates, const UDA_InventoryItem* ItemToIgnore) const
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

bool UDA_InventoryComponent::DoesItemFit(TArray<FIntPoint> const& SizeInCells, const FIntPoint& Coordinates, const UDA_InventoryItem* ItemToIgnore) const
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
	const FIntPoint* FoundCoordinates = Cells.FindByPredicate([this](const FIntPoint& Coordinates)
	{
		return IsFree(Coordinates);
	});

	return FoundCoordinates ? *FoundCoordinates : FIntPoint(-1);
}

FIntPoint UDA_InventoryComponent::GetFreeCellThatFitsItem(TArray<FIntPoint> const& SizeInCells)
{
	const FIntPoint* FoundCoordinates = Cells.FindByPredicate([this, SizeInCells](const FIntPoint& Coordinates)
	{
		return IsFree(Coordinates) && DoesItemFit(SizeInCells, Coordinates);
	});

	return FoundCoordinates ? *FoundCoordinates : FIntPoint(-1);
}

bool UDA_InventoryComponent::AddItem(const FDA_InventorySlot& Slot)
{
	if (AreCoordinatesValid(Slot.Item->GetStartCoordinates())) //@TODO: check that cell is free
	{
		Slots.Add(Slot);
		UE_LOG(X_Inventory, Verbose, TEXT("%s: Added \"%s\" item"), *GetOwner()->GetName(), *Slot.Item->GetItemName().ToString())
	
		NotifyInventoryUpdated();
		return true;
	}
	
	UE_LOG(X_Inventory, Log, TEXT("%s: Can't add \"%s\" item!"), *GetOwner()->GetName(), *Slot.Item->GetItemName().ToString())
	return false;
}

bool UDA_InventoryComponent::AddNewItem(UDA_InventoryItemDefinition* Definition, const int32 Quantity)
{
	UDA_InventoryItem* Item = CreateItem(Definition);
	if (Item == nullptr) return false;
	
	const FIntPoint Coordinates = GetFreeCellThatFitsItem(Item->GetSizeInCells());
	Item->SetStartCoordinates(Coordinates);

	const FDA_InventorySlot Slot = FDA_InventorySlot(Item, Quantity);
	return AddItem(Slot);
}

bool UDA_InventoryComponent::RemoveItem(const FDA_InventorySlot& Slot)
{
	Slots.Remove(Slot);
	UE_LOG(X_Inventory, Verbose, TEXT("%s: Removed \"%s\" item"), *GetOwner()->GetName(), *Slot.Item->GetItemName().ToString())
	
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
			UE_LOG(X_Inventory, Log, TEXT("%s: Moved \"%s\" item to %s coordinates"), *GetOwner()->GetName(), *Slot.Item->GetItemName().ToString(), *Destination.ToString())
			
			NotifyInventoryUpdated();
			return true;
		}
	}

	UE_LOG(X_Inventory, Log, TEXT("%s: Item \"%s\" can't be moved to %s coordinates!"), *GetOwner()->GetName(), *InSlot.Item->GetItemName().ToString(), *Destination.ToString())
	return false;
}

UDA_InventoryItem* UDA_InventoryComponent::CreateItem(UDA_InventoryItemDefinition* Definition)
{
	if (!ensure(Definition && Definition->ItemClass)) return nullptr;
	
	UDA_InventoryItem* Item = NewObject<UDA_InventoryItem>(GetOwner(), Definition->ItemClass);
	if (Item != nullptr)
	{
		Item->SetOwningInventory(this);
		Item->SetDefinition(Definition);
	}
	
	return Item;
}

void UDA_InventoryComponent::NotifyInventoryUpdated()
{
	OnInventoryUpdated.Broadcast();
	UE_LOG(X_Inventory, Verbose, TEXT("%s: Inventory was updated"), *GetOwner()->GetName())
}

