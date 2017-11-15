// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "SocketIOClientComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ReboundGameMode.generated.h"

UCLASS(minimalapi)
class AReboundGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AReboundGameMode();

	virtual void BeginPlay() override;

	USocketIOClientComponent* SIOClientComponent;

};
