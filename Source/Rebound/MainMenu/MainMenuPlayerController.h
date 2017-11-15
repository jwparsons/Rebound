// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
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

	void SearchForGame();
	void StopSearchForGame();
};
