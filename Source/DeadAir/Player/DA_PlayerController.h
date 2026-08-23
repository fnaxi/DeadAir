// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CommonPlayerController.h"
#include "DA_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API ADA_PlayerController : public ACommonPlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> MappingContext;

	UPROPERTY(EditDefaultsOnly, Category = "UserInterface")
	TSubclassOf<class UDA_InventoryWidget> InventoryWidgetClass;
	
	virtual void BeginPlay() override;
	
private:
	void SetUIMode(bool bUIMode);
};
