// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ASAIController.generated.h"

//DECLARE_MULTICAST_DELEGATE_OneParam(FInitAIOnChanged, AASAIController* ref)
/**
 * 
 */
UENUM()
enum class CurDetectSituation
{

	NoneInRange, //범위안에 없는 상황
	PlayerInRange, // 범위안에 있는 상황
	PlayerGetOutOfRange, // 범위안에 들어갔다 나간 상황
	PlayerIsDetected,  // 발각된 상황

};
UCLASS()
class ASPROTOTYPE_API AASAIController : public AAIController
{
	GENERATED_BODY()

public:
	CurDetectSituation CurSituation;
	AActor* GetDetectedPlayer();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	AASAIController();
	virtual void OnPossess(APawn* InPawn) override;
	void RunAI();
	void StopAI();
	void CheckPlayer(AActor* P);

	//BB 데이터 정보 
	void SetBB_Target(UObject* object);
	UObject* GetBB_Target();

	void SetBB_IsDetect(bool b);
	bool GetBB_IsDetect();

	void SetBB_PatrolLoc(FVector vector);
	FVector GetBB_PatrolLoc();

	void SetBB_PathLoc(FVector vector);
	FVector GetBB_PathLoc();

	void SetBB_AttackRange(FVector vector);
	FVector GetBB_AttackRange();

	void StartDetection();
	void StopDetection();
	UFUNCTION()
	void OnPawnDetected(const TArray<AActor*>& DetectedPawns);

	float AISightRadius = 400.f;
	float LoseSightRadius = 500.f;
	float AIFieldOfView = 90.f;

	void RangeSizeDown();
	void RangeSizeUP();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	TObjectPtr<class UWidgetComponent> DetectBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AttackRange);
	float AttackRange;

	class UASDetectWidget* getWidget();

	float DistanceDifference_Value;
	//virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }

	//FInitAIOnChanged AIOnChanged;
	//AASAIController* ReturnAIRef(AASAIController*ref);

	//전방선언
	class AASCharacterPlayer* PlayerRef;

	float DetectionLevel;
	float MaxLevel;

private:
	class UAISenseConfig_Sight* SightConfig;
	
	void SetupPerception();


	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBAsset;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTAsset;

	//전방선언
	class UASDetectWidget* UiRef;
	class AASEnemyCharacter* EnemyRef;

	bool IsTargetInRange;

protected:

	//FGenericTeamId TeamId;
	////각 Actor의 id를 비교하여, 현재 Actor가 적인지 사물인지 팀인지 알려준다. 
	//virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
};
