// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SpringArmComponent.h"
#include "GSpringArmComponent.generated.h"

class USpringArmSetting;
class UGSpringArmSetting;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTG_API UGSpringArmComponent : public USpringArmComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGSpringArmComponent();

	/**
	 * 转换到设置的视角
	 * @param Setting 视角的设置
	 * @param InTargetFactor 转换到目标的比例, 0~1
	 * @param Seconds 用时
	 * @param Curve 转换时应该使用的曲线, 不填写(默认)就使用线性转换
	 */
	UFUNCTION(BlueprintCallable)
	void TransformView(USpringArmSetting* Setting, float InTargetFactor, float Seconds, UCurveFloat* Curve = nullptr);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USpringArmSetting> TargetSpringArmSetting;

	UPROPERTY(BlueprintReadOnly)
	float ViewTransformTimeRemaining = 0;

	UPROPERTY(BlueprintReadOnly)
	float ViewTransformTime = 0;

	UPROPERTY(BlueprintReadOnly)
	float TargetFactor = 0;

	UPROPERTY(BlueprintReadOnly)
	UCurveFloat* BlendCurve = nullptr;

	UPROPERTY(BlueprintReadOnly)
	float StartLength = 0;
};
