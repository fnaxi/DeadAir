// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/DA_InventoryItem.h"

UDA_InventoryItem::UDA_InventoryItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Size = FIntPoint(1, 1);
	bIsRotated = false;
	// todo: ItemID = 0;
}

void UDA_InventoryItem::OnConstruct()
{
	// SizeInCells.Empty();
	// SizeInCells = GetItemSize();

	// CachedSize = Size;
	// CachedSizeInCells = SizeInCells;

	bIsRotated = false;
}

void UDA_InventoryItem::SetStartCoordinates(const FIntPoint& Coordinates)
{
	StartCoordinates = Coordinates;
}

void UDA_InventoryItem::SetOwningInventory(UDA_InventoryComponent* NewInventory)
{
	OwnerInventory = NewInventory;
}

TArray<FIntPoint> UDA_InventoryItem::GetSizeInCells() const
{
	TArray<FIntPoint> ItemSize;

	for (int32 X = 0; X < Size.X; X++)
	{
		for (int32 Y = 0; Y < Size.Y; Y++)
		{
			ItemSize.Add(FIntPoint(X, Y));		
		}
	}

	return ItemSize;
}

bool UDA_InventoryItem::CanRotate()
{
	// Only rotate rectangle-shaped items because they might fit in a specific space.
	return Size.X != Size.Y;

	//return true; // Uncomment: If you want to be able to rotate any item.
}

void UDA_InventoryItem::Rotate()
{
	/*if (!CanRotate())
	{
		return;
	}

	if (bIsRotated)
	{
		Size = CachedSize;
		SizeInCells = CachedSizeInCells;

		bIsRotated = false;

		HandleItemRotation();
		//OwnerInventory->HandleInventoryUpdate();

		return;
	}

	SizeInCells.Empty();

	for (const FIntPoint& Coordinates : CachedSizeInCells)
	{
		FIntPoint InvertedCoordinates = FIntPoint(Coordinates.Y, Coordinates.X);
		SizeInCells.Add(InvertedCoordinates);	
	}

	const FIntPoint InvertedSize = FIntPoint(CachedSize.Y, CachedSize.X);
	Size = InvertedSize;

	bIsRotated = true;

	HandleItemRotation();
	//OwnerInventory->HandleInventoryUpdate();*/
}

void UDA_InventoryItem::HandleItemRotation()
{
	OnItemRotated.Broadcast();
}

FIntPoint UDA_InventoryItem::GetCoordinatesFromHover(const FIntPoint& HoveredCoordinates) const
{
	return FIntPoint(HoveredCoordinates.X - ((Size.X - 1) / 2), HoveredCoordinates.Y - ((Size.Y - 1) / 2));
}

