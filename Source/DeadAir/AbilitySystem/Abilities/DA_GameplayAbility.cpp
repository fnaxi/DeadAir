// CopyRight © Dead Air Game. All Rights Reserved.


#include "DA_GameplayAbility.h"

#include "AbilitySystem/DA_AbilitySystemComponent.h"
#include "Player/DA_Character.h"
#include "Player/DA_PlayerController.h"

UDA_AbilitySystemComponent* UDA_GameplayAbility::GetDeadAirAbilitySystemComponentFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<UDA_AbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent.Get()) : nullptr);
}

AController* UDA_GameplayAbility::GetControllerFromActorInfo() const
{
	if (CurrentActorInfo)
	{
		if (AController* PC = CurrentActorInfo->PlayerController.Get())
		{
			return PC;
		}

		// Look for a player controller or pawn in the owner chain.
		AActor* TestActor = CurrentActorInfo->OwnerActor.Get();
		while (TestActor)
		{
			if (AController* C = Cast<AController>(TestActor))
			{
				return C;
			}

			if (APawn* Pawn = Cast<APawn>(TestActor))
			{
				return Pawn->GetController();
			}

			TestActor = TestActor->GetOwner();
		}
	}

	return nullptr;
}

ULocalPlayer* UDA_GameplayAbility::GetLocalPlayerFromActorInfo() const
{
	if (const ADA_PlayerController* PlayerController = GetDeadAirPlayerControllerFromActorInfo())
	{
		return PlayerController->GetLocalPlayer();
	}
	return nullptr;
}

ADA_PlayerController* UDA_GameplayAbility::GetDeadAirPlayerControllerFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<ADA_PlayerController>(CurrentActorInfo->PlayerController.Get()) : nullptr);
}

ADA_Character* UDA_GameplayAbility::GetDeadAirCharacterFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<ADA_Character>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}

