// CopyRight © Dead Air Game. All Rights Reserved.


#include "Inventory/DA_InventoryItem.h"

#include "Inventory/DA_InventoryItemDefinition.h"

UDA_InventoryItem::UDA_InventoryItem(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UDA_InventoryItem::SetOwningInventory(UDA_InventoryComponent* InInventory)
{
	OwnerInventory = InInventory;
}

void UDA_InventoryItem::SetDefinition(UDA_InventoryItemDefinition* InDefinition)
{
	ensure(InDefinition);
	Definition = InDefinition;
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

FIntPoint UDA_InventoryItem::GetCoordinatesFromHover(const FIntPoint& HoveredCoordinates) const
{
	return FIntPoint(HoveredCoordinates.X - ((GetSize().X - 1) / 2), HoveredCoordinates.Y - ((GetSize().Y - 1) / 2));
}

FText UDA_InventoryItem::GetItemName() const
{
	return Definition ? Definition->Name : FText::FromString(TEXT("SID_InvalidItemName"));
}

FText UDA_InventoryItem::GetItemDescription() const
{
	return Definition ? Definition->Description : FText::FromString(TEXT("SID_InvalidItemDescription"));
}

FIntPoint UDA_InventoryItem::GetSize() const
{
	return Definition ? Definition->Size : FIntPoint(1);
}

FIntPoint UDA_InventoryItem::GetAtlasCoordinates() const
{
	return Definition ? Definition->AtlasCoordinates : FIntPoint(1);
}

float UDA_InventoryItem::GetWeight() const
{
	return Definition ? Definition->Weight : 0.0f;
}

