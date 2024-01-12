// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/CodeLobbyGameMode.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"

ACodeLobbyGameMode::ACodeLobbyGameMode() : CanWeStart(false)
{
}

// ������ ��Ģ�̶� ������Ͽ� ������ص���, Replicate������ �ݵ�� �������
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
