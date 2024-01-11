// Fill out your copyright notice in the Description page of Project Settings.


#include "Title/CodeTitleHUD.h"
#include "Blueprint/UserWidget.h"
#include "Containers/UnrealString.h"

void ACodeTitleHUD::BeginPlay()
{
	Super::BeginPlay();
	ShowMainMenu();
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
	FString string = FString::Printf(TEXT("%s"), MainMenu->GetName());
	FText text = FText::FromString(string);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, FString::Printf(TEXT("%s"), text.ToString()));
}

void ACodeTitleHUD::ShowOptionsMenu()
{
	APlayerController* Player0 = GetWorld()->GetFirstPlayerController();
	if (!IsValid(OptionsMenu))
	{
		OptionsMenu = CreateWidget<UUserWidget>(Player0, OptionsMenuWidgetClass);
	}
	OptionsMenu->AddToViewport();
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
