// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuWidget.h"

void UMainMenuWidget::Construct()
{
	Super::Construct();

	UE_LOG(LogTemp, Warning, TEXT("a"));

	UButton* JoinButton = Cast<UButton>(GetWidgetFromName(TEXT("JoinGameButton")));
	JoinButton->OnClicked.AddDynamic(this, &UMainMenuWidget::JoinGame);
}

void UMainMenuWidget::JoinGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Your message"));
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
