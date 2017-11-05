// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/UMG/Public/Components/Button.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class REBOUND_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void Construct();
	void JoinGame();
};
