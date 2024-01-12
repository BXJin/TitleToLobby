// Fill out your copyright notice in the Description page of Project Settings.


#include "Title/CodeTitleHUD.h"
#include "Blueprint/UserWidget.h"
#include "Containers/UnrealString.h"
#include "Kismet/GameplayStatics.h"

ACodeTitleHUD::ACodeTitleHUD() : PlayerSettingsSave(FString(TEXT("PlayerSettingsSave")))
{
}

void ACodeTitleHUD::BeginPlay()
{
	Super::BeginPlay();

	SaveGameCheck();
}

void ACodeTitleHUD::SaveGameCheck()
{
	if (UGameplayStatics::DoesSaveGameExist(PlayerSettingsSave, 0))
	{
		ShowMainMenu();
		CreateSaveGame = true;
	}
	else 
		ShowOptionsMenu();
}


void ACodeTitleHUD::ShowMainMenu()
{
	APlayerController* Player0 = GetWorld()->GetFirstPlayerController();
	if(!IsValid(MainMenu))
	{
		MainMenu = CreateWidget<UUserWidget>(Player0, MainMenuWidgetClass);
	}
	MainMenu->AddToViewport();
	
	if (IsValid(Player0))
	{
		Player0->SetShowMouseCursor(true);
		Player0->SetInputMode(FInputModeUIOnly());
	}
}

void ACodeTitleHUD::ShowOptionsMenu()
{
	APlayerController* Player0 = GetWorld()->GetFirstPlayerController();
	if (!IsValid(OptionsMenu))
	{
		OptionsMenu = CreateWidget<UUserWidget>(Player0, OptionsMenuWidgetClass);
	}
	OptionsMenu->AddToViewport();

	if (IsValid(Player0))
	{
		Player0->SetShowMouseCursor(true);
	}
}

void ACodeTitleHUD::ShowHostMenu()
{
	APlayerController* Player0 = GetWorld()->GetFirstPlayerController();
	if (!IsValid(HostMenu))
	{
		HostMenu = CreateWidget<UUserWidget>(Player0, HostMenuWidgetClass);
	}
	HostMenu->AddToViewport();
}

void ACodeTitleHUD::ShowServerMenu()
{
	APlayerController* Player0 = GetWorld()->GetFirstPlayerController();
	ServerMenu = CreateWidget<UUserWidget>(Player0, ServerMenuWidgetClass);
	ServerMenu->AddToViewport();
}

