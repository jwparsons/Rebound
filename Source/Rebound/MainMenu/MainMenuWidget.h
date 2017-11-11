// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/UMG/Public/Components/Button.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

UCLASS()
class REBOUND_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UMainMenuWidget(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, Category = "Buttons")
	void JoinGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Search")
	bool bIsSearchingForGame;

};
