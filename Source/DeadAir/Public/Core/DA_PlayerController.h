// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DA_PlayerController.generated.h"

/**
 * 
 */
UCLASS(PrioritizeCategories = "DeadAir")
class DEADAIR_API ADA_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="DeadAir")
	TSubclassOf<class UDA_InventoryWidget> InventoryWidgetClass;

	UFUNCTION(BlueprintPure)
	class UDA_InventoryComponent* GetInventoryComponent() const;
	
	virtual void BeginPlay() override;
	
private:
	UPROPERTY()
	TObjectPtr<UDA_InventoryWidget> InventoryWidget;

	void SetUIMode(bool bUIMode);
};
