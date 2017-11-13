// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MainMenuPlayerController.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"

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

	UFUNCTION(BlueprintCallable, Category = "Buttons")
	void ExitGame();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game Search")
	bool bIsSearchingForGame;

};
