// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ASCharacterPlayer.h"
#include "Animation/ASAnimInstance.h"
#include "Player/ASPlayerState.h"
#include "ASWeapon.h"
//ī�޶� �������
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
//�Է¿��� �������
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
//�ɸ��� ������ �������
#include"GameFramework/CharacterMovementComponent.h"
//������Ʈ �浹 �������
#include "Components/CapsuleComponent.h"
//�Ҹ������� ���� ���а���
#include "Math/UnrealMathUtility.h"


AASCharacterPlayer::AASCharacterPlayer()
{
	//ī�޶�
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	//SnipSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SnipSpringArm"));
	//SnipSpringArm->TargetArmLength = 50.0f;
	//SnipSpringArm->bUsePawnControlRotation = true;

	//SnipCam = CreateDefaultSubobject<UCameraComponent>(TEXT("SnipCam"));
	//SnipCam->SetupAttachment(SnipSpringArm, USpringArmComponent::SocketName);
	//SnipCam->bUsePawnControlRotation = false;

	//���� ���� ������ ������
	MinSoundRange = 100.0f;
	MaxSoundRange = 300.0f;
	WalkSoundMultiplier = 1.0f;
	RunSoundMultiplier = 3.0f;

	// �Ҹ� ���� ������Ʈ ���� �� ����
	SoundRangeCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("SoundRangeCapsule"));
	SoundRangeCapsule->SetupAttachment(RootComponent);
	SoundRangeCapsule->SetCollisionProfileName(TEXT("SoundRange")); 
	SoundRangeCapsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly); // �浹 �˻縸 ����
	SoundRangeCapsule->SetCapsuleSize(50.0f, 20.0f); // ũ�� ���� (������, ����)
	SoundRangeCapsule->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f)); // ��� ��ġ ����


	ClothesMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ClothesMesh"));
	ClothesMesh->SetupAttachment(RootComponent);
	//�� ������ �ӽ� ����
	ClothesMesh->SetRelativeLocation(FVector(- 1.0f, 6.0f, -115.0f));
	ClothesMesh->SetRelativeRotation(FRotator(0.0f, -60.0f,0.0f));
	ClothesMesh->SetRelativeScale3D(FVector(1.1f,1.1f,1.1f));

	//�Է�
	static ConstructorHelpers::FObjectFinder<UInputMappingContext> InputMappingContextRef(TEXT("/Game/ASPrototype/Input/IMC_Third.IMC_Third"));
	if (InputMappingContextRef.Object)
	{
		DefaultMappingContext = InputMappingContextRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionJumpRef(TEXT("/Game/ASPrototype/Input/IA_Jump.IA_Jump"));
	if (nullptr != InputActionJumpRef.Object)
	{
		JumpAction = InputActionJumpRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionMoveRef(TEXT("/Game/ASPrototype/Input/IA_Move.IA_Move"));
	if (nullptr != InputActionMoveRef.Object)
	{
		MoveAction = InputActionMoveRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionLookRef(TEXT("/Game/ASPrototype/Input/IA_Look.IA_Look"));
	if (nullptr != InputActionLookRef.Object)
	{
		LookAction = InputActionLookRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionWearRef(TEXT("/Game/ASPrototype/Input/IA_Wear.IA_Wear"));
	if (nullptr != InputActionWearRef.Object)
	{
		WearAction = InputActionWearRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UInputAction> InputActionRunRef(TEXT("/Game/ASPrototype/Input/IA_Run.IA_Run"));
	if (nullptr != InputActionRunRef.Object)
	{
		RunAction = InputActionRunRef.Object;
	}

	SoundRangeCapsule->SetVisibility(true);
	SoundRangeCapsule->SetHiddenInGame(false);

	
	FName WeaponAttachmentSocket(TEXT("hand_rSocket_attachment"));
	FName WeaponSocket(TEXT("hand_rSocket"));
	if (GetMesh()->DoesSocketExist(WeaponAttachmentSocket))
	{
		//WeaponAttachment = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponAttachment"));
		//static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Sight(TEXT("/Game/BLS_Nomad_SMG_Content/Meshes/Attachments/SM_Reflex_Sight.SM_Reflex_Sight"));
		//if (SK_Sight.Succeeded())
		//{
		//	WeaponAttachment->SetSkeletalMesh(SK_Sight.Object);
		//}
		//WeaponAttachment->SetupAttachment(GetMesh(), WeaponAttachmentSocket);

		//if (GetMesh()->DoesSocketExist(WeaponSocket))
		//{
		//	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
		//	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SK_Rifle_01(TEXT("/Game/MarketplaceBlockout/Modern/Weapons/Assets/Rifles/01/SKM_Modern_Weapons_Rifle_01.SKM_Modern_Weapons_Rifle_01"));
		//	if (SK_Rifle_01.Succeeded())
		//	{
		//		Weapon->SetSkeletalMesh(SK_Rifle_01.Object);
		//	}
		//	Weapon->SetupAttachment(GetMesh(), WeaponSocket);
		//}

		WeaponAttachment = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponAttachment"));
		static ConstructorHelpers::FObjectFinder<UStaticMesh> SK_Sight(TEXT("/Game/BLS_Nomad_SMG_Content/Meshes/Attachments/SM_Reflex_Sight.SM_Reflex_Sight"));
		if (SK_Sight.Succeeded())
		{
			WeaponAttachment->SetStaticMesh(SK_Sight.Object);
		}
		WeaponAttachment->SetupAttachment(GetMesh(), WeaponAttachmentSocket);
	}
	
}

void AASCharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CurrentSpeed = GetVelocity().Size();

	UpdateSoundRange();
}

void AASCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	FName WeaponSocket(TEXT("hand_rSocket"));
	auto CurWeapon = GetWorld()->SpawnActor<AASWeapon>(FVector::ZeroVector, FRotator::ZeroRotator);
	if (CurWeapon != nullptr)
	{
		CurWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, WeaponSocket);
		CurrentWeapon = CurWeapon;
	}

	//�Է� ���νý����� ��Ʈ�Ѱ� ���� 
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (nullptr != Subsystem)
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
		//Subsystem->RemoveMappingContext(DefaultMappingContext); �ʿ� �� ���� ���⵵ ���� 
	}
	UE_LOG(LogTemp, Warning, TEXT("GetController"));
	playerController = CastChecked<AASPlayerController>(GetController());
	// SoundRangeCapsule�� ��Ƽ������ ������
	UMaterialInterface* Material = SoundRangeCapsule->GetMaterial(0);

	// ��Ƽ������ ��ȿ���� Ȯ�� �� ���� ����
	if (Material)
	{
		// ������ ���������� ����
		FLinearColor NewColor = FLinearColor::Red;

		// ��Ƽ���� �ν��Ͻ� ���� �� �Ӽ� ����
		UMaterialInstanceDynamic* DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);
		DynamicMaterial->SetVectorParameterValue(TEXT("Color"), NewColor);
	
		// ��Ƽ���� ����
		SoundRangeCapsule->SetMaterial(0, DynamicMaterial);
	}
}

void AASCharacterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UE_LOG(LogTemp,Warning,TEXT("SetUPInput"));
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AASCharacterBase::Shoot);
	//PlayerInputComponent->BindAction(TEXT("SceneChange"), EInputEvent::IE_Pressed, playerController, &AASPlayerController::UIScreenChange);
	//PlayerInputComponent->BindAction(TEXT("SceneChange"), EInputEvent::IE_Pressed, this, &AASPlayerController::UIScreenChange);
	
	PlayerInputComponent->BindAction(TEXT("SceneChange"), EInputEvent::IE_Pressed, this, &AASCharacterPlayer::ChangeUI);
	PlayerInputComponent->BindAction(TEXT("ZoomIn"), EInputEvent::IE_Pressed, this, &AASCharacterBase::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("ZoomOut"), EInputEvent::IE_Pressed, this, &AASCharacterBase::ZoomOut);




	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AASCharacterBase::Reload);
	PlayerInputComponent->BindAction(TEXT("Heal"), EInputEvent::IE_Pressed, this, &AASCharacterBase::Heal);
	PlayerInputComponent->BindAction(TEXT("GetDamage"), EInputEvent::IE_Pressed, this, &AASCharacterBase::TestingGetDamage);


	//���� �Է� �ý��� ���
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	//�Է� �������ؽ�Ʈ������ �׼��̶� �Լ��� ����
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AASCharacterPlayer::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AASCharacterPlayer::Look);
	EnhancedInputComponent->BindAction(WearAction, ETriggerEvent::Triggered, this, &AASCharacterPlayer::Wear);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Triggered, this, &AASCharacterPlayer::SprintStart);
	EnhancedInputComponent->BindAction(RunAction, ETriggerEvent::Completed, this, &AASCharacterPlayer::SprinEnd);

}

void AASCharacterPlayer::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	FString text = FString::Printf(TEXT("Enemy Find You!"));
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, text);
}

void AASCharacterPlayer::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{	
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	//if(EnemyRef)
	//{
	//	//int Hp = FMath::Clamp(GetHp() - (EnemyRef->damage), 0, 100);
	//	//SetHp(Hp);
	//	GetDamaged(EnemyRef->damage);
	//	int Hp = GetHp();
	//	FString text = FString::Printf(TEXT("Player Hp : %d"), Hp);
	//	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, text);
	//	if (Hp > 0 && Hp <= LowHp)
	//	{
	//		SetState(State::Hurt);
	//	}
	//	if (Hp <= 0)
	//	{
	//		SetDead();
	//	}
	//}
}


void AASCharacterPlayer::OnFire()
{

	//FHitResult OutHit;
	//FVector Start = CurrentWeapon->GetActorLocation();

	//FVector ForwardVector = 
}

//������ ����
void AASCharacterPlayer::Move(const FInputActionValue& Value) 
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.X);
	AddMovementInput(RightDirection, MovementVector.Y);
}

void AASCharacterPlayer::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);

	USkeletalMesh* PlayerMesh = GetMesh()->GetSkeletalMeshAsset();
	//PlayerMesh->setbonetr
}

void AASCharacterPlayer::SprintStart(const FInputActionValue& Value)
{	
	GetCharacterMovement()->MaxWalkSpeed = 1000;
}

void AASCharacterPlayer::SprinEnd(const FInputActionValue& Value)
{
	GetCharacterMovement()->MaxWalkSpeed = 500;
}

void AASCharacterPlayer::Wear(const FInputActionValue& Value)	
{	
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(SearchMontage);

	static const FString OutfitPath = TEXT("/Game/ASPrototype/Mesh/AS_Pullover.AS_Pullover");
	// Soft Object Reference�� ����Ͽ� �� �ε�
	static TSoftObjectPtr<USkeletalMesh> NewClothesRef(OutfitPath);
	USkeletalMesh* NewClothesMesh = NewClothesRef.LoadSynchronous();

	if (NewClothesMesh)
	{
		if (ClothesMesh)
		{
			ClothesMesh->SetSkeletalMesh(NewClothesMesh);
		}
	}

	FString text = FString::Printf(TEXT("Wearing.."));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, text);
}



void AASCharacterPlayer::UpdateSoundRange()
{	
	// ���� ũ��
	float Radius, Height;
	SoundRangeCapsule->GetScaledCapsuleSize(Radius, Height);
	FVector CurrentSize = FVector(Radius, Radius, Height);

	float SpeedMultiplier = CurrentSpeed > 0 ? ((GetCharacterMovement()->MaxWalkSpeed>500) ? RunSoundMultiplier : WalkSoundMultiplier) : 0.0f;
	float NewSoundRange = MinSoundRange + (MaxSoundRange - MinSoundRange) * SpeedMultiplier;
	FVector TargetSize = FVector(NewSoundRange, NewSoundRange, Height); // ���̴� ���������� ����
	
	// ���� �������� ������ �ε巴�� ����  _
	FVector LerpedSize = FMath::Lerp(CurrentSize, TargetSize, GetWorld()->DeltaTimeSeconds * 1.0);

	// ũ�� ����
	SoundRangeCapsule->SetCapsuleSize(LerpedSize.X, LerpedSize.Y);
	
}

void AASCharacterPlayer::ChangeUI()
{
	playerController->UIScreenChange();
	auto AnimInstance = Cast<UASAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;
	AnimInstance->SwitchSnipAnim();
	//SwitchSnip.Broadcast();
}








