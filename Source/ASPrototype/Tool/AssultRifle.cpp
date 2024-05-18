// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/AssultRifle.h"

AAssultRifle::AAssultRifle()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> AssultRifleRef(TEXT("/Game/MarketplaceBlockout/Modern/Weapons/Assets/Rifles/01/SM_Modern_Weapons_Rifle_01.SM_Modern_Weapons_Rifle_01"));
	{
		ensure(AssultRifleRef.Object);
		if (AssultRifleRef.Object)
		{
			WeaponModel->SetStaticMesh(AssultRifleRef.Object);
		}
	}


	DamageMultiplier = 1.5;
	WeaponType = EWeaponType::Shoot;
	WeaponName = EWeaponName::AssaultRifle;
	FireMode = EFireMode::FullAuto;
	MagazineSize = 90;
}
