// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/Pistol.h"

APistol::APistol()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> PistolRef(TEXT("/Game/MarketplaceBlockout/Modern/Weapons/Assets/Rifles/03/SM_Modern_Weapons_Rifle_03.SM_Modern_Weapons_Rifle_03"));
	{
		ensure(PistolRef.Object);
		if (PistolRef.Object)
		{
			WeaponModel->SetStaticMesh(PistolRef.Object);
		}
	}

	DamageMultiplier = 0.8;
	WeaponType = EWeaponType::Shoot;
	WeaponName = EWeaponName::Pistol;
	FireMode = EFireMode::SemiAuto;
	MagazineSize = 14;
}
