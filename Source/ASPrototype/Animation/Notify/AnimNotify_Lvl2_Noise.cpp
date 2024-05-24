// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/Notify/AnimNotify_Lvl2_Noise.h"
#include "Gimmick/SoundSender.h"
#include "AI/Sound_tags.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Character/ASCharacterPlayer.h" 
void UAnimNotify_Lvl2_Noise::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);

	AudioObject = NewObject<ASoundSender>();
	FVector loc = MeshComp->GetOwner()->GetActorLocation();
	AudioObject->NoiseCheck(loc, tags::lvl2_Sound_tag);
}
