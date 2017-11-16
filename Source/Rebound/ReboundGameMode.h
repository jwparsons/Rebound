// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "SocketIOClientComponent.h"
#include "ReboundBall.h"

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
	virtual bool ReadyToStartMatch_Implementation() override;

	USocketIOClientComponent* SIOClientComponent;
};
