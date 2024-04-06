// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ASEnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
//BB정보 얻기 위해 
#include "AI/ASAIController.h"


// Sets default values
AASEnemyBase::AASEnemyBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	//Stats
	MaxHp = 100;
	CurHp = MaxHp;
	Damage = 10;
	CurState = EState::Idle;

	//스켈레톤 + 애니메이션 적용 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharaterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/AnimStarterPack/UE4_Mannequin/Mesh/SK_Mannequin.SK_Mannequin'"));
	if (CharaterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharaterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Script/Engine.AnimBlueprint'/Game/ASPrototype/Animation/ABP_CharacterAnimation.ABP_CharacterAnimation_C'"));
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}



    //DetectBar->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));


	//Weapon Setting
	Gun = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun"));
	Gun->SetupAttachment(RootComponent);

	//생성자에서 캐스팅 시 문제발생 (원인 모름) <-
	//AActor* owner = GetOwner();
	//ensure(owner);
	//AiRef = Cast<AASAIController>(GetOwner());
	//ensure(AiRef);

}

// Called when the game starts or when spawned
void AASEnemyBase::BeginPlay()
{	
	AiRef = Cast<AASAIController>(GetOwner());
	Super::BeginPlay();
}

// Called every frame
void AASEnemyBase::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

	//이 함수는 task에 넣는게 바람직해 보임 . enemy를 식별하지 못했을 때만 동작해야 하므로.
	//DistanceAlongSpline = (SplineSpeed * DeltaTime) + DistanceAlongSpline;
	//FVector NewLoc = Spline->GetLocationAtDistanceAlongSpline(DistanceAlongSpline, ESplineCoordinateSpace::Local);
	//AiRef->SetBB_PathLoc(NewLoc);
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("LOCATION: %f"), DistanceAlongSpline));
}

// Called to bind functionality to input
void AASEnemyBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AASEnemyBase::GetActorEyesViewPoint(FVector& OutLocation, FRotator& OutRotation) const
{
	OutLocation = GetMesh()->GetSocketLocation("HeadSocket");
	OutRotation = GetMesh()->GetSocketRotation("HeadSocket");
}

void AASEnemyBase::SetState(EState NewState)
{
	CurState = NewState;
	SetStateAnimation(CurState);
}

EState AASEnemyBase::GetState()
{
	return EState();
}

void AASEnemyBase::SetStateAnimation(EState NewState)
{
	AiRef = Cast<AASAIController>(GetOwner());
	switch (NewState)
	{	
	case EState::Idle:
		Gun->SetHiddenInGame(true);
		GetCharacterMovement()->MaxWalkSpeed = 300.f;
		AiRef->RangeSizeDown();
		break;

	case EState::Walk:
		Gun->SetHiddenInGame(true);
		GetCharacterMovement()->MaxWalkSpeed = 300.f; //이것만 상태변화에서 가장 의미있어보임.
		AiRef->RangeSizeDown();
		break;

	case EState::Attack:
		Gun->SetHiddenInGame(false);
		GetCharacterMovement()->MaxWalkSpeed = 500.f;
		AiRef->RangeSizeUP();

		break;

	case EState::Hurt:
		break;

	case EState::Hidden:
		break;

	case EState::Dead:
		break;

	default:
		break;
	}
}


