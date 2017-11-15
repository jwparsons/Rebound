// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"

UMainMenuWidget::UMainMenuWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bIsSearchingForGame = false;
}

void UMainMenuWidget::JoinGame()
{
	AMainMenuPlayerController* MainMenuPlayerController = Cast<AMainMenuPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainMenuPlayerController->SearchForGame();
	bIsSearchingForGame = !bIsSearchingForGame;
}

void UMainMenuWidget::ExitGame()
{
	AMainMenuPlayerController* MainMenuPlayerController = Cast<AMainMenuPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	MainMenuPlayerController->StopSearchForGame();
	UKismetSystemLibrary::QuitGame(GetWorld(), MainMenuPlayerController, EQuitPreference::Quit);
}
