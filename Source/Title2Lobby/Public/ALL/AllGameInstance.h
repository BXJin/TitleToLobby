// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AllGameInstance.generated.h"

UCLASS()
class TITLE2LOBBY_API UAllGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText LobbyName;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> LoadingScreenWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* LoadingScreen;

public:
	UFUNCTION(BlueprintCallable)
	void ShowLoadingScreen();

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void LaunchLobby(int32 NumberOfPlayers, bool EnableLan , const FText& ServerName);

	void LaunchLobby_Implementation(int32 NumberOfPlayers, bool EnableLan, const FText& ServerName);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void JoinServer(FBlueprintSessionResult SessionToJoin);

	void JoinServer_Implementation(FBlueprintSessionResult SessionToJoin);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void DestroySessionCall(APlayerController* PlayerController );

	void DestroySessionCall_Implementation(APlayerController* PlayerController);
};
