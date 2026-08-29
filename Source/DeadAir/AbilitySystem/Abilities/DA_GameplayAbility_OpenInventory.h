// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DA_GameplayAbility.h"
#include "DA_GameplayAbility_OpenInventory.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class DEADAIR_API UDA_GameplayAbility_OpenInventory : public UDA_GameplayAbility
{
	GENERATED_BODY()

public:
	UDA_GameplayAbility_OpenInventory();

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDA_InventoryWidget> InventoryWidgetClass;

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	                             const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	UPROPERTY()
	TObjectPtr<class UCommonActivatableWidget> InventoryWidget;

	UFUNCTION()
	void OnInventoryWidgetClosed();
};
