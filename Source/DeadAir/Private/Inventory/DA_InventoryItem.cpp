// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/DA_InventoryItem.h"

#include "Inventory/DA_InventoryItemDataAsset.h"

void UDA_InventoryItem::SetOwningInventory(UDA_InventoryComponent* NewInventory)
{
	OwnerInventory = NewInventory;
}

void UDA_InventoryItem::SetDataAsset(UDA_InventoryItemDataAsset* InDataAsset)
{
	ensure(InDataAsset);
	DataAsset = InDataAsset;
}

void UDA_InventoryItem::SetStartCoordinates(const FIntPoint& Coordinates)
{
	StartCoordinates = Coordinates;
}

TArray<FIntPoint> UDA_InventoryItem::GetSizeInCells() const
{
	TArray<FIntPoint> ItemSize;

	for (int32 X = 0; X < GetSize().X; X++)
	{
		for (int32 Y = 0; Y < GetSize().Y; Y++)
		{
			ItemSize.Add(FIntPoint(X, Y));
		}
	}

	return ItemSize;
}

/*bool UDA_InventoryItem::CanRotate()
{
	// Only rotate rectangle-shaped items because they might fit in a specific space.
	return GetSize().X != GetSize().Y;

	//return true; // Uncomment: If you want to be able to rotate any item.
}*/

/*void UDA_InventoryItem::Rotate()
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

	for (const FIntPoint& Coordinates : CachedSizeInCells)
	{
		FIntPoint InvertedCoordinates = FIntPoint(Coordinates.Y, Coordinates.X);
		SizeInCells.Add(InvertedCoordinates);	
	}

	const FIntPoint InvertedSize = FIntPoint(CachedSize.Y, CachedSize.X);
	Size = InvertedSize;

	bIsRotated = true;

	HandleItemRotation();
	//OwnerInventory->HandleInventoryUpdate();
}*/

/*void UDA_InventoryItem::HandleItemRotation()
{
	OnItemRotated.Broadcast();
}*/

FIntPoint UDA_InventoryItem::GetCoordinatesFromHover(const FIntPoint& HoveredCoordinates) const
{
	return FIntPoint(HoveredCoordinates.X - ((GetSize().X - 1) / 2), HoveredCoordinates.Y - ((GetSize().Y - 1) / 2));
}

FText UDA_InventoryItem::GetItemName() const
{
	return DataAsset ? DataAsset->Name : FText::FromString(TEXT("SID_InvalidItemName"));
}

FText UDA_InventoryItem::GetItemDescription() const
{
	return DataAsset ? DataAsset->Description : FText::FromString(TEXT("SID_InvalidItemDescription"));
}

FIntPoint UDA_InventoryItem::GetSize() const
{
	return DataAsset ? DataAsset->Size : FIntPoint(1);;
}

FIntPoint UDA_InventoryItem::GetAtlasCoordinates() const
{
	return DataAsset ? DataAsset->AtlasCoordinates : FIntPoint(1);
}

float UDA_InventoryItem::GetWeight() const
{
	return DataAsset ? DataAsset->Weight : 0.0f;
}

