// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/Pistol.h"

APistol::APistol()
{
	DamageMultiplier = 0.8;
	WeaponType = EWeaponType::Shoot;
	WeaponName = EWeaponName::Pistol;
	FireMode = EFireMode::SemiAuto;
	MagazineSize = 14;
}
