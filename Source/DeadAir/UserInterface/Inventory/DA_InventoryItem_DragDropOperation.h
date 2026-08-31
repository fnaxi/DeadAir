// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DA_InventoryItem_DragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_InventoryItem_DragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	// Sets default values
	UDA_InventoryItem_DragDropOperation()
	{
		Pivot = EDragPivot::CenterCenter;
	}
};
