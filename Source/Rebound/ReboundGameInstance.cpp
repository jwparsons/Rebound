// Fill out your copyright notice in the Description page of Project Settings.

#include "ReboundGameInstance.h"

UReboundGameInstance::UReboundGameInstance()
{
	PlayerName = FString(TEXT("?"));
}

void UReboundGameInstance::SetPlayerName(FString InputText)
{
	if (InputText.Len() > 0)
		PlayerName = InputText;
	else
		PlayerName = FString(TEXT("?"));
}