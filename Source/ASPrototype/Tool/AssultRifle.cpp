// Fill out your copyright notice in the Description page of Project Settings.


#include "Tool/AssultRifle.h"

AAssultRifle::AAssultRifle()
{
	DamageMultiplier = 1.5;
	WeaponType = EWeaponType::Shoot;
	WeaponName = EWeaponName::AssaultRifle;
	FireMode = EFireMode::FullAuto;
	MagazineSize = 90;
}
