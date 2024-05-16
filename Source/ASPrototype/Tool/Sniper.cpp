// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/Sniper.h"

ASniper::ASniper()
{
	DamageMultiplier = 0.8;
	WeaponType = EWeaponType::Shoot;
	WeaponName = EWeaponName::Sniper;
	FireMode = EFireMode::SemiAuto;
	MagazineSize = 14;
}
