// Fill out your copyright notice in the Description page of Project Settings.

#include "MainMenuGameModeBase.h"

AMainMenuGameModeBase::AMainMenuGameModeBase()
{
	DefaultPawnClass = AMainMenuPawn::StaticClass();
	PlayerControllerClass = AMainMenuPlayerController::StaticClass();
	HUDClass = AMainMenuHUD::StaticClass();
}
