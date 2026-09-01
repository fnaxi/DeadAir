// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DA_WeaponBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDA_OnShootSignature);

/**
 * 
 */
UCLASS(Abstract)
class DEADAIR_API ADA_WeaponBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADA_WeaponBase();

	UPROPERTY(BlueprintAssignable)
	FDA_OnShootSignature OnShoot;
	
	UFUNCTION(BlueprintCallable)
	void StartFire();

	UFUNCTION(BlueprintCallable)
	void StopFire();
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsFiring() const { return bFireInProgress; }
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<USkeletalMeshComponent> Mesh;
	
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	FName MuzzleSocketName = TEXT("s_muzzle");
	
	UPROPERTY(EditDefaultsOnly, Category = Weapon, meta=(ClampMin = 200, ClampMax = 1200))
	int32 RoundsPerMinute = 625;
	
	UPROPERTY(EditDefaultsOnly, Category = Weapon, meta=(ClampMin = 1000, ClampMax = 10000))
	float MaxShootDistance = 3000.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = Weapon, meta=(ClampMin = 1, ClampMax = 2.5))
	float BulletSpread = 1.25f;

	//@TODO: WeaponDefinition
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void MakeShoot();
	void MakeHit(FHitResult& OutHitResult, const FVector& OutTraceStart, const FVector& OutTraceEnd);
	
	/** Get info about start and end locations of the shoot trace. */
	virtual bool GetTraceData(FVector& OutTraceStart, FVector& OutTraceEnd) const;
	
	/** Get a player controller that holds this weapon. */
	APlayerController* GetPlayerController() const;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	FTimerHandle ShootTimerHandle;
	bool bFireInProgress;

	void ResetAddons();
};
