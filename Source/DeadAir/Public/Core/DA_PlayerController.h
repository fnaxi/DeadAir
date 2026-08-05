// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DA_PlayerController.generated.h"

/**
 * 
 */
UCLASS(PrioritizeCategories = "UserInterface|Input")
class DEADAIR_API ADA_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UserInterface")
	TSubclassOf<class UDA_InventoryWidget> InventoryWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<class UInputMappingContext> MappingContext;
	
	UFUNCTION(BlueprintPure)
	class UDA_InventoryComponent* GetInventoryComponent() const;
	
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TObjectPtr<UDA_InventoryWidget> InventoryWidget;

	void SetUIMode(bool bUIMode);
};
