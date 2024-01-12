// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/CodeLobbyPC.h"
#include "Lobby/CodeLobbyGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/UserWidget.h"
#include "Lobby/CodeLobbyMenu.h"
#include "Kismet/GameplayStatics.h"

void ACodeLobbyPC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACodeLobbyPC, PlayerSettings);
}

void ACodeLobbyPC::InitSetUp_Implementation()
{
	SaveGameCheck();
	CallUpdate(PlayerSettings, false);
}

void ACodeLobbyPC::CallUpdate_Implementation(const FPlayerInfo& PlayerInfo, bool IsChangedStatus)
{
	PlayerSettings = PlayerInfo;
	ACodeLobbyGameMode* GM = Cast<ACodeLobbyGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (IsValid(GM))
	{
		GM->SwapCharacter(this, PlayerSettings.MyPlayerCharacter, IsChangedStatus);
		GM->EveryOneUpdate();
	}
}

void ACodeLobbyPC::CreateLobbyMenu_Implementation(const FText& ServerName)
{
	SetShowMouseCursor(true);

	LobbyMenu = CreateWidget<UCodeLobbyMenu>(this, LobbyMenuWidgetClass);
	LobbyMenu->LobbyServerName = ServerName;
	LobbyMenu->AddToViewport();

	SetInputMode(FInputModeGameAndUI());
}

void ACodeLobbyPC::AddPlayerInfo_Implementation(const TArray<FPlayerInfo>& ConnectedPlayerInfo)
{
	AllPlayersInfo = ConnectedPlayerInfo;
	if (IsValid(LobbyMenu))
	{
		LobbyMenu->ClearList();
		for (auto Value : AllPlayersInfo)
		{
			LobbyMenu->UpdateList(Value);
		}
	}
	
}

void ACodeLobbyPC::UpdateLobbySettings_Implementation(UTexture2D* MapImage, const FText& MapName, const FText& MapTime)
{
	LobbyMenu->MapImage = MapImage;
	LobbyMenu->MapName = MapName;
	LobbyMenu->MapTime = MapTime;
}

void ACodeLobbyPC::ShowLoadingScreen_Implementation()
{
	LobbyMenu->RemoveFromParent();
	LoadingScreen = CreateWidget<UUserWidget>(this, LoadingScreenWidgetClass);
	LoadingScreen->AddToViewport();
}

void ACodeLobbyPC::UpdateNumberOfPlayers(int32 CurrentPlayers, int32 MaxPlayers)
{
	if (IsValid(LobbyMenu))
	{
		FText NewText = FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentPlayers, MaxPlayers));
		LobbyMenu->PlayersDisplay = NewText;
	}
}

void ACodeLobbyPC::SaveGameCheck()
{
}

void ACodeLobbyPC::SaveGame()
{
}

void ACodeLobbyPC::RoadGame()
{
}
