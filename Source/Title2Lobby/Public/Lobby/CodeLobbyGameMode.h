// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ALL/PlayerInfo.h"
#include "GameFramework/GameModeBase.h"
#include "CodeLobbyGameMode.generated.h"

class APlayerController;
class ACharacter;

UCLASS()
class TITLE2LOBBY_API ACodeLobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ACodeLobbyGameMode();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	virtual void Logout(AController* Exiting) override;

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SwapCharacter(APlayerController* PlayerController, TSubclassOf<ACharacter> Character, bool ChangeStatus);

	void SwapCharacter_Implementation(APlayerController* PlayerController, TSubclassOf<ACharacter> Character, bool ChangeStatus);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void EveryOneUpdate();

	void EveryOneUpdate_Implementation();

	UFUNCTION(Server, Reliable)
	void RespawnPlayer(APlayerController* PlayerController);

	void RespawnPlayer_Implementation(APlayerController* PlayerController);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerUpdateLobbySettings(UTexture2D* MapImage, const FText& MapName, const FText& MapDifficulty, int32 MapID);

	void ServerUpdateLobbySettings_Implementation(UTexture2D* MapImage, const FText& MapName, const FText& MapDifficulty, int32 MapID);

public:
	UFUNCTION(BlueprintCallable)
	void LaunchTheGame();

public:
	UPROPERTY(BlueprintReadOnly)
	bool CanWeStart;

	UPROPERTY(BlueprintReadOnly)
	FText ServerName;

	UPROPERTY(BlueprintReadOnly)
	int32 MaxPlayers;

private:
	UPROPERTY(EditAnywhere)
	UTexture2D* g_MapImage;

	UPROPERTY(EditAnywhere)
	FText g_MapName;

	UPROPERTY(EditAnywhere)
	FText g_MapDifficulty;

	int32 g_MapID;

public:
	TArray<bool> AvailableCharacters;

	UPROPERTY(BlueprintReadOnly)
	TArray<APlayerController*> AllPlayerControllers;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<AActor*> AllRespawnPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACharacter> BaseCharacter;

	TArray<FPlayerInfo> ConnectedPlayerInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<ACharacter>> AllCharacters;
};  
