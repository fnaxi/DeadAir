// CopyRight © Dead Air Game. All Rights Reserved.


#include "DA_GameplayAbility_OpenInventory.h"

#include "DA_GameplayTags.h"
#include "DA_MiscUtils.h"
#include "AbilitySystem/Tasks/DA_AbilityTask_PushWidget.h"
#include "UserInterface/Inventory/DA_InventoryWidget.h"

UDA_GameplayAbility_OpenInventory::UDA_GameplayAbility_OpenInventory()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	ActivationPolicy = EDA_AbilityActivationPolicy::OnInputTriggered;
}

void UDA_GameplayAbility_OpenInventory::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                        const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (ULocalPlayer* LocalPlayer = GetLocalPlayerFromActorInfo())
	{
		ENSURE_KISMET(InventoryWidgetClass)
		if (UDA_AbilityTask_PushWidget* PushInventory = UDA_AbilityTask_PushWidget::PushWidget(this, LocalPlayer, DeadAirGameplayTags::Layer_GameMenu, InventoryWidgetClass))
		{
			PushInventory->OnWidgetClosed.AddDynamic(this, &ThisClass::OnInventoryWidgetClosed);

			PushInventory->ReadyForActivation();
		}
	}
}

void UDA_GameplayAbility_OpenInventory::OnInventoryWidgetClosed()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false, false);
}

