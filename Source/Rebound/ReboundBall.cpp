// Fill out your copyright notice in the Description page of Project Settings.

#include "ReboundBall.h"


// Sets default values
AReboundBall::AReboundBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create root component
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	// create rebound ball mesh
	ReboundBallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReboundBall"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FReboundBallMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (FReboundBallMesh.Object)
		ReboundBallMesh->SetStaticMesh(FReboundBallMesh.Object);

	// set rebound ball material
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FReboundBallMaterial(TEXT("Material'/Game/Materials/M_BlueGlow.M_BlueGlow'"));
	if (FReboundBallMaterial.Object)
		ReboundBallMesh->SetMaterial(0, FReboundBallMaterial.Object);

	// set rebound ball physics material
	/*
	static ConstructorHelpers::FObjectFinder<UObject> FReboundBallPhysicalMaterial(TEXT("PhysicalMaterial'/Game/Physics/PM_ArenaWall.PM_ArenaWall'"));
	if (FReboundBallPhysicalMaterial.Object)
		ReboundBallMesh->SetPhysMaterialOverride((UPhysicalMaterial*)FReboundBallPhysicalMaterial.Object);
	*/

	// set rebound ball scale
	FVector ReboundBallScale = FVector(1.0f, 1.0f, 1.0f);
	ReboundBallMesh->SetWorldScale3D(ReboundBallScale);

	// set rebound ball location
	FVector ReboundBallLocation = FVector(0.0f, 0.0f, 10.0f);
	ReboundBallMesh->SetWorldLocation(ReboundBallLocation);

	// attach to parent
	FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::SnapToTarget,
		EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, true);
	ReboundBallMesh->AttachToComponent(RootComponent, AttachmentTransformRules);

	// set physics parameters
	ReboundBallMesh->SetSimulatePhysics(true);
	ReboundBallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ReboundBallMesh->SetConstraintMode(EDOFMode::XYPlane);

	// set elapsed time
	ElapsedTime = 0.0f;
}

// Called when the game starts or when spawned
void AReboundBall::BeginPlay()
{
	Super::BeginPlay();

	FVector InitialImpulse = FVector(0.0f, 500.0f, 0.0f);
	ReboundBallMesh->AddImpulse(InitialImpulse);
}

// Called every frame
void AReboundBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Direction = ReboundBallMesh->GetComponentVelocity();
	FVector ImpulseNormal = UKismetMathLibrary::Normal(Direction);
	FVector ImpulseStrength = UKismetMathLibrary::Multiply_VectorFloat(ImpulseNormal, 500.0f + 25.0f * ElapsedTime);
	ReboundBallMesh->AddImpulse(ImpulseStrength);

	ElapsedTime += DeltaTime;
}

