// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GAnimInstance.generated.h"

USTRUCT(BlueprintType)
struct PROJECTG_API FCharacterInfo
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float MaxSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Acceleration;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator Rotation;
};

USTRUCT(BlueprintType)
struct PROJECTG_API FCharacterMoveState
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bShouldMove;

	// 速度与面朝方向的夹角
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Angle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float SpeedFactor; // = speed / max_speed
};

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class PROJECTG_API UGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ACharacter> Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FCharacterInfo CharacterInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FCharacterMoveState MoveState;
};
