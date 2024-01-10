// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerInfo.generated.h"


USTRUCT(Atomic, BlueprintType)
struct FPlayerInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FText MyPlayerName;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSoftObjectPtr<UTexture2D> MyPlayerLogo;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSoftObjectPtr<ACharacter> MyPlayerCharacter;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    TSoftObjectPtr<UTexture2D> MyPlayerCharacterImage;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FText MyPlayerStatus;// = FText::FromString("Not Ready");

    //UPROPERTY(BlueprintReadWrite, EditAnywhere)
    //SoftObjectPtr<UTexture2D> ImageArray[10] = { 0 ,};
    //TArray<UTexture2D*> TextureList;

    FPlayerInfo()
    {
        FSoftObjectPath Logo(TEXT("/Script/Engine.Texture2D'/Game/Textures/Logo/Logo01.Logo01'"));
        MyPlayerLogo = Logo;
        MyPlayerStatus = FText::FromString("Not Ready");
    }
};
class TITLE2LOBBY_API PlayerInfo
{
public:
	PlayerInfo();
	~PlayerInfo();
};
