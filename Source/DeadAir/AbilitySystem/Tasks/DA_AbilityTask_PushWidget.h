// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "DA_AbilityTask_PushWidget.generated.h"

class UCommonActivatableWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDA_OnWidgetClosedSignature);

/**
 * 
 */
UCLASS()
class DEADAIR_API UDA_AbilityTask_PushWidget : public UAbilityTask
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FDA_OnWidgetClosedSignature OnWidgetClosed;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UDA_AbilityTask_PushWidget* PushWidget(UGameplayAbility* OwningAbility, ULocalPlayer* InLocalPlayer, FGameplayTag InLayer, TSubclassOf<UCommonActivatableWidget> InWidgetClass);

	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	
private:
	UPROPERTY()
	TObjectPtr<UCommonActivatableWidget> Widget;
	
	UPROPERTY()
	TObjectPtr<ULocalPlayer> LocalPlayer;
	
	UPROPERTY()
	FGameplayTag Layer;
	
	UPROPERTY()
	TSubclassOf<UCommonActivatableWidget> WidgetClass;

	UFUNCTION()
	void HandleWidgetDeactivated();
};
