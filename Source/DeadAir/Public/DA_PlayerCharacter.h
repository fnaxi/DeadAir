// CopyRight Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "DA_PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class DEADAIR_API ADA_PlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADA_PlayerCharacter(const FObjectInitializer& ObjInit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	/** First-person camera. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UCameraComponent> Camera;
	
	/** Hands mesh for first-person view. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> HUDHands;

	/** Weapon mesh to attach to camera in first-person view. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USkeletalMeshComponent> HUDGun;
	
	/** Weapon mesh to attach to camera in first-person view. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UDA_InventoryComponent> InventoryComponent;

	/** Socket to attach a weapon to inside the HUDHands mesh. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName GunSocketName = TEXT("GunSocket");
	
	/** Weapon bone names. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName ScopeBoneName = TEXT("wpn_scope");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName SilencerBoneName = TEXT("wpn_silencer");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName GrenadeLauncherBoneName = TEXT("wpn_launcher");
	
	/** Input mapping context. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputMappingContext> MappingContext;

	/** Input axis for the movement. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<class UInputAction> MoveInputAction;
	
	/** Input axis for camera look. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> LookInputAction;

	/** Input action for jump. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> JumpInputAction;
	
	/** Input action for crouch. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> CrouchInputAction;
	
	/** Input action for sprint. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	TObjectPtr<UInputAction> SprintInputAction;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	/** Is character sprinting or no. */
	UFUNCTION(BlueprintCallable, Category = "Movement")
	bool IsSprinting() const;

	/**
	 * Enable no clip mode for the character. Disables any collision and enables fly mode.
	 * @param InFlySpeed The speed with which character will fly around. Useful when exploring big maps.
	 */
	UFUNCTION(Exec)
	void XNoClip(float InFlySpeed = 1000.0f);
	
private:
	/** Move the character. */
	void Move(const FInputActionValue& InputValue);
#if !UE_BUILD_SHIPPING
	void StopMove(const FInputActionValue& InputValue);
#endif
	
	/** Look around using the camera. */
	void Look(const FInputActionValue& InputValue);

	/** Call to start or stop crouching. */
	void StartCrouch(const FInputActionValue& InputValue);
	void StopCrouch(const FInputActionValue& InputValue);

	/** Call to start or stop running. */
	void StartSprinting();
	void StopSprinting();

	/** Is character moving forward or no? */
	bool bIsMovingForward = false;
	
	/** Is character wants to run. */
	bool bWantsToSprint = false;

#if !UE_BUILD_SHIPPING
	/** Is no clip mode enabled (flying with no collision). */
	bool bNoClip = false;
	
	/** Handles movement in no clip mode. */
	void StartFlyUp(const FInputActionValue& InputValue) { bFlyMoveUp = true; }
	void StopFlyUp(const FInputActionValue& InputValue) { bFlyMoveUp = false; }
	bool bFlyMoveUp = false;
	
	void StartFlyDown(const FInputActionValue& InputValue) { bFlyMoveDown = true; }
	void StopFlyDown(const FInputActionValue& InputValue) { bFlyMoveDown = false; }
	bool bFlyMoveDown = false;

	/** Cache the movement input. */
	FVector2D FlyMoveInput = FVector2D::ZeroVector;
#endif
	
};
