// CopyRight © Dead Air Game. All Rights Reserved.


#include "DA_AbilityTask_PushWidget.h"

#include "CommonActivatableWidget.h"
#include "CommonUIExtensions.h"

UDA_AbilityTask_PushWidget* UDA_AbilityTask_PushWidget::PushWidget(UGameplayAbility* OwningAbility, ULocalPlayer* InLocalPlayer, FGameplayTag InLayer,
                                                                   TSubclassOf<UCommonActivatableWidget> InWidgetClass)
{
	UDA_AbilityTask_PushWidget* Ability = NewAbilityTask<UDA_AbilityTask_PushWidget>(OwningAbility);
	Ability->LocalPlayer = InLocalPlayer;
	Ability->Layer = InLayer;
	Ability->WidgetClass = InWidgetClass;
	return Ability;
}

void UDA_AbilityTask_PushWidget::Activate()
{
	Super::Activate();
	
	Widget = UCommonUIExtensions::PushContentToLayer_ForPlayer(LocalPlayer, Layer, WidgetClass);
	if (Widget)
	{
		Widget->OnDeactivated().AddUObject(this, &ThisClass::HandleWidgetDeactivated);
	}
	else
	{
		HandleWidgetDeactivated();
	}
}

void UDA_AbilityTask_PushWidget::OnDestroy(bool bInOwnerFinished)
{
	if (Widget)
	{
		Widget->OnDeactivated().RemoveAll(this);
	}
	Super::OnDestroy(bInOwnerFinished);
}

void UDA_AbilityTask_PushWidget::HandleWidgetDeactivated()
{
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnWidgetClosed.Broadcast();
	}

	EndTask();
}

