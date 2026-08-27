// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DA_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS(MinimalAPI, Abstract)
class UDA_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability")
	DEADAIR_API class UDA_AbilitySystemComponent* GetDeadAirAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	DEADAIR_API AController* GetControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	DEADAIR_API ULocalPlayer* GetLocalPlayerFromActorInfo() const;
	
	UFUNCTION(BlueprintCallable, Category = "Ability")
	DEADAIR_API class ADA_PlayerController* GetDeadAirPlayerControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = "Ability")
	DEADAIR_API class ADA_Character* GetDeadAirCharacterFromActorInfo() const;
};
