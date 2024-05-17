// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ASWeaponBase.generated.h"

UENUM()
enum class EWeaponType
{
	Shoot,
	ProjectTile,
	Melee
};

UENUM()
enum class EWeaponName
{
	Unarmed,
	Pistol,
	AssaultRifle,
	Sniper
};

UENUM()
enum class EFireMode
{
	SemiAuto,
	FullAuto
};



UCLASS()
class ASPROTOTYPE_API AASWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AASWeaponBase();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TObjectPtr<class UStaticMeshComponent> WeaponModel;
protected:
	float DamageMultiplier;
	int MagazineSize;
	float Range;
	EWeaponType WeaponType;
	EWeaponName WeaponName;
	EFireMode FireMode;

};
