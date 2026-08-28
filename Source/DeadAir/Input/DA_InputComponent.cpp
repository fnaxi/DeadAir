// CopyRight © Dead Air Game. All Rights Reserved.


#include "DA_InputComponent.h"

#include "EnhancedInputSubsystems.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(DA_InputComponent)

class UDA_InputConfig;

UDA_InputComponent::UDA_InputComponent(const FObjectInitializer& ObjectInitializer)
{
}

void UDA_InputComponent::AddInputMappings(const UDA_InputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	// Here you can handle any custom logic to add something from your input config if required

	if (InputConfig->MappingContext)
	{
		InputSubsystem->AddMappingContext(InputConfig->MappingContext, 0);
	}
}

void UDA_InputComponent::RemoveInputMappings(const UDA_InputConfig* InputConfig, UEnhancedInputLocalPlayerSubsystem* InputSubsystem) const
{
	check(InputConfig);
	check(InputSubsystem);

	// Here you can handle any custom logic to remove input mappings that you may have added above
}

void UDA_InputComponent::RemoveBinds(TArray<uint32>& BindHandles)
{
	for (const uint32 Handle : BindHandles)
	{
		RemoveBindingByHandle(Handle);
	}
	BindHandles.Reset();
}

