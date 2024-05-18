// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ASEnemyCharacter.h"
#include "AI/ASAIController.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/DamageEvents.h"
#include "Engine/EngineTypes.h"

AASEnemyCharacter::AASEnemyCharacter()
{
	AIControllerClass = AASAIController::StaticClass();
	
}
float AASEnemyCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	//EPhysicalSurface PhysicalSurface = UGameplayStatics::GetSurfaceType(HitResult);
	//FString BoneName;
	//switch (PhysicalSurface)
	//{
	//case SurfaceType1:
	//	//BoneName = FString::FromInt(PhysicalSurface);
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT(" hitting: Head")));
	//	break;
	//case SurfaceType2:
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT(" hitting: ArmsAndLimb")));
	//	break;
	//case SurfaceType3:
	//	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT(" hitting: Body")));
	//	break;
	//default:
	//	break;
	//}

	return DamageAmount;
}


void AASEnemyCharacter::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
}


void AASEnemyCharacter::GetHitResult(FHitResult HitReuslt)
{
	this->HitResult = HitReuslt;
}

bool AASEnemyCharacter::AttackCheck()
{
	FHitResult OutHit;
	FDamageEvent DamageEvent;
	FVector Start = WeaponInfo->WeaponModel->GetComponentLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector End = (Start + (ForwardVector * 1000.0f));

	FCollisionQueryParams CollisionParams;

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_GameTraceChannel4, CollisionParams); //   EnemyAttack 

	if (OutHit.GetActor() == AiRef->GetPlayer())
	{

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::Printf(TEXT(" hitting: %s"),
			*OutHit.GetActor()->GetName()));
		OutHit.GetActor()->TakeDamage(10.0f, DamageEvent,GetController(),this);
		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT(" hitting: Others ")));
		return false;
	}
}

void AASEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

}






