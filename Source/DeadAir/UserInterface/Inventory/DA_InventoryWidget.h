// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "DA_InventoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_InventoryWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

public:
	virtual TOptional<FUIInputConfig> GetDesiredInputConfig() const override;

protected:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UDA_InventoryGridWidget> Grid;
};
