// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CodeTitleHUD.generated.h"

/**
 * 
 */
UCLASS()
class TITLE2LOBBY_API ACodeTitleHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> MainMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* MainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> OptionsMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* OptionsMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> HostMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* HostMenu;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> ServerMenuWidgetClass;

	UPROPERTY(BlueprintReadWrite)
	UUserWidget* ServerMenu;

public:
	UFUNCTION(BlueprintCallable)
	void ShowMainMenu();

	UFUNCTION(BlueprintCallable)
	void ShowOptionsMenu();

	UFUNCTION(BlueprintCallable)
	void ShowHostMenu();

	UFUNCTION(BlueprintCallable)
	void ShowServerMenu();

};
