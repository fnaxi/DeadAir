// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DA_AbilitySet.generated.h"

struct FGameplayAbilitySpecHandle;
struct FActiveGameplayEffectHandle;
class UAttributeSet;
class UGameplayEffect;

/**
 * Data used by the ability set to grant gameplay abilities.
 */
USTRUCT(BlueprintType)
struct FDA_AbilitySet_GameplayAbility
{
	GENERATED_BODY()

	/** Gameplay ability to grant. */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UDA_GameplayAbility> Ability = nullptr;

	/** Level of ability to grant. */
	UPROPERTY(EditDefaultsOnly)
	int32 AbilityLevel = 1;

	/** Tag used to process input for the ability. */
	UPROPERTY(EditDefaultsOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag; //@TODO: does not work for now
};

/**
 * Data used by the ability set to grant gameplay effects.
 */
USTRUCT(BlueprintType)
struct FDA_AbilitySet_GameplayEffect
{
	GENERATED_BODY()

	/** Gameplay effect to grant. */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> GameplayEffect = nullptr;

	// Level of gameplay effect to grant.
	UPROPERTY(EditDefaultsOnly)
	float EffectLevel = 1.0f;
};

/**
 * Data used by the ability set to grant attribute sets.
 */
USTRUCT(BlueprintType)
struct FDA_AbilitySet_AttributeSet
{
	GENERATED_BODY()

	/** Gameplay effect to grant. */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAttributeSet> AttributeSet;
};


/**
 * Data used to store handles to what has been granted by the ability set.
 */
USTRUCT(BlueprintType)
struct FDA_AbilitySet_GrantedHandles
{
	GENERATED_BODY()

public:
	void AddAbilitySpecHandle(const FGameplayAbilitySpecHandle& Handle);
	void AddGameplayEffectHandle(const FActiveGameplayEffectHandle& Handle);
	void AddAttributeSet(UAttributeSet* Set);

	void TakeFromAbilitySystem(class UDA_AbilitySystemComponent* AbilitySystem);

protected:
	/** Handles to the granted abilities. */
	UPROPERTY()
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;

	/** Handles to the granted gameplay effects. */
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> GameplayEffectHandles;

	/** Pointers to the granted attribute sets. */
	UPROPERTY()
	TArray<TObjectPtr<UAttributeSet>> GrantedAttributeSets;
};

/**
 * Non-mutable data asset used to grant gameplay abilities and gameplay effects.
 */
UCLASS(BlueprintType, Const)
class DEADAIR_API UDA_AbilitySet : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UDA_AbilitySet(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()) : Super(ObjectInitializer) { }

	/**
	 * Grants the ability set to the specified ability system component.
	 * The returned handles can be used later to take away anything that was granted.
	 */
	void GiveToAbilitySystem(UDA_AbilitySystemComponent* AbilitySystem, FDA_AbilitySet_GrantedHandles* OutGrantedHandles, UObject* SourceObject = nullptr) const;

protected:
	/** Gameplay abilities to grant when this ability set is granted. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Abilities", meta=(TitleProperty=Ability))
	TArray<FDA_AbilitySet_GameplayAbility> GrantedGameplayAbilities;

	/** Gameplay effects to grant when this ability set is granted. */
	UPROPERTY(EditDefaultsOnly, Category = "Gameplay Effects", meta=(TitleProperty=GameplayEffect))
	TArray<FDA_AbilitySet_GameplayEffect> GrantedGameplayEffects;

	/** Attribute sets to grant when this ability set is granted. */
	UPROPERTY(EditDefaultsOnly, Category = "Attribute Sets", meta=(TitleProperty=AttributeSet))
	TArray<FDA_AbilitySet_AttributeSet> GrantedAttributes;
};
