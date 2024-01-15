// Fill out your copyright notice in the Description page of Project Settings.


#include "Lobby/CodeLobbyGameMode.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/Actor.h"
#include "ALL/AllGameInstance.h"
#include "Lobby/CodeLobbyPC.h"

ACodeLobbyGameMode::ACodeLobbyGameMode() : CanWeStart(false)
{
}

// 내부적 규칙이라 헤더파일에 선언안해도됨, Replicate변수는 반드시 해줘야함
void ACodeLobbyGameMode::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//DOREPLIFETIME(ACodeLobbyGameMode, ControlRot);
}

void ACodeLobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (HasAuthority())
	{
		AllPlayerControllers.Add(NewPlayer);
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), AllRespawnPoints);
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf( TEXT("Points %d"),AllRespawnPoints.Num()));
		UAllGameInstance* GameInstance = Cast<UAllGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		MaxPlayers = GameInstance->MaxPlayers;
		ServerName = GameInstance->LobbyName;
		ACodeLobbyPC* LobbyPc = Cast<ACodeLobbyPC>(NewPlayer);
		if (IsValid(LobbyPc))
		{
			LobbyPc->InitSetUp();
			LobbyPc->CreateLobbyMenu(ServerName);
			LobbyPc->UpdateLobbySettings(g_MapImage,g_MapName,g_MapDifficulty);
			RespawnPlayer(LobbyPc);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("RespawnPlayer"));
		}
	}
}


void ACodeLobbyGameMode::SwapCharacter_Implementation(APlayerController* PlayerController, TSubclassOf<ACharacter> Character, bool ChangeStatus)
{
}

void ACodeLobbyGameMode::EveryOneUpdate_Implementation()
{
	if (AllPlayerControllers.Num() > 0)
	{
		ConnectedPlayerInfo.Empty();
		for (auto Value : AllPlayerControllers)
		{
			ACodeLobbyPC* m_LobbyPC = Cast<ACodeLobbyPC>(Value);
			if (IsValid(m_LobbyPC))
			{
				ConnectedPlayerInfo.Add(m_LobbyPC->PlayerSettings);
				m_LobbyPC->UpdateNumberOfPlayers(AllPlayerControllers.Num(), MaxPlayers);
			}
		}
		for (auto Value : AllPlayerControllers)
		{
			ACodeLobbyPC* m_LobbyPC = Cast<ACodeLobbyPC>(Value);
			if (IsValid(m_LobbyPC))
			{
				m_LobbyPC->AddPlayerInfo(ConnectedPlayerInfo);
				m_LobbyPC->UpdateAvailableChacracter(AvailableCharacters);
			}
		}
		for (auto Value : ConnectedPlayerInfo)
		{		
			if ( (Value.MyPlayerStatus.EqualToCaseIgnored(FText::FromString("Not Ready"))) 
				|| (Value.MyPlayerCharacter == BaseCharacter) )
			{
				CanWeStart = false;
				break;
			}
			else
			{
				CanWeStart = true;
			}
		}
	}
}

void ACodeLobbyGameMode::RespawnPlayer_Implementation(APlayerController* PlayerController)
{
	if (IsValid(PlayerController->GetPawn()))
	{
		GetWorld()->DestroyActor(PlayerController->GetPawn());
	}
	auto RandomIndex = FMath::RandRange(0, AllRespawnPoints.Num() - 1);
	check(BaseCharacter);
	ACharacter* NewChar = GetWorld()->SpawnActor<ACharacter>(BaseCharacter, AllRespawnPoints[RandomIndex]->GetActorTransform());
	PlayerController->Possess(NewChar);
	EveryOneUpdate();
}

void ACodeLobbyGameMode::ServerUpdateLobbySettings_Implementation(UTexture2D* MapImage, const FText& MapName, const FText& MapDifficulty, int32 MapID)
{
	g_MapImage = MapImage;
	g_MapName = MapName;
	g_MapDifficulty = MapDifficulty;
	g_MapID = MapID;

	for (auto Value : AllPlayerControllers)
	{
		ACodeLobbyPC* m_LobbyPC = Cast<ACodeLobbyPC>(Value);
		if (IsValid(m_LobbyPC))
		{
			m_LobbyPC->UpdateLobbySettings(g_MapImage, g_MapName, g_MapDifficulty);
		}
	}
}

void ACodeLobbyGameMode::LaunchTheGame()
{
	switch (g_MapID)
	{
	case 0:
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(), 
			FString::Printf(TEXT("servertravel/Game/Maps/Arena01")), GetWorld()->GetFirstPlayerController());
		break;
	case 1:
		UKismetSystemLibrary::ExecuteConsoleCommand(GetWorld(),
			FString::Printf(TEXT("servertravel/Game/Maps/Arena02")), GetWorld()->GetFirstPlayerController());
		break;
	}
}
