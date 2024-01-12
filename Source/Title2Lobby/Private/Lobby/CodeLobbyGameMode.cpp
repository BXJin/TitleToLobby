// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/CodeLobbyGameMode.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

ACodeLobbyGameMode::ACodeLobbyGameMode() : CanWeStart(false)
{
}

// 내부적 규칙이라 헤더파일에 선언안해도됨, Replicate변수는 반드시 해줘야함
void ACodeLobbyGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ACodeLobbyGameMode, ControlRot);
}

void ACodeLobbyGameMode::SwapCharacter_Implementation(APlayerController* PlayerController, TSubclassOf<ACharacter> Character, bool ChangeStatus)
{
}

void ACodeLobbyGameMode::EveryOneUpdate_Implementation()
{
}

void ACodeLobbyGameMode::LaunchTheGame()
{
}
