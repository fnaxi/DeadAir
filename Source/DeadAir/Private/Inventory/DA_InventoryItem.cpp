// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/DA_InventoryItem.h"

UDA_InventoryItem::UDA_InventoryItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	Size = FDA_Point2D(1, 1);
	bIsRotated = false;
	UniqueId = 0;
}

void UDA_InventoryItem::OnConstruct()
{
	SizeInCells.Empty();
	SizeInCells = CalcItemSize();

	CachedSize = Size;
	CachedSizeInCells = SizeInCells;

	bIsRotated = false;
}

void UDA_InventoryItem::SetStartCoordinates(const FDA_Point2D& Coordinates)
{
	StartCoordinates = Coordinates;
}

TArray<FDA_Point2D> UDA_InventoryItem::CalcItemSize()
{
	TArray<FDA_Point2D> ItemSize;

	for (int32 X = 0; X < Size.X; X++)
	{
		for (int32 Y = 0; Y < Size.Y; Y++)
		{
			ItemSize.Add(FDA_Point2D(X, Y));		
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
	if (!CanRotate())
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

	for (const FDA_Point2D& Coordinates: CachedSizeInCells)
	{
		FDA_Point2D InvertedCoordinates = FDA_Point2D(Coordinates.Y, Coordinates.X);
		SizeInCells.Add(InvertedCoordinates);	
	}

	const FDA_Point2D InvertedSize = FDA_Point2D(CachedSize.Y, CachedSize.X);
	Size = InvertedSize;

	bIsRotated = true;

	HandleItemRotation();
	//OwnerInventory->HandleInventoryUpdate();
}

void UDA_InventoryItem::SetOwningInventory(UDA_InventoryComponent* NewInventory)
{
	OwnerInventory = NewInventory;
}

void UDA_InventoryItem::HandleItemRotation()
{
	OnItemRotated.Broadcast();
}
