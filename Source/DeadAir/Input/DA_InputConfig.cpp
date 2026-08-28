// CopyRight © Dead Air Game. All Rights Reserved.


#include "DA_InputConfig.h"

#include "DA_LogChannels.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(DA_InputConfig)

UDA_InputConfig::UDA_InputConfig(const FObjectInitializer& ObjectInitializer)
{
}

const UInputAction* UDA_InputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag, const bool bLogNotFound) const
{
	for (const FDA_InputAction& Action : NativeInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(X_DeadAir, Error, TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}

const UInputAction* UDA_InputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, const bool bLogNotFound) const
{
	for (const FDA_InputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(X_DeadAir, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
