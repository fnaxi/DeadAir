// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DA_InventoryComponent.h"
#include "DA_InventoryItem.generated.h"

DECLARE_MULTICAST_DELEGATE(FDA_OnItemRotatedSignature) // todo: Remove rotation

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DEADAIR_API UDA_InventoryItem : public UObject
{
	GENERATED_BODY()

public:
	UDA_InventoryItem(const FObjectInitializer& ObjectInitializer);

	/** How big is this item in columns and rows (X=Columns, Y=Rows). */
	UPROPERTY(EditDefaultsOnly)
	FIntPoint Size;
	
	/** Called whenever an item is rotated. */
	FDA_OnItemRotatedSignature OnItemRotated;

	UFUNCTION(BlueprintPure)
	UDA_InventoryComponent* GetOwnerInventory() const { return OwnerInventory.Get(); }
	
	/** Called when a new instance of a UDA_InventoryItem is created. @see UDA_InventoryComponent::CreateItem() */
	void OnConstruct();

	/** Stores the first cell coordinates (top-left cell of our item) where we stored this item in the grid. */
	void SetStartCoordinates(const FIntPoint& Coordinates);

	void SetOwningInventory(UDA_InventoryComponent* NewInventory);

	/**
	 * Calculates how many cells are needed to store this item based on Size.
	 *
	 * @return An array of cell(s) coordinates relative to StartCoordinates.
	 */
	TArray<FIntPoint> GetSizeInCells() const;

	/**
	 * Checks whether we can rotate this item.
	 * @return true, if we can rotate this item.
	 * 
	 * @note Currently only rectangle-shaped items can be rotated.
	 */
	bool CanRotate();

	/** Rotates the item (inverts Size and SizeInCells coordinates). Use cached values to undo this. */
	void Rotate();

	/** Notifies all listeners that the item has been rotated. */
	void HandleItemRotation();

	FIntPoint GetCoordinatesFromHover(const FIntPoint& HoveredCoordinates) const;
	
	FORCEINLINE const FIntPoint& GetStartCoordinates() const { return StartCoordinates; }
	// FORCEINLINE const TArray<FIntPoint>& GetSizeInCells() const { return SizeInCells; }
	
	FORCEINLINE FGuid GetItemID() const { return ItemID; }

private:
	/** Item's owning inventory component reference. */
	UPROPERTY()
	TWeakObjectPtr<UDA_InventoryComponent> OwnerInventory;
	
	/** First grid cell (top-left corner of the item) coordinates where an empty space that can fit this item was found. */
	FIntPoint StartCoordinates;
	
	/** All grid cells coordinates used to store this item. */
	// TArray<FIntPoint> SizeInCells; // todo: replace with GetSizeInCells() instead (single source of truth)
	
	FGuid ItemID = FGuid::NewGuid();
	
	/** These hold default data before rotating the item. */
	// FIntPoint CachedSize;
	// TArray<FIntPoint> CachedSizeInCells; // todo: Remove

	/** Whether the item is currently rotated. */
	uint8 bIsRotated : 1;
};
