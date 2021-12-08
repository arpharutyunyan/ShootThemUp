// Shoot Them Up Game, All Rights Reserved


#include "Weapon/STUBaseWeapon.h"
#include <Components/SkeletalMeshComponent.h>

DEFINE_LOG_CATEGORY_STATIC(LogWeapon, All, All)

ASTUBaseWeapon::ASTUBaseWeapon()
{
 	
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

}


void ASTUBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTUBaseWeapon::Fire()
{
	UE_LOG(LogWeapon, Display, TEXT("Fire"));
}
