// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GPlayerController.generated.h"

UENUM(BlueprintType)
enum class EGunState : uint8
{
	Idle,
	Equiping,
	Equiped,
	Reloading,
	Demounting,
	Max
};

class UGAnimInstance;
class USpringArmSetting;
class UKAS_SpringArmSetting;
struct FInputActionValue;
class UNiagaraSystem;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class PROJECTG_API AGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AGPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UNiagaraSystem> FXCursor;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SetDestinationClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> ViewScrollAction;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	virtual void SetupInputComponent() override;

	// To add mapping context
	virtual void BeginPlay() override;

	/** Input handlers for SetDestination action. */
	void OnInputStarted();
	void OnSetDestinationTriggered();
	void OnSetDestinationReleased();
	void OnMouseWheel(const FInputActionValue& Value);

private:
	FVector CachedDestination;

	float FollowTime; // For how long it has been pressed

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmSetting> TopDownSetting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmSetting> ThirdPersonSetting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCurveFloat> TransitionCurve;

public:
	UFUNCTION(BlueprintCallable)
	void EquipGun();

	UFUNCTION(BlueprintCallable)
	void DemountGun();

	UFUNCTION(BlueprintCallable)
	void ReloadGun();

	UFUNCTION(BlueprintCallable)
	void FireGun();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UAnimMontage> GunMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation, meta=(AllowPrivateAccess = "true"))
	FName DemountGunName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation, meta=(AllowPrivateAccess = "true"))
	FName ReloadGunName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation, meta=(AllowPrivateAccess = "true"))
	FName FireGunAnimName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation, meta=(AllowPrivateAccess = "true"))
	FName EquipGunAnimName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UAnimInstance> NoGunLocomotionAnimInstanceClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Animation, meta=(AllowPrivateAccess = "true"))
	TSubclassOf<UAnimInstance> GunLocomotionAnimInstanceClass;

	UAnimInstance* AnimInstance;

	EGunState GunState;
};