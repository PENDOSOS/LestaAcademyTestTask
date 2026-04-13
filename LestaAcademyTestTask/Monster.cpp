#include "Monster.h"
#include "Weapon.h"

#include <random>

Monster::Monster(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon, std::string name)
	: strength(strength)
	, agility(agility)
	, stamina(stamina)
	, drop(std::move(weapon))
	, damage(damage)
	, health(health + stamina)
	, name(name)
{
}

Monster::~Monster()
{}

std::unique_ptr<Weapon> Monster::DropWeapon()
{
	return std::move(drop);
}

std::unique_ptr<DamageInfo> Monster::GiveDamage(int enemyAgility)
{
	if (IsAttackSuccess(enemyAgility))
	{
		std::unique_ptr<DamageInfo> damageInfo = std::make_unique<DamageInfo>(MONSTER_DAMAGE, damage, 0, strength);
		AcceptAbility(damageInfo.get());
		return damageInfo;
	}
	return nullptr;
}

void Monster::TakeDamage(std::unique_ptr<DamageInfo> damageInfo)
{
	if (damageInfo == nullptr)
		return;

	AcceptAbility(damageInfo.get());
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
	: Monster(health, damage, strength, agility, stamina, std::move(weapon), "Goblin")
{}

Skeleton::Skeleton(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon)
	: Monster(health, damage, strength, agility, stamina, std::move(weapon), "Skeleton")
{}

void Skeleton::AcceptAbility(DamageInfo* damageInfo)
{
	if (damageInfo == nullptr)
		return;

	if (damageInfo->damageType == DamageType::CRUSHING)
		damageInfo->weaponDamage *= 2;
}

Slime::Slime(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon)
	: Monster(health, damage, strength, agility, stamina, std::move(weapon), "Slime")
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
	: Monster(health, damage, strength, agility, stamina, std::move(weapon), "Ghost")
{}

void Ghost::AcceptAbility(DamageInfo* damageInfo)
{
	if (damageInfo == nullptr)
		return;

	if (damageInfo->bonusDamage < agility)
		damageInfo->bonusDamage = 1;
}

Golem::Golem(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon)
	: Monster(health, damage, strength, agility, stamina, std::move(weapon), "Golem")
{}

void Golem::AcceptAbility(DamageInfo* damageInfo)
{
	if (damageInfo == nullptr)
		return;

	damageInfo->weaponDamage -= stamina;
}

Dragon::Dragon(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon)
	: Monster(health, damage, strength, agility, stamina, std::move(weapon), "Dragon")
	, currentTurn(0)
{}

void Dragon::AcceptAbility(DamageInfo* damageInfo)
{
	if (damageInfo == nullptr)
		return;

	if (damageInfo->damageType == MONSTER_DAMAGE)
	{
		currentTurn++;
		if (currentTurn % 3 == 0)
			damageInfo->bonusDamage = 3;
	}
}
