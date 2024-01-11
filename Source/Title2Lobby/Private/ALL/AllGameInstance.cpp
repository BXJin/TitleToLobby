// Fill out your copyright notice in the Description page of Project Settings.


#include "ALL/AllGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "FindSessionsCallbackProxy.h"

void UAllGameInstance::ShowLoadingScreen()
{
	if (!IsValid(LoadingScreen))
	{
		LoadingScreen = CreateWidget<UUserWidget>(GetWorld(), LoadingScreenWidgetClass);
		LoadingScreen->SetOwningPlayer(GetWorld()->GetFirstPlayerController());
	}
	LoadingScreen->AddToViewport();
}

void UAllGameInstance::LaunchLobby_Implementation(int32 NumberOfPlayers, bool EnableLan, const FText& ServerName)
{
}

void UAllGameInstance::JoinServer_Implementation(FBlueprintSessionResult SessionToJoin)
{
}

void UAllGameInstance::DestroySessionCall_Implementation(APlayerController* PlayerController)
{
}
