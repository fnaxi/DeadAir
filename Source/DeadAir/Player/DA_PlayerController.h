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

public:
	void ToggleInventory();
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<class UInputMappingContext> MappingContext;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	TObjectPtr<class UInputAction> InventoryAction;
	
	UPROPERTY(EditDefaultsOnly, Category="UserInterface")
	TSubclassOf<class UDA_InventoryWidget> InventoryWidgetClass;
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY()
	TWeakObjectPtr<class UCommonActivatableWidget> InventoryWidget;
};
