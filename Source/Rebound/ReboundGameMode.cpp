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
}

void AReboundGameMode::BeginPlay()
{
	if (SIOClientComponent) {
		SIOClientComponent->Connect(FString("http://127.0.0.1:3000"));
		SIOClientComponent->EmitNative(FString("server creation"), GetWorld()->GetAddressURL());

		SIOClientComponent->OnNativeEvent(FString("terminate"), [&](const FString& Event, const TSharedPtr<FJsonValue>& Message)
		{
			UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit);
		});
	}
}
