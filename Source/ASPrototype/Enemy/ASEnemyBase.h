// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

//�̵� ���� ����
//#include "Enemy/PatrolPath.h"
//�� ���ʹ̵��� �Ǻ��ϱ� ���� ID���� �־���
//#include "GenericTeamAgentInterface.h"

#include "ASEnemyBase.generated.h"

UENUM()
enum class EState
{
	Idle, 
	Walk,
	Attack, //���ݻ��� 
	Hurt,  //���ҰŸ���
	Hidden, //���� ����
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

	//TArray<FVector> ���� ���� Actor Ŭ���� ������ 
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

	//���ʹ̰� �������� �������� �ƴ��� �Ǵ��ϱ� ���� ����
	//virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//���ʹ̰� �������� �������� �ƴ��� �Ǵ��ϱ� ���� ���� 
	//FGenericTeamId TeamId;

	void SetState(EState NewState);
	EState GetState();

};
