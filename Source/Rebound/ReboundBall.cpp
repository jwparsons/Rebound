// Fill out your copyright notice in the Description page of Project Settings.

#include "ReboundBall.h"


// Sets default values
AReboundBall::AReboundBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// create rebound ball mesh
	ReboundBallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ReboundBall"));
	RootComponent = ReboundBallMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FReboundBallMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (FReboundBallMesh.Object)
		ReboundBallMesh->SetStaticMesh(FReboundBallMesh.Object);

	// set rebound ball material
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> FReboundBallMaterial(TEXT("Material'/Game/Materials/M_BlueGlow.M_BlueGlow'"));
	if (FReboundBallMaterial.Object)
		ReboundBallMesh->SetMaterial(0, FReboundBallMaterial.Object);

	// set rebound ball scale
	FVector ReboundBallScale = FVector(1.0f, 1.0f, 1.0f);
	ReboundBallMesh->SetWorldScale3D(ReboundBallScale);

	// set rebound ball location
	FVector ReboundBallLocation = FVector(0.0f, 0.0f, 10.0f);
	ReboundBallMesh->SetWorldLocation(ReboundBallLocation);

	// set physics parameters
	ReboundBallMesh->SetSimulatePhysics(true);
	ReboundBallMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	ReboundBallMesh->SetConstraintMode(EDOFMode::XYPlane);
	ReboundBallMesh->SetNotifyRigidBodyCollision(true);
	ReboundBallMesh->BodyInstance.bLockXRotation = true;
	ReboundBallMesh->BodyInstance.bLockYRotation = true;
	ReboundBallMesh->BodyInstance.bLockZRotation = true;

	// set elapsed time
	ElapsedTime = 0.0f;

	// register OnHit for CapsuleComponent
	ReboundBallMesh->OnComponentHit.AddDynamic(this, &AReboundBall::OnHit);

	// create particle system trail
	TrailParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail"));
	if (TrailParticle)
	{
		static ConstructorHelpers::FObjectFinder<UParticleSystem> FTrailParticle(TEXT("ParticleSystem'/Game/Particles/P_Trail.P_Trail'"));
		if (FTrailParticle.Object)
			TrailParticle->SetTemplate(FTrailParticle.Object);
		FVector TrailParticleLocation = FVector(-50.0f, 0.0f, 0.0f);
		FRotator TrailParticleRotation = FRotator(0.0f, -180.0f, 0.0f);
		TrailParticle->SetRelativeLocation(TrailParticleLocation);
		TrailParticle->SetRelativeRotation(TrailParticleRotation);
		TrailParticle->SetupAttachment(ReboundBallMesh);
		TrailParticle->bAutoActivate = false;
	}

	// replication
	bReplicates = true;
	bReplicateMovement = true;
}

// Called when the game starts or when spawned
void AReboundBall::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AReboundBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// add velocity to ball
	FVector Direction = ReboundBallMesh->GetComponentVelocity();
	FVector ImpulseNormal = UKismetMathLibrary::Normal(Direction);
	FVector ImpulseStrength = UKismetMathLibrary::Multiply_VectorFloat(ImpulseNormal, 500.0f + 25.0f * ElapsedTime);
	ReboundBallMesh->AddImpulse(ImpulseStrength);

	// update ball rotation
	FRotator RotationFromX = UKismetMathLibrary::MakeRotFromX(Direction);
	ReboundBallMesh->SetWorldRotation(RotationFromX);

	// create explosion particle
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), TrailParticle->Template, GetActorLocation(), RotationFromX, true);

	ElapsedTime += DeltaTime;
}

void AReboundBall::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(AReboundCharacter::StaticClass()))
	{
		if (!OtherComponent->ComponentHasTag(FName("Shield")))
		{
			AReboundCharacter* Player = Cast<AReboundCharacter>(OtherActor);
			Player->RemoveHealth();
		}
	}
}
