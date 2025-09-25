#include "Monster.h"
#include "Weapon.h"

#include <random>

Monster::Monster(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon)
	: strength(strength)
	, agility(agility)
	, stamina(stamina)
	, drop(std::move(weapon))
	, damage(damage)
	, health(health)
{
}

Monster::~Monster()
{}

std::unique_ptr<Weapon> Monster::DropWeapon()
{
	return std::move(drop);
}

DamageInfo* Monster::GiveDamage(int enemyAgility)
{
	if (IsAttackSuccess(enemyAgility))
	{
		DamageInfo* damageInfo = new DamageInfo{ MONSTER_DAMAGE, damage, 0, strength };
		AcceptAbility(damageInfo);
		return damageInfo;
	}
	return nullptr;
}

void Monster::TakeDamage(DamageInfo* damageInfo)
{
	if (damageInfo == nullptr)
		return;

	AcceptAbility(damageInfo);
	health -= (damageInfo->weaponDamage + damageInfo->bonusDamage + damageInfo->attackerStrength);
}

bool Monster::IsAttackSuccess(int enemyAgility)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, agility + enemyAgility);

	return dist(rng) > enemyAgility;
}

Goblin::Goblin(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon)
	: Monster(health, damage, strength, agility, stamina, std::move(weapon))
{}

Skeleton::Skeleton(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon)
	: Monster(health, damage, strength, agility, stamina, std::move(weapon))
{}

void Skeleton::AcceptAbility(DamageInfo* damageInfo)
{
	if (damageInfo == nullptr)
		return;

	if (damageInfo->damageType == DamageType::CRUSHING)
		damageInfo->weaponDamage *= 2;
}

Slime::Slime(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon)
	: Monster(health, damage, strength, agility, stamina, std::move(weapon))
{}

void Slime::AcceptAbility(DamageInfo* damageInfo)
{
	if (damageInfo == nullptr)
		return;

	if (damageInfo->damageType == DamageType::CHOPPING)
	{
		damageInfo->weaponDamage = 0;
	}
}

Ghost::Ghost(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon)
	: Monster(health, damage, strength, agility, stamina, std::move(weapon))
{}

void Ghost::AcceptAbility(DamageInfo* damageInfo)
{
	if (damageInfo == nullptr)
		return;

	if (damageInfo->bonusDamage < agility)
		damageInfo->bonusDamage = 1;
}

Golem::Golem(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon)
	: Monster(health, damage, strength, agility, stamina, std::move(weapon))
{}

void Golem::AcceptAbility(DamageInfo* damageInfo)
{
	if (damageInfo == nullptr)
		return;

	damageInfo->weaponDamage -= stamina;
}

Dragon::Dragon(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon)
	: Monster(health, damage, strength, agility, stamina, std::move(weapon))
	, currentTurn(1)
{}

void Dragon::AcceptAbility(DamageInfo* damageInfo)
{
	if (damageInfo == nullptr)
		return;

	currentTurn++;
	if (currentTurn % 3 == 0)
		damageInfo->bonusDamage = 3;
}
