// Fill out your copyright notice in the Description page of Project Settings.


#include "GAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/PawnMovementComponent.h"

void UGAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	Character = Cast<ACharacter>(GetOwningActor());
}

void UGAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Character)
	{
		CharacterInfo.Velocity = Character->GetVelocity();
		CharacterInfo.Speed = Character->GetVelocity().Size();
		CharacterInfo.Acceleration = Character->GetVelocity();
		CharacterInfo.Rotation = Character->GetActorRotation();
		CharacterInfo.MaxSpeed = Character->GetMovementComponent()->GetMaxSpeed();
	}
	MoveState.bShouldMove = CharacterInfo.Speed > 5.f && CharacterInfo.Acceleration != FVector::ZeroVector;
	const FRotator VelocityRotator = CharacterInfo.Velocity.Rotation();
	MoveState.Angle = VelocityRotator.Yaw - CharacterInfo.Rotation.Yaw;
	MoveState.SpeedFactor = CharacterInfo.Speed / CharacterInfo.MaxSpeed;
	GetCurveValueWithDefault("UpFoot", 0, FootState.UpFoot);
	GetCurveValueWithDefault("CanStop", 0, FootState.CanStop);
}
