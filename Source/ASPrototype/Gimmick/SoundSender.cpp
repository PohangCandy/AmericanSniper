// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/SoundSender.h"

#include "Enemy/ASEnemyCharacter.h"
#include "Character/ASCharacterPlayer.h" 

#include "Perception/AISenseConfig_Hearing.h" 
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Game/ASGameMode.h"

// Sets default values
ASoundSender::ASoundSender()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASoundSender::BeginPlay()
{
	Super::BeginPlay();
	//Get Target
	Player = Cast<AASCharacterPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AASCharacterPlayer::StaticClass()));
	Enemy = Cast<AASEnemyCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), AASEnemyCharacter::StaticClass()));
}


void ASoundSender::NoiseCheck(FVector loc, TCHAR* tag)
{
	UGameplayStatics::PlaySoundAtLocation(GetWorld(), _sound, loc);
	UAISense_Hearing::ReportNoiseEvent(Player->GetWorld(), loc, 1.0f, Player, 0.0f, tag);
}


//void ASoundSender::NoiseCheck(AActor* actor, TCHAR* tag)
//{
//	FVector NoiseLocation = actor->GetActorLocation();
//	UGameplayStatics::PlaySoundAtLocation(GetWorld(), _sound, NoiseLocation);
//	UAISense_Hearing::ReportNoiseEvent(GetWorld(), NoiseLocation, 1.0f, this, 0.0f, tag);
//}


// Called every frame
void ASoundSender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

