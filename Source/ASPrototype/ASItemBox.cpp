// Fill out your copyright notice in the Description page of Project Settings.


#include "ASItemBox.h"

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

}

// Called when the game starts or when spawned
void AASItemBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void AASItemBox::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AASItemBox::OnCharacterOverlap);
	UE_LOG(AS, Warning, TEXT("Post Item"));
}

// Called every frame
void AASItemBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AASItemBox::OnCharacterOverlap(UPrimitiveComponent* OverlappedCom, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(AS, Warning, TEXT("Collision with Item"));
}

