// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_Lvl1_Noise.h"
#include "Gimmick/SoundSender.h"
#include "AI/Sound_tags.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISenseConfig_Hearing.h" 
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Character/ASCharacterPlayer.h"
#include "Enemy/ASEnemyCharacter.h"

void UAnimNotify_Lvl1_Noise::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	FVector loc = MeshComp->GetOwner()->GetActorLocation();

	//Player인가 ? 
	AASCharacterPlayer* Player = Cast<AASCharacterPlayer>(MeshComp->GetOwner());
	if (Player)
	{
		UAISense_Hearing::ReportNoiseEvent(Player->GetWorld(), loc, 1.0f, Player, 0.0f, tags::lvl1_Sound_tag);
	}

	//Enemy인가 ? 
	AASEnemyCharacter* Enemy = Cast<AASEnemyCharacter>(MeshComp->GetOwner());
	if (Enemy)
	{
		Enemy->PlaySound(Enemy->GunSound);
		UAISense_Hearing::ReportNoiseEvent(Enemy->GetWorld(), loc, 1.0f, Enemy, 0.0f, tags::lvl3_Sound_tag);
	}

	//USoundBase* _sound; //플레이어 sound()함수 하나 구현해서, 이곳에 호출 
	//UGameplayStatics::PlaySoundAtLocation(GetWorld(), _sound, Loc);
}
