// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/TestEnemy.h"
#include "Character/ASCharacterPlayer.h"
#include "Engine/GameEngine.h"

// Sets default values
ATestEnemy::ATestEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

//��class�� �����ϸ� �ȵ�, �÷��̾� hp�� ��ȭ�� �÷��̾� Ŭ������ �ؾ���. 
//void ATestEnemy::NotifyActorBeginOverlap(AActor* OtherActor)
//{	
//	AASCharacterBase* playerRef = Cast<AASCharacterBase>(OtherActor);
//	if (playerRef)
//	{
//		int CurHp = playerRef->GetHp();
//		CurHp = FMath::Clamp(CurHp - damage, 0, 100);
//		playerRef->SetHp(CurHp);
//		FString text = FString::Printf(TEXT("Player Hp : %d"), CurHp);
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, text);
//		if (CurHp <= 0)
//		{
//			playerRef->SetDead();
//		}
//	}
//}



