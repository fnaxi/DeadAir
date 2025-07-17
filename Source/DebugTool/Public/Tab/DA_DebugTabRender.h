// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DA_DebugTabBase.h"
#include "DA_DebugTabRender.generated.h"

/**
 * 
 */
UCLASS()
class DEBUGTOOL_API UDA_DebugTabRender : public UDA_DebugTabBase
{
	GENERATED_BODY()

public:
	// Sets default values
	UDA_DebugTabRender();
	
	virtual void OnInitialize() override;
	virtual void OnDrawToolUI() override;
	virtual void OnDrawOverlay() override;
	virtual void OnGameLogic() override;
	
};
