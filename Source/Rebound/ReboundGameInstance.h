// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ReboundGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class REBOUND_API UReboundGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UReboundGameInstance();

	FString PlayerName;
	void SetPlayerName(FString PlayerInput);
};
