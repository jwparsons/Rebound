// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuPawn.h"


// Sets default values
AMainMenuPawn::AMainMenuPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
}

// Called when the game starts or when spawned
void AMainMenuPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainMenuPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainMenuPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}