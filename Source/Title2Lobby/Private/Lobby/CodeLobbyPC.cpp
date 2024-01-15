// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/CodeLobbyPC.h"
#include "Lobby/CodeLobbyGameMode.h"
#include "Net/UnrealNetwork.h"
#include "Blueprint/UserWidget.h"
#include "Lobby/CodeLobbyMenu.h"
#include "Kismet/GameplayStatics.h"
#include "ALL/PlayerSaveGame.h"

ACodeLobbyPC::ACodeLobbyPC() : PlayerSettingsSave(FString::Printf(TEXT("PlayerSettingsSave")))
{
}

void ACodeLobbyPC::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACodeLobbyPC, PlayerSettings);
	DOREPLIFETIME(ACodeLobbyPC, AvailableCharaters);
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

void ACodeLobbyPC::UpdateLobbySettings_Implementation(UTexture2D* MapImage, const FText& MapName, const FText& MapDifficulty)
{
	LobbyMenu->MapImage = MapImage;
	LobbyMenu->MapName = MapName;
	LobbyMenu->MapDifficulty = MapDifficulty;
}

void ACodeLobbyPC::ShowLoadingScreen_Implementation()
{
	LobbyMenu->RemoveFromParent();
	LoadingScreen = CreateWidget<UUserWidget>(this, LoadingScreenWidgetClass);
	LoadingScreen->AddToViewport();
}

void ACodeLobbyPC::UpdateAvailableChacracter_Implementation(const TArray<bool>& AvailableCharater)
{
	AvailableCharaters = AvailableCharater;
}

void ACodeLobbyPC::UpdateNumberOfPlayers_Implementation(int32 CurrentPlayers, int32 MaxPlayers)
{
	if (IsValid(LobbyMenu))
	{
		FText NewText = FText::FromString(FString::Printf(TEXT("%d / %d"), CurrentPlayers, MaxPlayers));
		LobbyMenu->PlayersDisplay = NewText;
	}
}

void ACodeLobbyPC::SaveGameCheck()
{
	if (UGameplayStatics::DoesSaveGameExist(PlayerSettingsSave, 0))
	{
		LoadGame();
	}
	SaveGame();
}

void ACodeLobbyPC::SaveGame()
{
	UPlayerSaveGame* SaveGameRef = Cast<UPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UPlayerSaveGame::StaticClass()));
	SaveGameRef->S_PlayerInfo = PlayerSettings;
	UGameplayStatics::SaveGameToSlot(SaveGameRef, PlayerSettingsSave, 0);
}

void ACodeLobbyPC::LoadGame()
{
	auto m_SaveGame = UGameplayStatics::LoadGameFromSlot(PlayerSettingsSave, 0);
	UPlayerSaveGame* SaveGameRef = Cast<UPlayerSaveGame>(m_SaveGame);
	if(!IsValid(SaveGameRef))
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("NoLoadSaveGame"));
	PlayerSettings.MyPlayerName = SaveGameRef->S_PlayerInfo.MyPlayerName;
	PlayerSettings.MyPlayerLogo = SaveGameRef->S_PlayerInfo.MyPlayerLogo;
	//check(BaseCharacter);
	PlayerSettings.MyPlayerCharacter = BaseCharacter;
}
