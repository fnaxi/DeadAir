// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DA_GameplayAbility.generated.h"

/**
 * Defines how an ability is meant to activate.
 */
UENUM(BlueprintType)
enum class EDA_AbilityActivationPolicy : uint8
{
	Manual = 0,
	
	// Try to activate the ability when the input is triggered.
	OnInputTriggered,

	// Continually try to activate the ability while the input is active.
	WhileInputActive,

	// Try to activate the ability when an avatar is assigned.
	//@TODO: OnSpawn
};

/**
 * 
 */
UCLASS(MinimalAPI, Abstract)
class UDA_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:	
	UFUNCTION(BlueprintCallable, Category = Ability)
	DEADAIR_API class UDA_AbilitySystemComponent* GetDeadAirAbilitySystemComponentFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = Ability)
	DEADAIR_API AController* GetControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = Ability)
	DEADAIR_API ULocalPlayer* GetLocalPlayerFromActorInfo() const;
	
	UFUNCTION(BlueprintCallable, Category = Ability)
	DEADAIR_API class ADA_PlayerController* GetDeadAirPlayerControllerFromActorInfo() const;

	UFUNCTION(BlueprintCallable, Category = Ability)
	DEADAIR_API class ADA_Character* GetDeadAirCharacterFromActorInfo() const;

	EDA_AbilityActivationPolicy GetActivationPolicy() const { return ActivationPolicy; }

protected:
	/** Defines how this ability is meant to activate. */
	UPROPERTY(EditDefaultsOnly, Category = Ability)
	EDA_AbilityActivationPolicy ActivationPolicy = EDA_AbilityActivationPolicy::Manual;
};
