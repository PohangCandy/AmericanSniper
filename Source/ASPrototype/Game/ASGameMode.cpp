// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ASGameMode.h"

AASGameMode::AASGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/ASPrototype/BluePrint/BP_Player.BP_Player_C'"));
	//DefaultPawnClass Setting
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}
	//PlayerControllerClass Setting
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ASPrototype.ASPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}
}
