// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/Sniper.h"

ASniper::ASniper()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SniperRef(TEXT("/Game/MarketplaceBlockout/Modern/Weapons/Assets/Rifles/06/SM_Modern_Weapons_Rifle_06.SM_Modern_Weapons_Rifle_06"));
	{
		ensure(SniperRef.Object);
		if (SniperRef.Object)
		{
			WeaponModel->SetStaticMesh(SniperRef.Object);
		}
	}

	DamageMultiplier = 0.8;
	WeaponType = EWeaponType::Shoot;
	WeaponName = EWeaponName::Sniper;
	FireMode = EFireMode::SemiAuto;
	MagazineSize = 14;
}
