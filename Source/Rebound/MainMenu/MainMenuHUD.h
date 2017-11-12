// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Runtime/CoreUObject/Public/UObject/ConstructorHelpers.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MainMenuWidget.h"

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
*
*/
UCLASS()
class REBOUND_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:
	AMainMenuHUD();
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HUD")
	TSubclassOf<UMainMenuWidget> BP_MainMenuWidget;

	UMainMenuWidget* MainMenuWidget;

};
