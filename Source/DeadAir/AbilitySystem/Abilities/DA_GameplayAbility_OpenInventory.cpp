// CopyRight © Dead Air Game. All Rights Reserved.


#include "DA_GameplayAbility_OpenInventory.h"

#include "CommonUIExtensions.h"
#include "DA_GameplayTags.h"
#include "DA_MiscUtils.h"
#include "Player/DA_PlayerController.h"
#include "UserInterface/Inventory/DA_InventoryWidget.h"

UDA_GameplayAbility_OpenInventory::UDA_GameplayAbility_OpenInventory()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UDA_GameplayAbility_OpenInventory::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                          const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	//@TODO: Move to ADA_PlayerController
	if (const ULocalPlayer* LocalPlayer = GetLocalPlayerFromActorInfo())
	{
		ENSURE_KISMET(InventoryWidgetClass)
		UCommonUIExtensions::PushContentToLayer_ForPlayer(LocalPlayer, DeadAirGameplayTags::Layer_GameMenu, InventoryWidgetClass);
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
