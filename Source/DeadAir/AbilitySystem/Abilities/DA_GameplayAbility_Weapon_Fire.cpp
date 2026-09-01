// CopyRight © Dead Air Game. All Rights Reserved.


#include "DA_GameplayAbility_Weapon_Fire.h"

#include "Player/DA_Character.h"
#include "Weapon/DA_WeaponBase.h"

UDA_GameplayAbility_Weapon_Fire::UDA_GameplayAbility_Weapon_Fire()
{
	ActivationPolicy = EDA_AbilityActivationPolicy::OnInputTriggered;
}

void UDA_GameplayAbility_Weapon_Fire::InputReleased(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo)
{
	Super::InputReleased(Handle, ActorInfo, ActivationInfo);

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}

void UDA_GameplayAbility_Weapon_Fire::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                                            const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	if (const ADA_Character* Character = GetDeadAirCharacterFromActorInfo())
	{
		if (ADA_WeaponBase* Weapon = Character->Weapon)
		{
			Weapon->StartFire();
		}
	}
}

void UDA_GameplayAbility_Weapon_Fire::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (const ADA_Character* Character = GetDeadAirCharacterFromActorInfo())
    {
		if (ADA_WeaponBase* Weapon = Character->Weapon)
		{
			Weapon->StopFire();
		}
    }
}

