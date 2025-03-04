// Fill out your copyright notice in the Description page of Project Settings.


#include "GSpringArmComponent.h"


#include "Setting/SpringArmSetting.h"


// Sets default values for this component's properties
UGSpringArmComponent::UGSpringArmComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	TargetArmLength = 800.f;
	SetUsingAbsoluteRotation(true);
	bDoCollisionTest = false;
	SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
}

void UGSpringArmComponent::TransformView(USpringArmSetting* Setting, float InTargetFactor, float Seconds, UCurveFloat* Curve)
{
	if (!Setting)
	{
		return;
	}
	ViewTransformTimeRemaining = Seconds;
	ViewTransformTime = Seconds;
	BlendCurve = Curve;
	TargetFactor = InTargetFactor;
	TargetSpringArmSetting = Setting;
}


// Called when the game starts
void UGSpringArmComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UGSpringArmComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (ViewTransformTimeRemaining > -0.5 && ViewTransformTime != 0)
	{
		if (ViewTransformTimeRemaining == ViewTransformTime)
		{
			StartLength = TargetArmLength;
		}
		float T = (ViewTransformTime - ViewTransformTimeRemaining) / ViewTransformTime;
		if (BlendCurve)
		{
			T = BlendCurve->GetFloatValue(T);
		}
		TargetArmLength = FMath::Lerp(StartLength, TargetSpringArmSetting->SpringLength, T);
		ViewTransformTimeRemaining = FMath::Clamp(ViewTransformTimeRemaining - DeltaTime, 0, ViewTransformTime);
	}
}
