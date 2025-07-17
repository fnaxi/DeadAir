// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DA_DebugTabBase.h"
#include "DA_DebugTabCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEBUGTOOL_API UDA_DebugTabCharacter : public UDA_DebugTabBase
{
	GENERATED_BODY()

public:
	// Sets default values
	UDA_DebugTabCharacter();

	virtual void OnInitialize() override;
	virtual void OnDrawToolUI() override;
	virtual void OnDrawOverlay() override;
	virtual void OnGameLogic() override;
	
};
