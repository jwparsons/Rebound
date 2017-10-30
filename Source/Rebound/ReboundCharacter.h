// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"
#include "ConstructorHelpers.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ReboundCharacter.generated.h"

UCLASS(config=Game)
class AReboundCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

public:
	AReboundCharacter();
	virtual void BeginPlay();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }

public:
	void ExplodeCharacter();

private:
	UParticleSystemComponent* ExplosionParticle;
	UAudioComponent* ExplosionAudioPlayer;
	UAudioComponent* ScreamAudioPlayer;
	USoundWave* ExplosionSound;
	USoundWave* ScreamSound;
};

