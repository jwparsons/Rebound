// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuPlayerController.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
	SIOClientComponent = CreateDefaultSubobject<USocketIOClientComponent>(TEXT("SocketIOClientComponent"));
	SIOClientComponent->bShouldAutoConnect = false;
}

void AMainMenuPlayerController::BeginPlay()
{
	if (IsLocalPlayerController()) {
		SIOClientComponent->Connect(FString("http://127.0.0.1:3000"));
	}
}

void AMainMenuPlayerController::JoinGame(bool bIsSearchingForGame)
{
	if (IsLocalPlayerController()) {
		if (bIsSearchingForGame) {
			UE_LOG(LogTemp, Warning, TEXT("a"));
			SIOClientComponent->EmitNative(FString("join"), FString("hi"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("b"));
			SIOClientComponent->EmitNative(FString("cancel"), FString("hi"));
		}
	}
}
