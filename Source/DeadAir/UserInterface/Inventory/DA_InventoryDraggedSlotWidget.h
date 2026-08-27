// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DA_InventorySlotWidgetBase.h"
#include "DA_InventoryDraggedSlotWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEADAIR_API UDA_InventoryDraggedSlotWidget : public UDA_InventorySlotWidgetBase
{
	GENERATED_BODY()

	void OnItemRotated();
};
