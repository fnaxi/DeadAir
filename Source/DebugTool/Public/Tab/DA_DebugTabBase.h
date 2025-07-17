// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DA_DebugTabBase.generated.h"

/**
 * 
 */
UCLASS()
class DEBUGTOOL_API UDA_DebugTabBase : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values
	UDA_DebugTabBase();

	virtual void OnInitialize();
	virtual void OnDrawToolUI();
	virtual void OnDrawOverlay();
	virtual void OnGameLogic();

	FORCEINLINE bool IsOverlayEnabled() const { return bOverlayEnabled; };
	FORCEINLINE FString GetTabName() const { return TabName; };

protected:
	FString TabName = TEXT("GenericTab");
	
private:
	bool bOverlayEnabled = false;
	
};
