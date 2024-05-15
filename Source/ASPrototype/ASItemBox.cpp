// Fill out your copyright notice in the Description page of Project Settings.


#include "ASItemBox.h"
#include "Character/ASCharacterPlayer.h"
#include "UI/DetectItemWidget.h"

// Sets default values
AASItemBox::AASItemBox()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	Box = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BOX"));

	RootComponent = Trigger;
	Box->SetupAttachment(RootComponent);

	Trigger->SetBoxExtent(FVector(40.0f, 42.0f, 30.0f));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_BOX(TEXT("/Game/MarketplaceBlockout/Modern/Weapons/Assets/Rifles/01/SM_Modern_Weapons_Rifle_01.SM_Modern_Weapons_Rifle_01"));
	if (SM_BOX.Succeeded())
	{
		Box->SetStaticMesh(SM_BOX.Object);
	}

	Box->SetRelativeLocation(FVector(0.0f, -3.5f, -30.0f));

	Trigger->SetCollisionProfileName(TEXT("ItemBox"));
	Box->SetCollisionProfileName(TEXT("NoCollision"));

	UE_LOG(AS, Warning, TEXT("Make Item"));


	Effect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EFFECT"));
	Effect->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UParticleSystem> P_OVERLAP(TEXT("/Game/InfinityBladeGrassLands/Effects/FX_Mobile/ICE/combat/P_Buff_ShoutFreeze_02.P_Buff_ShoutFreeze_02"));
	if (P_OVERLAP.Succeeded())
	{
		Effect->SetTemplate(P_OVERLAP.Object);
		Effect->bAutoActivate = false;
	}


	//static ConstructorHelpers::FClassFinder<UDetectItemWidget> UI_Item_C(TEXT("/Game/UI/WB_ItemDetect.WB_ItemDetect"));
	//ItemWidgetClass = UI_Item_C.Class;

}

// Called when the game starts or when spawned
void AASItemBox::BeginPlay()
{
	Super::BeginPlay();
	/*ItemWidget = CreateWidget<UDetectItemWidget>(this, ItemWidgetClass);*/
	
}

void AASItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AASItemBox::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AASItemBox::OutCharacterOverlap);
	UE_LOG(AS, Warning, TEXT("Post Item"));
}

// Called every frame
void AASItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AASItemBox::SetPlayerCanGripUI()
{

}

void AASItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedCom, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(AS, Warning, TEXT("Collision with Item"));

	auto ABCharacter = Cast<AASCharacterPlayer>(OtherActor);
	if (nullptr != ABCharacter )
	{
			Effect->Activate(true);
			//Effect->OnSystemFinished.AddDynamic(this, &AASItemBox::OnEffectFinished);
			//ItemWidget->AddToViewport();
	}
}

void AASItemBox::OutCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(AS, Warning, TEXT("Out from Collision"));
	Effect->Deactivate();
	//ItemWidget->RemoveFromParent();
}

void AASItemBox::OnEffectFinished(UParticleSystemComponent* PSystem)
{
}


