// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CodeLobbyGameMode.generated.h"

class APlayerController;
class ACharacter;

UCLASS()
class TITLE2LOBBY_API ACodeLobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SwapCharacter(APlayerController* PlayerController, TSubclassOf<ACharacter> Character, bool ChangeStatus);

	void SwapCharacter_Implementation(APlayerController* PlayerController, TSubclassOf<ACharacter> Character, bool ChangeStatus);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void EveryOneUpdate();

	void EveryOneUpdate_Implementation();
};
