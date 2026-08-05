// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DA_InventoryTypes.h"
#include "Components/ActorComponent.h"
#include "DA_InventoryComponent.generated.h"

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

	/** How big is this grid in columns and rows (X=Columns, Y=Rows). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	FDA_Point2D GridSize;

	/** Size of the cell in pixels. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float CellSize;

	/** Holds all grid cells coordinates. */
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	TArray<FDA_Point2D> Cells;

	/** Holds our stored items and their grid coordinates. */
	UPROPERTY(BlueprintReadOnly, Category = "Grid")
	TArray<FDA_InventorySlot> Slots;

	/** Called when inventory changes (item added, removed, moved, etc.). */
	FOnInventoryUpdatedSignature OnInventoryUpdated;

	/** Initializes inventory cells basing on grid size. */
	UFUNCTION(BlueprintCallable, Category = "Grid")
	void Initialize();

	/**
	 * Checks whether the specified coordinates are inside the grid.
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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
