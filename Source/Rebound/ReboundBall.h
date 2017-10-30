// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ReboundCharacter.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReboundBall.generated.h"

UCLASS()
class REBOUND_API AReboundBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReboundBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

private:
	UPROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* ReboundBallMesh;

	UPROPERTY(EditAnywhere, Category = "Trail")
	UParticleSystemComponent* TrailParticle;
	float ElapsedTime;
};
