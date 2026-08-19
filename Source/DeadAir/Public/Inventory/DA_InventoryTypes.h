// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "DA_InventoryTypes.generated.h"

class UDA_InventoryItem;

USTRUCT(BlueprintType)
struct FDA_InventorySlot
{
	GENERATED_BODY()

	FDA_InventorySlot() = default;
	FDA_InventorySlot(UDA_InventoryItem* InItem, const int32 InQuantity)
	{
		Item = InItem;
		Quantity = InQuantity;
	}

	/*FDA_InventorySlot(const FDA_InventorySlot& Other)
	{
		Item = Other.Item;
		Quantity = Other.Quantity;
	}*/

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UDA_InventoryItem> Item;

	UPROPERTY(BlueprintReadOnly)
	int32 Quantity = 0;

	bool operator==(const FDA_InventorySlot& Other) const
	{
		return Item == Other.Item && Quantity == Other.Quantity;
	}
};

DECLARE_MULTICAST_DELEGATE(FDA_OnInventoryUpdatedSignature)
