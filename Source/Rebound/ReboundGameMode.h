// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "SocketIOClientComponent.h"
#include "ReboundBall.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerStart.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "ReboundCharacter.h"
#include "ReboundPlayerController.h"

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "ReboundGameMode.generated.h"

UCLASS(minimalapi)
class AReboundGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AReboundGameMode();

	virtual void BeginPlay() override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	virtual bool ReadyToStartMatch_Implementation() override;
	virtual bool ReadyToEndMatch_Implementation() override;
	virtual void EndMatch() override;

	USocketIOClientComponent* SIOClientComponent;
};
