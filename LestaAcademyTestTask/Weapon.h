#pragma once

#include <string>
#include <memory>

typedef enum DamageType
{
	CHOPPING = 0,
	CRUSHING,
	STABBING,
	MONSTER_DAMAGE,
	TOTAL_DAMAGE_TYPES,
};

struct Weapon
{
	DamageType damageType;
	int damage;
	std::string name;
};

enum WeaponEnum
{
	SWORD,
	CUDGEL,
	DAGGER,
	AXE,
	LANCE,
	LEGENDARY_SWORD,
	TOTAL_WEAPONS,
};

struct DamageInfo
{
	DamageType damageType;
	int weaponDamage;
	int bonusDamage;
	int attackerStrength;
};

class WeaponProducer
{
public:
	virtual std::unique_ptr<Weapon> GiveWeapon() = 0;
};

class SwordProducer : public WeaponProducer
{
	std::unique_ptr<Weapon> GiveWeapon() override final;
};

class CudgelProducer : public WeaponProducer
{
	std::unique_ptr<Weapon> GiveWeapon() override final;
};

class DaggerProducer : public WeaponProducer
{
	std::unique_ptr<Weapon> GiveWeapon() override final;
};

class AxeProducer : public WeaponProducer
{
	std::unique_ptr<Weapon> GiveWeapon() override final;
};

class LanceProducer : public WeaponProducer
{
	std::unique_ptr<Weapon> GiveWeapon() override final;
};

class LegendarySwordProducer : public WeaponProducer
{
	std::unique_ptr<Weapon> GiveWeapon() override final;
};