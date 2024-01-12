// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ALL/PlayerInfo.h"
#include "GameFramework/PlayerController.h"
#include "CodeLobbyPC.generated.h"


UCLASS()
class TITLE2LOBBY_API ACodeLobbyPC : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UCodeLobbyMenu> LobbyMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UCodeLobbyMenu* LobbyMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> LoadingScreenWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* LoadingScreen;

public:
	UPROPERTY(Replicated, BlueprintReadWrite)
	FPlayerInfo PlayerSettings;

public:
	UFUNCTION(Client, Reliable)
	void InitSetUp();

	void InitSetUp_Implementation();

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void CallUpdate(const FPlayerInfo& PlayerInfo, bool IsChangedStatus);

	void CallUpdate_Implementation(const FPlayerInfo& PlayerInfo, bool IsChangedStatus);

	UFUNCTION(Client , Reliable)
	void CreateLobbyMenu(const FText& ServerName);

	void CreateLobbyMenu_Implementation(const FText& ServerName);

	UFUNCTION(Client, Reliable)
	void AddPlayerInfo(const TArray<FPlayerInfo>& ConnectedPlayerInfo);

	void AddPlayerInfo_Implementation(const TArray<FPlayerInfo>& ConnectedPlayerInfo);

	UFUNCTION(Client, Reliable)
	void UpdateLobbySettings(UTexture2D* MapImage, const FText& MapName, const FText& MapTime);

	void UpdateLobbySettings_Implementation(UTexture2D* MapImage, const FText& MapName, const FText& MapTime);

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void ShowLoadingScreen();

	void ShowLoadingScreen_Implementation();

public:
	void UpdateNumberOfPlayers(int32 CurrentPlayers, int32 MaxPlayers);

private:
	void SaveGameCheck();
	
	void SaveGame();

	void RoadGame();

private:
	TArray<FPlayerInfo> AllPlayersInfo;
};
