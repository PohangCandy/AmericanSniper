// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Perception/AISense.h"
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
	TargetInRange, // 범위안에 있는 상황
	TargetGetOutOfRange, // 범위안에 들어갔다 나간 상황
	TargetIsSuspected, //의심 받는 상황
	TargetIsDetected,  // 발각된 상황
	
};
UCLASS()
class ASPROTOTYPE_API AASAIController : public AAIController
{
	GENERATED_BODY()

public:
	CurDetectSituation CurSituation;
	AActor* GetPlayer();

	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;

	AASAIController();
	virtual void OnPossess(APawn* InPawn) override;
	void RunAI();
	void StopAI();
	void CheckPlayer(AActor* P);

	void IncreaseDetectionLVL();
	void DecreaseDetectionLVL();

	//BB 데이터 정보 
	void SetBB_LastKnownPosition(FVector vector);
	FVector GetBB_LastKnownPosition();

	void SetBB_Target(UObject* object);
	UObject* GetBB_Target();

	void SetBB_IsDetect(bool b);
	bool GetBB_IsDetect();

	void SetBB_IsAlert(bool b);
	bool GetBB_IsAlert();

	void SetBB_PatrolLoc(FVector vector);
	FVector GetBB_PatrolLoc();

	void SetBB_PathLoc(FVector vector);
	FVector GetBB_PathLoc();

	void SetBB_AttackRange(FVector vector);
	FVector GetBB_AttackRange();

	void SetBB_CanShootTarget(bool b);
	bool GetBB_CanShootTarget();



	void StartDetection();
	void StopDetection();
	UFUNCTION()
	void OnPawnDetected(AActor* DetectedPawn, const  FAIStimulus Stimulus);
	//void OnSoundDetected(const AActor* Actor, const FAIStimulus Stimulus);
	UFUNCTION()
	//void OnTargetPerceptionUpdated_Delegate(AActor* Actor, const  FAIStimulus Stimulus);
	//void On_Updated(TArray<AActor*> const& updated_Actors);
	void On_Updated(AActor* DetectedPawn, const  FAIStimulus Stimulus);
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
	//bool EventOnBySound;

	FVector LastKnownPosition;

private:
	// AI구현을 위한 AIPerceptionComponent 선언
	UPROPERTY(VisibleDefaultsOnly, Category = Enemy)
	class UAIPerceptionComponent* AIPerComp;
	class UAISenseConfig_Sight* SightConfig;
	class UAISenseConfig_Hearing* HearingConfig;
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
