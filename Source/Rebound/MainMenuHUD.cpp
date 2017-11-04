// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuHUD.h"

AMainMenuHUD::AMainMenuHUD()
{
	static ConstructorHelpers::FClassFinder<UMainMenuWidget> FBP_MainMenuWidget(TEXT("WidgetBlueprint'/Game/UMG/BP_MainMenuWidget.BP_MainMenuWidget_C'"));
	if (FBP_MainMenuWidget.Class)
		BP_MainMenuWidget = FBP_MainMenuWidget.Class;
}

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController->IsLocalPlayerController())
	{
		if (BP_MainMenuWidget)
		{
			if (!MainMenuWidget)
			{
				MainMenuWidget = CreateWidget<UMainMenuWidget>(PlayerController, BP_MainMenuWidget);
				if (MainMenuWidget)
				{
					FInputModeGameAndUI InputMode;
					InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
					PlayerController->SetInputMode(InputMode);
					PlayerController->bShowMouseCursor = true;
					MainMenuWidget->AddToViewport();
				}
			}
		}
	}
}
