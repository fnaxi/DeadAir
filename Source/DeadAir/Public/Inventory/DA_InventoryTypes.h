// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "DA_InventoryTypes.generated.h"

class UDA_InventoryItem;

USTRUCT(BlueprintType)
struct FDA_Point2D // TODO(DA): FDA_InventoryCoordinate?
{
	GENERATED_BODY()

	FDA_Point2D()
	{
		X = 0;
		Y = 0;
	}

	FDA_Point2D(const int32 InX, const int32 InY)
	{
		X = InX;
		Y = InY;
	}

	FDA_Point2D(const FDA_Point2D& Other)
	{
		X = Other.X;
		Y = Other.Y;
	}

	// TODO(DA): does this really need to have EditAnywhere and BlueprintReadWrite
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0))
	int32 Y;

	bool operator==(const FDA_Point2D& Other) const
	{
		return (X == Other.X && Y == Other.Y);
	}

	FDA_Point2D operator+(const FDA_Point2D& Other) const
	{
		return FDA_Point2D(X + Other.X, Y + Other.Y);
	}

	bool IsValid() const
	{
		return X >= 0 && Y >= 0; 
	}

	// TODO(DA): make invalid constant
};

USTRUCT(BlueprintType)
struct FDA_InventorySlot
{
	GENERATED_BODY()

	FDA_InventorySlot()
	{
		Item = nullptr;
		Quantity = 0;
	}

	FDA_InventorySlot(UDA_InventoryItem* InItem, const int32 InQuantity)
	{
		Item = InItem;
		Quantity = InQuantity;
	}

	FDA_InventorySlot(const FDA_InventorySlot& Other)
	{
		Item = Other.Item;
		Quantity = Other.Quantity;
	}

	UPROPERTY(BlueprintReadOnly)
	UDA_InventoryItem* Item;

	UPROPERTY(BlueprintReadOnly)
	int32 Quantity;

	bool operator==(const FDA_InventorySlot& Other) const
	{
		return Item == Other.Item && Quantity == Other.Quantity;
	}
};

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdatedSignature)
