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
	AvailableCharacters.SetNum(9, false);
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
			//RespawnPlayer(LobbyPc);
			LobbyPc->UpdateNumberOfPlayers(AllPlayerControllers.Num(), MaxPlayers);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("RespawnPlayer"));
		}
	}
}

void ACodeLobbyGameMode::Logout(AController* Exiting)
{
	int32 m_Index;
	APlayerController* PC = Cast<APlayerController>(Exiting);
	if (AllPlayerControllers.Find(PC, m_Index))
	{
		ACodeLobbyPC* LobbyPc = Cast<ACodeLobbyPC>(PC);
		if (IsValid(LobbyPc))
		{
			AvailableCharacters[LobbyPc->SelectedCharacterNum] = true;
			AllPlayerControllers.RemoveAt(m_Index);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("PCs %d"), AllPlayerControllers.Num()));
			ConnectedPlayerInfo.RemoveAt(m_Index);
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("PIs %d"), ConnectedPlayerInfo.Num()));
			//UKismetArrayLibrary::Array_Remove();
			//Ukis
			EveryOneUpdate();
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, TEXT("Logout"));
}


void ACodeLobbyGameMode::SwapCharacter_Implementation(APlayerController* PlayerController, TSubclassOf<ACharacter> Character, bool ChangeStatus)
{
	if (!ChangeStatus)
	{
		if (IsValid(PlayerController->GetPawn()))
		{
			GetWorld()->DestroyActor(PlayerController->GetPawn());
		}
		auto RandomIndex = FMath::RandRange(0, AllRespawnPoints.Num() - 1);
		ACharacter* NewChar = GetWorld()->SpawnActor<ACharacter>(Character, AllRespawnPoints[RandomIndex]->GetActorTransform());
		PlayerController->Possess(NewChar);
//		EveryOneUpdate();		
	}
}

void ACodeLobbyGameMode::EveryOneUpdate_Implementation()
{
	FTimerHandle TimerHandle;

	if (AllPlayerControllers.Num() > 0)
	{
		ConnectedPlayerInfo.Empty();
		for (auto Value : AllPlayerControllers)
		{
			ACodeLobbyPC* m_LobbyPC = Cast<ACodeLobbyPC>(Value);
			if (IsValid(m_LobbyPC))
			{
				ConnectedPlayerInfo.Add(m_LobbyPC->PlayerSettings);
				GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("EveryoneUp %d"), AllPlayerControllers.Num()));
				m_LobbyPC->UpdateNumberOfPlayers(AllPlayerControllers.Num(), MaxPlayers);
			}
		}

		GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
			{
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
					if ((Value.MyPlayerStatus.EqualToCaseIgnored(FText::FromString("Not Ready")))
						|| (Value.MyPlayerCharacter == BaseCharacter))
					{
						CanWeStart = false;
						break;
					}
					else
					{
						CanWeStart = true;
					}
				}
			}, 0.01f, false);
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
