// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuPlayerController.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
	SIOClientComponent = CreateDefaultSubobject<USocketIOClientComponent>(TEXT("SocketIOClientComponent"));
	if (SIOClientComponent) {
		SIOClientComponent->bShouldAutoConnect = false;
	}
}

void AMainMenuPlayerController::BeginPlay()
{
	if (IsLocalPlayerController()) {
		SIOClientComponent->Connect(FString("http://127.0.0.1:3000"));
		if (SIOClientComponent) {
			SIOClientComponent->OnNativeEvent(FString("join game"), [](const FString& Event, const TSharedPtr<FJsonValue>& Message)
			{
				//Called when the event is received
				UE_LOG(LogTemp, Warning, TEXT("blem"));
			});
		}
	}
}

void AMainMenuPlayerController::SearchForGame()
{
	if (IsLocalPlayerController())
	{
		SIOClientComponent->EmitNative(FString("join"), FString("hi"));
	}
}

void AMainMenuPlayerController::StopSearchForGame()
{
	if (IsLocalPlayerController())
	{
		SIOClientComponent->EmitNative(FString("cancel"), FString("hi"));
	}
}
