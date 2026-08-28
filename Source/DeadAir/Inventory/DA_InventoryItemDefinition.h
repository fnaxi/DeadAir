// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DA_InventoryItemDefinition.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class DEADAIR_API UDA_InventoryItemDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = General)
	FText Name;
	
	UPROPERTY(EditDefaultsOnly, Category = General)
	FText Description;

	UPROPERTY(EditDefaultsOnly, Category = General)
	FIntPoint AtlasCoordinates = FIntPoint(1);
	
	/** How big is this item in columns and rows (X=Columns, Y=Rows). */
	UPROPERTY(EditDefaultsOnly, Category = General)
	FIntPoint Size = FIntPoint(1);
	
	UPROPERTY(EditDefaultsOnly, Category = General)
	float Weight = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = General)
	TSubclassOf<class UDA_InventoryItem> ItemClass;

	//@TODO: Fragments
};
