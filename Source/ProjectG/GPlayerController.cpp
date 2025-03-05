// Fill out your copyright notice in the Description page of Project Settings.


#include "GPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GSpringArmComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "GameFramework/Character.h"

AGPlayerController::AGPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	CachedDestination = FVector::ZeroVector;
	FollowTime = 0.f;
}

void AGPlayerController::BeginPlay()
{
	if (const ACharacter* MyCharacter = GetCharacter())
	{
		AnimInstance = MyCharacter->GetMesh()->GetAnimInstance();
		if (AnimInstance)
		{
			AnimInstance->LinkAnimClassLayers(NoGunLocomotionAnimInstanceClass);
		}
	}
}

void AGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	// Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Setup mouse input events
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Started, this, &AGPlayerController::OnInputStarted);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Triggered, this, &AGPlayerController::OnSetDestinationTriggered);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Completed, this, &AGPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(SetDestinationClickAction, ETriggerEvent::Canceled, this, &AGPlayerController::OnSetDestinationReleased);
		EnhancedInputComponent->BindAction(ViewScrollAction, ETriggerEvent::Triggered, this, &AGPlayerController::OnMouseWheel);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AGPlayerController::OnInputStarted()
{
	StopMovement();
}

// Triggered every frame when the input is held down
void AGPlayerController::OnSetDestinationTriggered()
{
	// We flag that the input is being pressed
	FollowTime += GetWorld()->GetDeltaSeconds();

	// We look for the location in the world where the player has pressed the input
	FHitResult Hit;

	// If we hit a surface, cache the location
	if (GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, Hit))
	{
		CachedDestination = Hit.Location;
	}

	// Move towards mouse pointer or touch
	APawn* ControlledPawn = GetPawn();
	if (ControlledPawn != nullptr)
	{
		FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
		ControlledPawn->AddMovementInput(WorldDirection, 1.0, false);
	}
}

void AGPlayerController::OnSetDestinationReleased()
{
	// If it was a short press
	if (FollowTime <= ShortPressThreshold)
	{
		// We move there and spawn some particles
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, CachedDestination);
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, CachedDestination, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
	}

	FollowTime = 0.f;
}

void AGPlayerController::OnMouseWheel(const FInputActionValue& Value)
{
	float WheelData = Value.Get<float>();
	ACharacter* Actor = GetCharacter();
	if (Actor)
	{
		UGSpringArmComponent* SpringArm = Actor->FindComponentByClass<UGSpringArmComponent>();
		if (SpringArm)
		{
			if (WheelData < 0.f)
			{
				SpringArm->TransformView(TopDownSetting, 1, .5F, TransitionCurve);
			}
			else
			{
				SpringArm->TransformView(ThirdPersonSetting, 0, .5F, TransitionCurve);
			}
		}
	}
}

void AGPlayerController::EquipGun()
{
	if (GunMontage && GunState == EGunState::Idle)
	{
		float Succeed = AnimInstance->Montage_Play(GunMontage);
		if (Succeed == 0.0f)
		{
			return;
		}
		GunState = EGunState::Equiping;
		AnimInstance->Montage_JumpToSection(EquipGunAnimName);
		AnimInstance->LinkAnimClassLayers(GunLocomotionAnimInstanceClass);
		FOnMontageEnded OnMontageEnded;
		OnMontageEnded.BindLambda([this](UAnimMontage*, bool /*bInterrupted*/)
		{
			GunState = EGunState::Equiped;
		});
		AnimInstance->Montage_SetEndDelegate(OnMontageEnded);
	}
}

void AGPlayerController::DemountGun()
{
	if (GunMontage && GunState == EGunState::Equiped)
	{
		float Succeed = AnimInstance->Montage_Play(GunMontage);
		if (Succeed == 0.0f)
		{
			return;
		}
		GunState = EGunState::Demounting;
		AnimInstance->Montage_JumpToSection(DemountGunName);
		AnimInstance->LinkAnimClassLayers(NoGunLocomotionAnimInstanceClass);
		FOnMontageEnded OnMontageEnded;
		OnMontageEnded.BindLambda([this](UAnimMontage*, bool /*bInterrupted*/)
		{
			GunState = EGunState::Idle;
		});
		AnimInstance->Montage_SetEndDelegate(OnMontageEnded);
	}
}

void AGPlayerController::ReloadGun()
{
}

void AGPlayerController::FireGun()
{
}
