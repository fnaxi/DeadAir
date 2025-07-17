// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DA_MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API ADA_MainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	// Sets default values
	ADA_MainMenuGameMode();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
