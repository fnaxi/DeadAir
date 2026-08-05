// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DA_InventoryComponent.h"
#include "DA_InventoryItem.generated.h"

DECLARE_MULTICAST_DELEGATE(FDA_OnItemRotatedSignature) // TODO(DA): Remove rotation support

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, PrioritizeCategories="Item")
class DEADAIR_API UDA_InventoryItem : public UObject
{
	GENERATED_BODY()

public:
	UDA_InventoryItem(const FObjectInitializer& ObjectInitializer);

	/** Called when we create an instance of a UItem. @see UDA_InventoryComponent::CreateItem() */
	void OnConstruct();

	/** Stores the first cell coordinates (top-left cell of our item) where we stored this item in the grid. */
	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetStartCoordinates(const FDA_Point2D& Coordinates);

	/** How big is this item in columns and rows (X=Columns, Y=Rows). */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	FDA_Point2D Size;
	
	UFUNCTION(BlueprintPure, Category = "Item")
	FORCEINLINE FDA_Point2D const& GetStartCoordinates() { return StartCoordinates; }

	UFUNCTION(BlueprintPure, Category = "Item")
	FORCEINLINE TArray<FDA_Point2D> const& GetSizeInCells() { return SizeInCells; }

	/**
	 * Calculates how many cells are needed to store this item based on Size.
	 * 
	 * @return An array of cell(s) coordinates relative to StartCoordinates.
	 */
	UFUNCTION(BlueprintPure, Category = "Item")
	TArray<FDA_Point2D> CalculateItemSize();

	/**
	 * Checks whether we can rotate this item.
	 * @return true, if we can rotate this item.
	 * 
	 * @note Currently only rectangle-shaped items can be rotated.
	 */
	UFUNCTION(BlueprintPure, Category = "Item")
	bool CanRotate();

	/** Rotates the item (inverts Size and SizeInCells coordinates). Use cached values to undo this. */
	UFUNCTION(BlueprintCallable, Category = "Item")
	void Rotate();

	UFUNCTION(BlueprintPure, Category = "Item")
	UDA_InventoryComponent* GetOwnerInventory() const
	{
		return OwnerInventory;
	}

	UFUNCTION(BlueprintCallable, Category = "Item")
	void SetOwningInventory(UDA_InventoryComponent* NewInventory);

	/** Notifies all listeners that the item has been rotated. */
	UFUNCTION(BlueprintCallable, Category = "Item")
	void HandleItemRotation();

	/** Called whenever an item is rotated. */
	FDA_OnItemRotatedSignature OnItemRotated;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item")
	int32 UniqueId; // TODO(DA): FGuid

private:
	/** First grid cell (Top-left corner of our item) coordinates where we found an empty space that can fit this item. */
	FDA_Point2D StartCoordinates;

	/** All grid cells coordinates used to store this item. */
	TArray<FDA_Point2D> SizeInCells;

	/** These hold default data before rotating the item. */
	FDA_Point2D CachedSize;
	TArray<FDA_Point2D> CachedSizeInCells;

	/** Whether the item is currently rotated. */
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item")
	uint8 bIsRotated : 1;

	/** Item's owning inventory component reference. */
	UPROPERTY(Transient, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Item")
	UDA_InventoryComponent* OwnerInventory; // TODO(DA): Remove private access
};
