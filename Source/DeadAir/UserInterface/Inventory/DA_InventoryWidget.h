// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UserInterface/DA_ActivatableWidget.h"
#include "DA_InventoryWidget.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEADAIR_API UDA_InventoryWidget : public UDA_ActivatableWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UDA_InventoryGridWidget> Grid;

	UPROPERTY(EditDefaultsOnly)
	FDataTableRowHandle CloseInventoryInputAction;
	
	virtual void NativeOnInitialized() override;
	
private:
	void CloseInventory();
};
