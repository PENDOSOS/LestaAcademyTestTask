#include "Player.h"
#include "Weapon.h"

#include <random>
#include <iostream>

BasePlayer::BasePlayer(int strength, int agility, int stamina)
	: currentHealth(0)
	, strength(strength)
	, agility(agility)
	, stamina(stamina)
	, currentTurn(0)
	, weapon(nullptr)
	, name("Player")
{}

BasePlayer::~BasePlayer()
{}

void BasePlayer::TakeDamage(std::unique_ptr<DamageInfo> damageInfo)
{
	if (damageInfo == nullptr)
		return;
	currentHealth -= (damageInfo->weaponDamage + damageInfo->bonusDamage + damageInfo->attackerStrength);
}

std::unique_ptr<DamageInfo> BasePlayer::GiveDamage(int enemyAgility)
{
	currentTurn++;
	if (IsAttackSuccess(enemyAgility))
	{
		std::unique_ptr<DamageInfo> damageInfo = std::make_unique<DamageInfo>(weapon->damageType, weapon->damage, 0, strength);
		return std::move(damageInfo);
	}
	return nullptr;
}

void BasePlayer::ChangeWeapon(std::unique_ptr<Weapon> weapon)
{
	bool changeWeapon = true;
	if (this->weapon != nullptr)
	{
		std::cout << "Change cuurent weapon to " << weapon->name << "? (1 - Yes, 0 - No): " << std::endl;
		std::cin >> changeWeapon;
	}
	if (changeWeapon)
		std::swap(this->weapon, weapon);
}

bool BasePlayer::IsAttackSuccess(int enemyAgility)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, agility + enemyAgility);

	return dist(rng) > enemyAgility;
}

PlayerClassLevel::PlayerClassLevel(std::unique_ptr<Player> player, int healthByLevel)
	: player(std::move(player))
	, healthByLevel(healthByLevel)
{
	this->player->SetHealth(healthByLevel);
}

PlayerClassLevel::~PlayerClassLevel()
{}

std::unique_ptr<DamageInfo> PlayerClassLevel::GiveDamage(int enemyAgility)
{
	std::unique_ptr<DamageInfo> damageInfo = player->GiveDamage(enemyAgility);
	AcceptAbility(damageInfo.get(), enemyAgility);
	return damageInfo;
}

void PlayerClassLevel::TakeDamage(std::unique_ptr<DamageInfo> damageInfo)
{
	if (damageInfo == nullptr)
		return;

	AcceptAbility(damageInfo.get());
	player->TakeDamage(std::move(damageInfo));
}

bool PlayerClassLevel::IsAttackSuccess(int enemyAgility)
{
	return player->IsAttackSuccess(enemyAgility);
}

void PlayerClassLevel::ChangeWeapon(std::unique_ptr<Weapon> weapon)
{
	if (weapon != nullptr)
		player->ChangeWeapon(std::move(weapon));
}

#define CLASS_BANDIT_HEALTH_BY_LEVEL 4

ClassBanditLevel1::ClassBanditLevel1(std::unique_ptr<Player> player, std::unique_ptr<Weapon> startWeapon)
	: PlayerClassLevel(std::move(player), CLASS_BANDIT_HEALTH_BY_LEVEL)
{
	this->player->ChangeWeapon(std::move(startWeapon));
}

void ClassBanditLevel1::PrintLevelBonusInfo()
{
	std::cout << "Bandit 1 level. Ability: silent attack - gives 1 additional damage if player agility is more than enemy agility." << std::endl;
}

void ClassBanditLevel1::AcceptAbility(DamageInfo* damageInfo, int enemyAgility)
{
	// accept ability if attack success or player gives damage
	if (damageInfo == nullptr || damageInfo->damageType == MONSTER_DAMAGE)
		return;

	if (enemyAgility < GetAgility())
		damageInfo->bonusDamage += 1;
}

ClassBanditLevel2::ClassBanditLevel2(std::unique_ptr<Player> player)
	: PlayerClassLevel(std::move(player), CLASS_BANDIT_HEALTH_BY_LEVEL)
	, abilityAccepted(false)
{
	AcceptAbility();
}

void ClassBanditLevel2::PrintLevelBonusInfo()
{
	std::cout << "Bandit 2 level. Ability: gives 1 additional agility." << std::endl;
}

void ClassBanditLevel2::AcceptAbility(DamageInfo* damageInfo, int enemyAgility)
{
	if (!abilityAccepted)
	{
		IncreaseAgility(1);
		abilityAccepted = true;
	}
}

ClassBanditLevel3::ClassBanditLevel3(std::unique_ptr<Player> player)
	: PlayerClassLevel(std::move(player), CLASS_BANDIT_HEALTH_BY_LEVEL)
{}

void ClassBanditLevel3::PrintLevelBonusInfo()
{
	std::cout << "Bandit 3 level. Ability: poison - gives 1 additional damage on second turn, 2 additional damage on third turn etc." << std::endl;
}

void ClassBanditLevel3::AcceptAbility(DamageInfo* damageInfo, int enemyAgility)
{
	if (damageInfo == nullptr || damageInfo->damageType == MONSTER_DAMAGE)
		return;

	int currentTurn = GetCurrentTurn();
	if (currentTurn > 1)
	{
		damageInfo->bonusDamage += currentTurn - 1;
	}
}

#define CLASS_WARRIOR_HEALTH_BY_LEVEL 5

ClassWarriorLevel1::ClassWarriorLevel1(std::unique_ptr<Player> player, std::unique_ptr<Weapon> startWeapon)
	: PlayerClassLevel(std::move(player), CLASS_WARRIOR_HEALTH_BY_LEVEL)
{
	this->player->ChangeWeapon(std::move(startWeapon));
}

void ClassWarriorLevel1::PrintLevelBonusInfo()
{
	std::cout << "Warrior 1 level. Ability: impulse to action - player gives double damage in first turn." << std::endl;
}

void ClassWarriorLevel1::AcceptAbility(DamageInfo* damageInfo, int enemyAgility)
{
	if (damageInfo == nullptr || damageInfo->damageType == MONSTER_DAMAGE)
		return;

	if (player->GetCurrentTurn() == 1)
	{
		damageInfo->bonusDamage = damageInfo->weaponDamage;
	}
}

ClassWarriorLevel2::ClassWarriorLevel2(std::unique_ptr<Player> player)
	: PlayerClassLevel(std::move(player), CLASS_WARRIOR_HEALTH_BY_LEVEL)
{}

void ClassWarriorLevel2::PrintLevelBonusInfo()
{
	std::cout << "Warrior 2 level. Ability: shield - player takes 3 damage less if his strength more than attacker strength." << std::endl;
}

void ClassWarriorLevel2::AcceptAbility(DamageInfo* damageInfo, int enemyAgility)
{
	// ability accepts only if player takes damage
	if (damageInfo == nullptr || damageInfo->damageType != MONSTER_DAMAGE)
		return;

	if (player->GetStrength() > damageInfo->attackerStrength)
	{
		damageInfo->weaponDamage -= 3;
	}
}

ClassWarriorLevel3::ClassWarriorLevel3(std::unique_ptr<Player> player)
	: PlayerClassLevel(std::move(player), CLASS_WARRIOR_HEALTH_BY_LEVEL)
	, abilityAccepted(false)
{}

void ClassWarriorLevel3::PrintLevelBonusInfo()
{
	std::cout << "Warrior 3 level. Ability: gives 1 additional strength." << std::endl;
}

void ClassWarriorLevel3::AcceptAbility(DamageInfo* damageInfo, int enemyAgility)
{
	if (!abilityAccepted)
	{
		IncreaseStrength(1);
		abilityAccepted = true;
	}
}

#define CLASS_WARRIOR_HEALTH_BY_LEVEL 6

ClassBarbarianLevel1::ClassBarbarianLevel1(std::unique_ptr<Player> player, std::unique_ptr<Weapon> startWeapon)
	: PlayerClassLevel(std::move(player), CLASS_WARRIOR_HEALTH_BY_LEVEL)
{
	ChangeWeapon(std::move(startWeapon));
}

void ClassBarbarianLevel1::PrintLevelBonusInfo()
{
	std::cout << "Barbarian 1 level. Ability: player gives 2 additional damage in first three turns. Every next turn player gives 1 damage less." << std::endl;
}

void ClassBarbarianLevel1::AcceptAbility(DamageInfo* damageInfo, int enemyAgility)
{
	if (damageInfo == nullptr || damageInfo->damageType == MONSTER_DAMAGE)
		return;

	int currentTurn = GetCurrentTurn();
	if (currentTurn >= 1 && currentTurn <= 3)
	{
		damageInfo->bonusDamage += 2;
	}
	else
	{
		damageInfo->bonusDamage -= 1;
	}
}

ClassBarbarianLevel2::ClassBarbarianLevel2(std::unique_ptr<Player> player)
	: PlayerClassLevel(std::move(player), CLASS_WARRIOR_HEALTH_BY_LEVEL)
{}

void ClassBarbarianLevel2::PrintLevelBonusInfo()
{
	std::cout << "Barbarian 2 level. Ability: taken damage is reduces by the amount of stamina." << std::endl;
}

void ClassBarbarianLevel2::AcceptAbility(DamageInfo* damageInfo, int enemyAgility)
{
	if (damageInfo == nullptr || damageInfo->damageType != MONSTER_DAMAGE)
		return;

	damageInfo->weaponDamage -= player->GetStamina();
}

ClassBarbarianLevel3::ClassBarbarianLevel3(std::unique_ptr<Player> player)
	: PlayerClassLevel(std::move(player), CLASS_WARRIOR_HEALTH_BY_LEVEL)
	, abilityAccepted(false)
{}

void ClassBarbarianLevel3::PrintLevelBonusInfo()
{
	std::cout << "Barbarian 3 level. Ability: gives 1 additional stamina." << std::endl;
}

void ClassBarbarianLevel3::AcceptAbility(DamageInfo* damageInfo, int enemyAgility)
{
	if (!abilityAccepted)
	{
		IncreaseStamina(1);
		abilityAccepted = true;
	}
}
