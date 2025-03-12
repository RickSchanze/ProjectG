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

USTRUCT(BlueprintType)
struct FCurveState
{
	GENERATED_BODY()

	// 哪只脚抬起来了
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float CanStop = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float UpFoot = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float AnimDrivenSpeed;
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

	// 读取曲线的值, 并以此值修复角色的位置
	UFUNCTION(BlueprintCallable)
	void FixCharacterLocation(float DeltaTime);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<ACharacter> Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FCharacterInfo CharacterInfo;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FCharacterMoveState MoveState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FCurveState CurveState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool bNeedFixLocation;
};
