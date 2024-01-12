// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/CodeLobbyMenu.h"
#include "Engine/Texture2D.h"

void UCodeLobbyMenu::ClearList_Implementation()
{
}

void UCodeLobbyMenu::UpdateList_Implementation(const FPlayerInfo& PlayerInfo)
{
	UpdatePlayerList(PlayerInfo);
}

void UCodeLobbyMenu::UpdatePlayerList_Implementation(const FPlayerInfo& PlayerInfo)
{
}
