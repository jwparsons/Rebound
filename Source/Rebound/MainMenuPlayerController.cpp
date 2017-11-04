// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuPlayerController.h"

AMainMenuPlayerController::AMainMenuPlayerController() {
	static ConstructorHelpers::FClassFinder<UUserWidget> FBP_MainMenuWidget(TEXT("WidgetBlueprint'/Game/UMG/BP_MainMenuWidget.BP_MainMenuWidget_C'"));
	if (FBP_MainMenuWidget.Class)
		BP_MainMenuWidget = FBP_MainMenuWidget.Class;
}

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (BP_MainMenuWidget)
	{
		if (!MainMenuWidget)
		{
			MainMenuWidget = CreateWidget<UUserWidget>(this, BP_MainMenuWidget);
			if (MainMenuWidget)
			{
				MainMenuWidget->AddToViewport();
			}
		}
	}
}