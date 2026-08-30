// CopyRight © Dead Air Game. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "DA_Character.generated.h"

struct FGameplayTag;
struct FInputActionValue;
class UInputAction;

/**
 * 
 */
UCLASS(Abstract)
class DEADAIR_API ADA_Character : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADA_Character();

	virtual void PostInitializeComponents() override;
	
	UFUNCTION(BlueprintCallable)
	class UDA_AbilitySystemComponent* GetDeadAirAbilitySystemComponent() const { return AbilitySystemComponent; }
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<class UCameraComponent> Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<USkeletalMeshComponent> Hand;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<class UDA_InventoryComponent> InventoryComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components)
	TObjectPtr<UDA_AbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(EditDefaultsOnly, Category = Gameplay)
	TObjectPtr<class UDA_AbilitySet> AbilitySet;
	
	UPROPERTY(EditDefaultsOnly, Category = Input)
	TObjectPtr<class UDA_InputConfig> InputConfig;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Input_AbilityInputTagPressed(FGameplayTag InputTag);
	void Input_AbilityInputTagReleased(FGameplayTag InputTag);
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
private:
	void Input_Move(const FInputActionValue& InputValue);
	void Input_LookMouse(const FInputActionValue& InputValue);
	void Input_LookStick(const FInputActionValue& InputValue);
	void Input_Crouch(const FInputActionValue& InputActionValue);
};
