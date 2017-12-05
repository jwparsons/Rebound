// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ReboundGameMode.h"
#include "ReboundCharacter.h"
#include "UObject/ConstructorHelpers.h"

AReboundGameMode::AReboundGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	SIOClientComponent = CreateDefaultSubobject<USocketIOClientComponent>(TEXT("SocketIOClientComponent"));
	if (SIOClientComponent) {
		SIOClientComponent->bShouldAutoConnect = false;
	}

	PlayerControllerClass = AReboundPlayerController::StaticClass();
}

void AReboundGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (SIOClientComponent) {
		SIOClientComponent->Connect(FString("http://73.118.57.198:3000"));
		SIOClientComponent->EmitNative(FString("server creation"), GetWorld()->GetAddressURL());

		SIOClientComponent->OnNativeEvent(FString("terminate"), [&](const FString& Event, const TSharedPtr<FJsonValue>& Message)
		{
			UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit);
			FGenericPlatformMisc::RequestExit(false);
		});
	}

	// spawn ball
	FVector Location(0.0f, 0.0f, 150.0f);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AReboundBall>(Location, Rotation, SpawnInfo);
}

/** select best spawn point for player */
AActor* AReboundGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	for (TActorIterator<APlayerStart> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		APlayerStart* PlayerStart = *ActorItr;
		if (PlayerStart->PlayerStartTag != FName("TAKEN"))
		{
			PlayerStart->PlayerStartTag = FName("TAKEN");
			return PlayerStart;
		}
	}
	return nullptr;
}

bool AReboundGameMode::ReadyToStartMatch_Implementation() {
	if (NumPlayers >= 4)
		return true;
	else
		return false;
}

bool AReboundGameMode::ReadyToEndMatch_Implementation()
{
	int NumAlive = 0;
	for (TActorIterator<AReboundCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		if (ActorItr->ActorHasTag(FName("dead")))
			NumAlive++;
	}
	return NumAlive == 0;
}

void AReboundGameMode::EndMatch()
{
	if (SIOClientComponent) {
		SIOClientComponent->Connect(FString("http://73.118.57.198:3000"));
		SIOClientComponent->EmitNative(FString("match end"), GetWorld()->GetAddressURL());
	}
	Super::EndMatch();
}
