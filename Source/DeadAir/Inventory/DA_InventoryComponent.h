// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DA_InventoryComponent.generated.h"

class UDA_InventoryItem;
class UDA_InventoryItemDefinition;

DECLARE_MULTICAST_DELEGATE(FDA_OnInventoryUpdatedSignature)

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DEADAIR_API UDA_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values
	UDA_InventoryComponent();

	/** Called when inventory changes (item added, removed, moved, etc.). */
	FDA_OnInventoryUpdatedSignature OnInventoryUpdated;

	/** Initializes inventory cells basing on grid size. */
	void Initialize();
	
	/**
	 * Checks whether the specified coordinates are inside the grid.
	 *
	 * @param	Coordinates		Grid cell coordinates.
	 * @return True, if the coordinates are inside the grid.
	 */
	bool IsWithinBoundaries(const FIntPoint& Coordinates) const;

	/**
	 * Checks whether a specific grid cell is free to use.
	 *
	 * @param	Coordinates		Grid cell coordinates.
	 * @param	ItemToIgnore	Optional item to ignore (usually the item being drag&dropped).
	 * @return True, if the grid cell is free to use.
	 */
	bool IsFree(const FIntPoint& Coordinates, const UDA_InventoryItem* ItemToIgnore = nullptr) const;

	/**
	 * Checks whether we can fit an item on a specific grid cell coordinates.
	 *
	 * @param	SizeInCells		Item size we are trying to fit.
	 * @param	Coordinates		Grid cell coordinates.
	 * @param	ItemToIgnore	Optional item to ignore (usually the item being drag&dropped).
	 * @return True, if we can fit that item on the specified grid cell coordinates.
	 */
	bool DoesItemFit(TArray<FIntPoint> const& SizeInCells, const FIntPoint& Coordinates, const UDA_InventoryItem* ItemToIgnore = nullptr) const;

	/**
	 * Searches for a free (unused) grid cell.
	 *
	 * @return Free cell coordinates on the grid. (-1, -1) if none found.
	 */
	FIntPoint GetFreeCell();

	/**
	 * Searches for a free grid cell where we can fit a specific item.
	 *
	 * @param	SizeInCells		Item size we are trying to fit.
	 *
	 * @return Cell coordinates where we can fit that item on the grid. (-1, -1) if none found.
	 */
	FIntPoint GetFreeCellThatFitsItem(TArray<FIntPoint> const& SizeInCells);

	//@TODO: FindItemAtCoordinates

	/**
	 * Adds an item instance to the inventory.
	 *
	 * @param	Item			Item to add to the inventory.
	 * @return True, if the item is added to the inventory. False otherwise.
	 */
	bool AddItem(UDA_InventoryItem* Item);

	/**
	 * Adds an item to the inventory using a name of the data asset.
	 * @param	ItemName		Name of the data asset.
	 */
	void AddNewItemByName(const FString& ItemName); //@TODO: Quantity
	
	/**
	 * Adds a new item instance to the inventory.
	 *
	 * @param	Definition		Data asset of the item.
	 * @param	Quantity		Quantity to add.
	 * @return True, if the item is added to the inventory. False otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	bool AddNewItem(UDA_InventoryItemDefinition* Definition, int32 Quantity = 1);
	
	/**
	 * Removes an existing item instance from the inventory.
	 *
	 * @param	Item			Item UniqueId we are trying to remove.
	 * @return True, if the item is removed from the inventory. False otherwise.
	 */
	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UDA_InventoryItem* Item);
	
	/**
	 * Moves an existing item from to the specified grid coordinates.
	 *
	 * @param	InItem			Source slot data.
	 * @param	Destination		Destination grid cell coordinates.
	 * @return True, if the item can be moved to destination. False otherwise.
	 */
	bool MoveItem(const UDA_InventoryItem* InItem, const FIntPoint& Destination);

	/** Notifies all listeners that the inventory has been updated. */
	void NotifyInventoryUpdated();

	FORCEINLINE TArray<FIntPoint> GetCells() const { return Cells; }
	FORCEINLINE TArray<UDA_InventoryItem*> GetItems() const { return Items; }

	FORCEINLINE FIntPoint GetGridSize() const { return GridSize; }
	FORCEINLINE float GetCellSize() const { return CellSize; }

protected:
	/** How big is this grid in columns and rows (X=Columns, Y=Rows). */
	UPROPERTY(EditDefaultsOnly)
	FIntPoint GridSize = FIntPoint(10, 10);

	/** Size of the cell in pixels. */
	UPROPERTY(EditDefaultsOnly)
	float CellSize = 70.f;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	/** Holds all grid cells coordinates. */
	TArray<FIntPoint> Cells;
	
	/** Holds stored items and their grid coordinates. */
	UPROPERTY()
	TArray< TObjectPtr<UDA_InventoryItem> > Items;
	
	/**
	 * Creates an item instance from the specified item class.
	 *
	 * @param	Definition		Data asset of the item.
	 */
	UDA_InventoryItem* CreateItem(UDA_InventoryItemDefinition* Definition);
};

inline bool AreCoordinatesValid(const FIntPoint Point) { return Point.X >= 0 && Point.Y >= 0; }
