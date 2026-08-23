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
	UDA_InventoryItem(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) { }
	
	/** Called whenever an item is rotated. */
	FDA_OnItemRotatedSignature OnItemRotated;

	UFUNCTION(BlueprintPure)
	UDA_InventoryComponent* GetOwnerInventory() const { return OwnerInventory.Get(); }

	void SetOwningInventory(UDA_InventoryComponent* InInventory);

	void SetDefinition(UDA_InventoryItemDefinition* InDefinition);
	
	/** Stores the first cell coordinates (top-left cell of our item) where we stored this item in the grid. */
	void SetStartCoordinates(const FIntPoint& Coordinates);

	/**
	 * Calculates how many cells are needed to store this item based on Size.
	 *
	 * @return An array of cell(s) coordinates relative to StartCoordinates.
	 */
	TArray<FIntPoint> GetSizeInCells() const;

	/** Rotates the item (inverts Size and SizeInCells coordinates). Use cached values to undo this. */
	// void Rotate();

	/** Notifies all listeners that the item has been rotated. */
	// void HandleItemRotation();

	FIntPoint GetCoordinatesFromHover(const FIntPoint& HoveredCoordinates) const;
	
	FORCEINLINE const FIntPoint& GetStartCoordinates() const { return StartCoordinates; }
	FORCEINLINE FGuid GetItemID() const { return UID; }

	FText		GetItemName()			const;
	FText		GetItemDescription()	const;
	FIntPoint	GetSize()				const;
	FIntPoint	GetAtlasCoordinates()	const;
	float		GetWeight()				const;
	
private:
	/** Item's owning inventory component reference. */
	UPROPERTY()
	TWeakObjectPtr<UDA_InventoryComponent> OwnerInventory;

	UPROPERTY()
	TObjectPtr<class UDA_InventoryItemDefinition> Definition;
	
	/** First grid cell (top-left corner of the item) coordinates where an empty space that can fit this item was found. */
	FIntPoint StartCoordinates;
	
	/** Whether the item is currently rotated. */
	bool bIsRotated = false;
	
	FGuid UID = FGuid::NewGuid();
};
