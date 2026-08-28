// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "DA_InputConfig.generated.h"

class UInputAction;
class UObject;
struct FFrame;

/**
 * Struct used to map an input action to a gameplay input tag.
 */
USTRUCT(BlueprintType)
struct FDA_InputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 * Non-mutable data asset that contains input configuration properties.
 */
UCLASS(BlueprintType, Const)
class UDA_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UDA_InputConfig(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = Pawn)
	const UInputAction* FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	UFUNCTION(BlueprintCallable, Category = Pawn)
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	/** Default input mapping context to bind. @see UDA_InputComponent::AddInputMappings */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<class UInputMappingContext> MappingContext;
	
	/**
	 * List of input actions used by the owner.
	 * These input actions are mapped to a gameplay tag and must be manually bound.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FDA_InputAction> NativeInputActions;

	/**
	 * List of input actions used by the owner.
	 * These input actions are mapped to a gameplay tag and are automatically bound to abilities with matching input tags.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FDA_InputAction> AbilityInputActions;
};
