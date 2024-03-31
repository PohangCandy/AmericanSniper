// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ASCharacterBase.h"
#include "Player/ASPlayerController.h"
#include "Character/ASCharacterStatComponent.h"
//충돌,움직임 헤더파일
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
//AnimInstance클래스와 연결
#include "Animation/ASAnimInstance.h"

// Sets default values
AASCharacterBase::AASCharacterBase()
{
	//Pawn
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//Capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("ABCapsule"));

	//Movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	//Mesh
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -100.0f), FRotator(0.0f, -90.f, 0.0f));
	GetMesh()->SetAnimationMode(EAnimationMode::AnimationBlueprint);
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));

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

	MaxHp = 100;
	CurHp = MaxHp;
	LowHp = 40;
	Damage = 10;
	CurState = State::None;

	//static ConstructorHelpers::FClassFinder<AASPlayerController> Controll_C(TEXT("/Script/ASPrototype.ASPlayerController_C"));
	//CurplayerControllerClass = Controll_C.Class;
	//PlayerController = Cast<AASPlayerController>(GetWorld()->GetFirstPlayerController());
	//PlayerController->ConnectUIwithData();

	CharacterStat = CreateDefaultSubobject<UASCharacterStatComponent>(TEXT("CHARACTERSTAT"));

}

void AASCharacterBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	OnHpChanged.Broadcast();
}

void AASCharacterBase::SetDead()
{	
	SetState(State::Dead);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	SetActorEnableCollision(false);

	//Dead Animation
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->StopAllMontages(0.0f);
	AnimInstance->Montage_Play(DeadMontage);

	GetWorld()->GetTimerManager().SetTimer(DeadTimerHandle, FTimerDelegate::CreateLambda([&]()
		{
			Destroy();
		}), 2.0f, false);
}

int AASCharacterBase::GetHp()
{
	return CurHp;
}

float AASCharacterBase::GetHpratio()
{
	if (CurHp <= 0)
	{
		return 0.0f;
	}
	float HpRatio = (float)CurHp / (float)MaxHp;
	return HpRatio;
}

void AASCharacterBase::SetHp(int Hp)
{
	CurHp = Hp;
}

void AASCharacterBase::GetDamaged(int damage)
{
	int Hp = GetHp() - damage;
	SetHp(Hp);

	OnHpChanged.Broadcast();
}

void AASCharacterBase::SetState(State NewState)
{
	CurState = NewState;
	UASAnimInstance* animinstance = Cast<UASAnimInstance>(GetMesh()->GetAnimInstance());
	animinstance->StateHandler(NewState);
}


State AASCharacterBase::GetState()
{
	return CurState;
}



void AASCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}
