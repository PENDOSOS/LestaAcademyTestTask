#include "Weapon.h"

Weapon* SwordProducer::GiveWeapon()
{
	return new Weapon{ DamageType::CHOPPING, 3, "Sword" };
}

Weapon* CudgelProducer::GiveWeapon()
{
	return new Weapon{ DamageType::CRUSHING, 3, "Cudgel" };
}

Weapon* DaggerProducer::GiveWeapon()
{
	return new Weapon{ DamageType::STABBING, 2, "Dagger" };
}

Weapon* AxeProducer::GiveWeapon()
{
	return new Weapon{ DamageType::CHOPPING, 4, "Axe" };
}

Weapon* LanceProducer::GiveWeapon()
{
	return new Weapon{ DamageType::STABBING, 3, "Lance" };
}

Weapon* LegendarySwordProducer::GiveWeapon()
{
	return new Weapon{ DamageType::CHOPPING, 3, "Legendary sword" };
}
