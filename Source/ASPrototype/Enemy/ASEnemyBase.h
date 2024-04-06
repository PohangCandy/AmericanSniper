// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

//이동 지점 설정
//#include "Enemy/PatrolPath.h"
//각 에너미들을 판별하기 위해 ID값을 넣어줌
//#include "GenericTeamAgentInterface.h"

#include "ASEnemyBase.generated.h"

UENUM()
enum class EState
{
	Idle, 
	Walk,
	Attack, //돌격상태 
	Hurt,  //절뚝거리기
	Hidden, //숨은 상태
	Dead
};


UCLASS()
class ASPROTOTYPE_API AASEnemyBase : public ACharacter//, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AASEnemyBase();

	float SplineSpeed;
	float DistanceAlongSpline;

private:
	uint32 MaxHp;
	uint32 CurHp;
	uint8 Damage;
	EState CurState;

	class AASAIController* AiRef;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const override;
	void SetStateAnimation(EState NewState);

	//TArray<FVector> 값을 가진 Actor 클래스 포인터 
	UPROPERTY(EditAnywhere)
	TObjectPtr<class APatrolPath> PatrolPath;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TObjectPtr<class UStaticMeshComponent> Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = name)
	FString Name;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = AI)
	//int32 ID = 0;

	//에너미가 적대적인 존재인지 아닌지 판단하기 위해 넣음
	//virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//에너미가 적대적인 존재인지 아닌지 판단하기 위해 넣음 
	//FGenericTeamId TeamId;

	void SetState(EState NewState);
	EState GetState();

};

