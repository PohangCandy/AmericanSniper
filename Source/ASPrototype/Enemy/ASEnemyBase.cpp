// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ASEnemyBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
//BB정보 얻기 위해 
#include "AI/ASAIController.h"
#include "UI/ASDetectWidget.h"

#include "Components/WidgetComponent.h"

#include "Tool/Pistol.h"
#include "Tool/AssultRifle.h"
#include "Tool/Sniper.h"

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
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ASEnemy"));

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	//GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

	//Widget
	QuestionMark = CreateDefaultSubobject<UWidgetComponent>(TEXT("QuestionMarkWidget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> QuestionMarkRef(TEXT("/Game/UI/WB_QuestionMark_UI.WB_QuestionMark_UI_C"));
	ensure(QuestionMarkRef.Class);
	if (QuestionMarkRef.Class)
	{
		QuestionMark->SetWidgetClass(QuestionMarkRef.Class);
		QuestionMark->SetWidgetSpace(EWidgetSpace::Screen);
		QuestionMark->SetDrawSize(FVector2D(30.0f, 30.0f));
		QuestionMark->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		QuestionMark->SetupAttachment(GetMesh());
		QuestionMark->AddRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));
		QuestionMark->SetRelativeLocation(FVector(0.0f, 0.0f, 210.0f));
		QuestionMark->SetHiddenInGame(true);
	}


	//Stats
	MaxHp = 100;
	CurHp = MaxHp;
	Damage = 10;
	CurState = EState::Idle;

	//스켈레톤 + 애니메이션 적용 
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CharaterMeshRef(TEXT("/Script/Engine.SkeletalMesh'/Game/ASPrototype/Enemy/Enemy/Meshes/SK_HeavyGSoldier_simple.SK_HeavyGSoldier_simple'"));
	if (CharaterMeshRef.Object)
	{
		GetMesh()->SetSkeletalMesh(CharaterMeshRef.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimInstanceClassRef(TEXT("/Script/Engine.AnimBlueprint'/Game/ASPrototype/Enemy/Enemy/ABP_TempEnemy.ABP_TempEnemy_C'"));
	//ensure(AnimInstanceClassRef.Class);
	if (AnimInstanceClassRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimInstanceClassRef.Class);
	}

	//무기 세팅 
	CurrentWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CurrentWeapon"));
	Pistol= CreateDefaultSubobject<APistol>(TEXT("Pistol"));
	AssultRifle = CreateDefaultSubobject<AAssultRifle>(TEXT("AssultRifle"));
	ensure(Pistol);
	ensure(AssultRifle);
	CurrentWeapon->SetStaticMesh(AssultRifle->WeaponModel->GetStaticMesh());
	CurrentWeapon->SetupAttachment(GetMesh(), FName(TEXT("Weapon_Socket")));
	WeaponInfo = AssultRifle;
	ensure(WeaponInfo);

	WalkSpeed = 300.0f;
	RunSpeed = 500.0f;
}

void AASEnemyBase::Attack()
{
	const float DelayTime = PlayAnimMontage(AttackMontage);
	AttackEnd(DelayTime);
}

void AASEnemyBase::AttackEnd(const float InDelayTime)
{
	FTimerHandle myTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(myTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			OnAttackEnd.Broadcast();
			// 타이머 초기화
			GetWorld()->GetTimerManager().ClearTimer(myTimerHandle);
		}), InDelayTime, false);
}



// Called when the game starts or when spawned
void AASEnemyBase::BeginPlay()
{	
	Super::BeginPlay();
	AiRef = Cast<AASAIController>(GetOwner());
	//무기변경 문제, None이 들어옴
	//WeaponInfo = Pistol;
	//CurrentWeapon->SetStaticMesh(Pistol->WeaponModel->GetStaticMesh());
	//CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepWorldTransform, FName(TEXT("Weapon_Socket")));
}

// Called every frame
void AASEnemyBase::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
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

void AASEnemyBase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
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
		WeaponInfo->WeaponModel->SetHiddenInGame(true);
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
		//AiRef->RangeSizeDown();
		break;
	case EState::Alert:
		GetCharacterMovement()->MaxWalkSpeed = 150.0f;
		break;
	case EState::Chasing:
		WeaponInfo->WeaponModel->SetHiddenInGame(false);
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed; // 상태변화에서 가장 의미
		//AiRef->RangeSizeUP();
		break;

	case EState::Attack:
		WeaponInfo->WeaponModel->SetHiddenInGame(false);
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		//AiRef->RangeSizeUP();
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


