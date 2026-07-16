// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DA_InventoryComponent.generated.h"

class UDA_InventoryItem;

USTRUCT(BlueprintType)
struct FDA_Point2D
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
	int32 X;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, UIMin = 0))
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

DECLARE_MULTICAST_DELEGATE(FOnInventoryUpdatedSignature);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEADAIR_API UDA_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDA_InventoryComponent();
	UDA_InventoryComponent(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	/** How big is this grid in columns and rows (X=Columns, Y=Rows). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FDA_Point2D GridSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float CellSize;

	/** Holds all grid cells coordinates. */
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	TArray<FDA_Point2D> Cells;

	/** Holds our stored items and their grid coordinates. */
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	TArray<FDA_InventorySlot> Slots;

	/** Called when inventory changes (item added, removed, moved, etc..). */
	FOnInventoryUpdatedSignature OnInventoryUpdated;


	UFUNCTION(BlueprintCallable, Category = "Grid")
	void Initialize();

	/**
	 * kChecks whether the specified coordinates are inside the grid.
	 *
	 * @param	Coordinates		Grid cell coordinates.
	 *
	 * @return True, if the coordinates are inside the grid.
	 */
	UFUNCTION(BlueprintPure, Category = "Grid")
	bool IsWithinBoundaries(const FDA_Point2D& Coordinates);

	/**
	 * Checks whether a specific grid cell is free to use.
	 *
	 * @param	Coordinates		Grid cell coordinates.
	 *
	 * @return True, if the grid cell is free to use.
	 */
	UFUNCTION(BlueprintPure, Category = "Grid")
	bool IsFree(const FDA_Point2D& Coordinates);

	/**
	 * Checks whether we can fit an item on a specific grid cell coordinates.
	 *
	 * @param	SizeInCells		Item size we are trying to fit.
	 * @param	Coordinates		Grid cell coordinates.
	 *
	 * @return True, if we can fit that item on the specified grid cell coordinates.
	 */
	UFUNCTION(BlueprintPure, Category = "Slot")
	bool DoesItemFit(TArray<FDA_Point2D> const& SizeInCells, const FDA_Point2D& Coordinates);

	/**
	 * Searches for a free (unused) grid cell.
	 *
	 * @return Free cell coordinates on the grid. (-1, -1) if none found.
	 */
	UFUNCTION(BlueprintPure, Category = "Slot")
	FDA_Point2D GetFreeCell();

	/**
	 * Searches for a free grid cell where we can fit a specific item.
	 *
	 * @param	SizeInCells		Item size we are trying to fit.
	 *
	 * @return Cell coordinates where we can fit that item on the grid. (-1, -1) if none found.
	 */
	UFUNCTION(BlueprintPure, Category = "Slot")
	FDA_Point2D GetFreeCellThatFitsItem(TArray<FDA_Point2D> const& SizeInCells);

	/**
	 * Adds a new item instance to the inventory.
	 * @note Automatically tries to rotate the item if it doesn't fit.
	 *
	 * @param	ItemClass		Item class we are trying to add/instantiate.
	 * @param	Quantity		Quantity to add.
	 *
	 * @return True, if the item is added to the inventory. False otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool AddItem(TSubclassOf<UDA_InventoryItem> ItemClass, int32 Quantity);
	
	/**
	 * Removes an existing item instance from the inventory.
	 *
	 * @param	UniqueId		Item UniqueId we are trying to remove.
	 * @param	Quantity		Quantity to remove.
	 *
	 * @return True, if the item is removed from the inventory. False otherwise.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	bool RemoveItem(int32 UniqueId, int32 Quantity);

	/**
	 * Moves an existing item from to the specified grid coordinates.
	 *
	 * @param	Slot			Source slot data.
	 * @param	Destination		Destination grid cell coordinates.
	 */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void MoveItem(const FDA_InventorySlot& Slot, const FDA_Point2D& Destination);

	/** Notifies all listeners that the inventory has been updated. */
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void HandleInventoryUpdate();

private:
	/**
	 * Creates an item instance from the specified item class.
	 *
	 * @param	ItemClass		Item class to instantiate.
	 *
	 * @return a UItem instance of the specified class. nullptr otherwise.
	 */
	UDA_InventoryItem* CreateItem(TSubclassOf<UDA_InventoryItem> ItemClass);
};
