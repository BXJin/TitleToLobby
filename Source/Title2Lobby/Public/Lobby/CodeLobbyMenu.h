// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ALL/PlayerInfo.h"
#include "Blueprint/UserWidget.h"
#include "CodeLobbyMenu.generated.h"

/**
 * 
 */
UCLASS()
class TITLE2LOBBY_API UCodeLobbyMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LobbyMenuSettings")
	FText LobbyServerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LobbyMenuSettings")
	FText MapName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LobbyMenuSettings")
	FText MapTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LobbyMenuSettings")
	UTexture2D* MapImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LobbyMenuSettings")
	FText PlayersDisplay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LobbyMenuSettings")
	FText ReadyButtonText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "LobbyMenuSettings")
	FText ReadyStatus;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ClearList();

	void ClearList_Implementation();

public:
	UFUNCTION(Client, Reliable)
	void UpdateList(const FPlayerInfo& PlayerInfo);

	void UpdateList_Implementation(const FPlayerInfo& PlayerInfo);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void UpdatePlayerList(const FPlayerInfo& PlayerInfo);

	void UpdatePlayerList_Implementation(const FPlayerInfo& PlayerInfo);

};
