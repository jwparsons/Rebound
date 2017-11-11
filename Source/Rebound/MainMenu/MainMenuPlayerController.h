// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Editor/UMGEditor/Public/WidgetBlueprint.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "MainMenuWidget.h"
#include "SocketIOClientComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainMenuPlayerController.generated.h"

UCLASS()
class REBOUND_API AMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AMainMenuPlayerController();

	virtual void BeginPlay() override;

	USocketIOClientComponent* SIOClientComponent;
};
