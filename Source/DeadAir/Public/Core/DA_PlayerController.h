// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DA_PlayerController.generated.h"

class UDA_InventoryComponent;

/**
 * 
 */
UCLASS()
class DEADAIR_API ADA_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(exec)
	void XPrintInventory();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "UserInterface")
	TSubclassOf<class UDA_InventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> MappingContext;

	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<UDA_InventoryComponent> InventoryComponent;
	
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TObjectPtr<UDA_InventoryWidget> InventoryWidget;
	
	void SetUIMode(bool bUIMode);
};
