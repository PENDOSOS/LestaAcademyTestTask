#include "Weapon.h"

std::unique_ptr<Weapon> SwordProducer::GiveWeapon()
{
	return std::make_unique<Weapon>(DamageType::CHOPPING, 3, "Sword");
}

std::unique_ptr<Weapon> CudgelProducer::GiveWeapon()
{
	return std::make_unique<Weapon>(DamageType::CRUSHING, 3, "Cudgel");
}

std::unique_ptr<Weapon> DaggerProducer::GiveWeapon()
{
	return std::make_unique<Weapon>(DamageType::STABBING, 2, "Dagger");
}

std::unique_ptr<Weapon> AxeProducer::GiveWeapon()
{
	return std::make_unique<Weapon>(DamageType::CHOPPING, 4, "Axe");
}

std::unique_ptr<Weapon> LanceProducer::GiveWeapon()
{
	return std::make_unique<Weapon>(DamageType::STABBING, 3, "Lance");
}

std::unique_ptr<Weapon> LegendarySwordProducer::GiveWeapon()
{
	return std::make_unique<Weapon>(DamageType::CHOPPING, 3, "Legendary sword");
}
