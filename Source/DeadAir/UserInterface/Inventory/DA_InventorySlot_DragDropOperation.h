// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DA_InventorySlot_DragDropOperation.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_InventorySlot_DragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	// Sets default values
	UDA_InventorySlot_DragDropOperation()
	{
		Pivot = EDragPivot::CenterCenter;
	}
};
