// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsSearchingForGame = false;
	SIOClientComponent = CreateDefaultSubobject<USocketIOClientComponent>(TEXT("SocketIOClientComponent"));
}

void UMainMenuWidget::JoinGame()
{
	bIsSearchingForGame = !bIsSearchingForGame;
}
