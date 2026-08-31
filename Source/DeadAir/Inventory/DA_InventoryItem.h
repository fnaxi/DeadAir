// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DA_InventoryComponent.h"
#include "DA_InventoryItem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class DEADAIR_API UDA_InventoryItem : public UObject
{
	GENERATED_BODY()

public:
	UDA_InventoryItem(const FObjectInitializer& ObjectInitializer);

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

	FIntPoint GetCoordinatesFromHover(const FIntPoint& HoveredCoordinates) const;
	FORCEINLINE const FIntPoint& GetStartCoordinates() const { return StartCoordinates; }

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
	TObjectPtr<UDA_InventoryItemDefinition> Definition;
	
	/** First grid cell (top-left corner of the item) coordinates where an empty space that can fit this item was found. */
	FIntPoint StartCoordinates;
};
