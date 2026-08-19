// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DA_InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_InventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetInventory(class UDA_InventoryComponent* Inventory) const;
	
protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UDA_InventoryGridWidget> Grid;
};
