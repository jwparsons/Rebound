// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuPlayerController.h"

AMainMenuPlayerController::AMainMenuPlayerController()
{
	SIOClientComponent = CreateDefaultSubobject<USocketIOClientComponent>(TEXT("SocketIOClientComponent"));
}

void AMainMenuPlayerController::BeginPlay()
{
	if (IsLocalPlayerController()) {
		SIOClientComponent->Connect(FString("http://127.0.0.1:3000"));
	}
}
