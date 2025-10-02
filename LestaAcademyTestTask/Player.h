#pragma once

#include "Character.h"

#include <memory>

struct Weapon;

class Player : public Character
{
public:
	virtual ~Player() = 0 {}
	virtual void ChangeWeapon(std::unique_ptr<Weapon> weapon) = 0;
	virtual void UpdateTurn() = 0;
	virtual void SetHealth(int health) = 0;
	virtual void IncreaseStrength(int strength) = 0;
	virtual void IncreaseAgility(int agility) = 0;
	virtual void IncreaseStamina(int stamina) = 0;
	virtual int GetCurrentTurn() = 0;
	virtual int GetStrength() = 0;
	virtual int GetStamina() = 0;
};

// возможно стоит вынести счетчик текущего хода в классы,
// которым дествительно нужно знать о том, какой сейчас ход
class BasePlayer : public Player
{
public:
	BasePlayer(int strength, int agility, int stamina);
	~BasePlayer() override final;

	void TakeDamage(std::unique_ptr<DamageInfo> damageInfo) override final;
	std::unique_ptr<DamageInfo> GiveDamage(int enemyAgility) override final;
	// IsAttackSuccess по архитектуре не должен вызываться извне
	// возможно, чтоит его вынести в protected
	bool IsAttackSuccess(int enemyAgility) override final;
	bool IsAlive() override final { return currentHealth > 0; }
	int GetAgility() override final { return agility; }
	int GetStrength() override final { return strength; }
	int GetStamina() override final { return stamina; }

	void ChangeWeapon(std::unique_ptr<Weapon> weapon) override final;
	void UpdateTurn() override final { currentTurn++; }
	void SetHealth(int health) override final { currentHealth = health; }
	void IncreaseStrength(int strength) override final { this->strength += strength; }
	void IncreaseAgility(int agility) override final { this->agility += agility; }
	void IncreaseStamina(int stamina) override final { this->stamina += stamina; }
	int GetCurrentTurn() override final { return this->currentTurn; }
private:
	int currentHealth;
	int strength;
	int agility;
	int stamina;

	unsigned currentTurn;
	std::unique_ptr<Weapon> weapon;
};

enum struct PlayerClassesEnum
{
	BANDIT = 0,
	WARRIOR,
	BARBARIAN,

	TOTAL_CLASSES
};

// этот класс просто прослойка между Player и декораторами уровней
class PlayerClassLevel : public Player
{
public:
	PlayerClassLevel(std::unique_ptr<Player> player, int healthByLevel);
	virtual ~PlayerClassLevel() override;

	std::unique_ptr<DamageInfo> GiveDamage(int enemyAgility) override final;
	void TakeDamage(std::unique_ptr<DamageInfo> damageInfo) override final;
	int GetAgility() override final { return player->GetAgility(); }
	int GetStrength() override final { return player->GetStrength(); }
	int GetStamina() override final { return player->GetStamina(); }
	bool IsAttackSuccess(int enemyAgility) override final;
	bool IsAlive() override final { return player->IsAlive(); }
	void ChangeWeapon(std::unique_ptr<Weapon> weapon) override final;
	
	virtual void PrintLevelBonusInfo() = 0;

	void UpdateTurn() override final { player->UpdateTurn(); }
	void SetHealth(int health) override final { player->SetHealth(healthByLevel + health); }
	void IncreaseStrength(int strength) override final { player->IncreaseStrength(strength); }
	void IncreaseAgility(int agility) override final { player->IncreaseAgility(agility); }
	void IncreaseStamina(int stamina) override final { player->IncreaseStamina(stamina); }
	int GetCurrentTurn() { return player->GetCurrentTurn(); }
protected:
	virtual void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) = 0;

	std::unique_ptr<Player> player;
	int healthByLevel;
};

enum struct PlayerClassLevelsEnum
{
	LEVEL_1 = 1,
	LEVEL_2,
	LEVEL_3,

	TOTAL_CLASS_LEVELS
};

class ClassBanditLevel1 : public PlayerClassLevel
{
public:
	ClassBanditLevel1(std::unique_ptr<Player> player, std::unique_ptr<Weapon> startWeapon);
	~ClassBanditLevel1() override final {}
	void PrintLevelBonusInfo() override final;
private:
	void AcceptAbility(DamageInfo* damageInfo, int enemyAgility) override final;
};

class ClassBanditLevel2 : public PlayerClassLevel
{
public:
	ClassBanditLevel2(std::unique_ptr<Player> player);
	~ClassBanditLevel2() override final {}
	void PrintLevelBonusInfo() override final;
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) override final;

	bool abilityAccepted;
};

class ClassBanditLevel3 : public PlayerClassLevel
{
public:
	// возможно стоит убрать healthByLevel из контсруктора и сделать константу в каждом классе
	ClassBanditLevel3(std::unique_ptr<Player> player);
	~ClassBanditLevel3() override final {}
	void PrintLevelBonusInfo() override final;
private:
	void AcceptAbility(DamageInfo* damageInfo, int enemyAgility = -1) override final;
};


class ClassWarriorLevel1 : public PlayerClassLevel
{
public:
	ClassWarriorLevel1(std::unique_ptr<Player> player, std::unique_ptr<Weapon> startWeapon);
	~ClassWarriorLevel1() override final {}
	void PrintLevelBonusInfo() override final;
private:
	void AcceptAbility(DamageInfo* damageInfo, int enemyAgility = -1) override final;
};

class ClassWarriorLevel2 : public PlayerClassLevel
{
public:
	ClassWarriorLevel2(std::unique_ptr<Player> player);
	~ClassWarriorLevel2() override final {}
	void PrintLevelBonusInfo() override final;
private:
	void AcceptAbility(DamageInfo* damageInfo, int enemyAgility = -1) override final;
};

class ClassWarriorLevel3 : public PlayerClassLevel
{
public:
	ClassWarriorLevel3(std::unique_ptr<Player> player);
	~ClassWarriorLevel3() override final {}
	void PrintLevelBonusInfo() override final;
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) override final;

	bool abilityAccepted;
};

class ClassBarbarianLevel1 : public PlayerClassLevel
{
public:
	ClassBarbarianLevel1(std::unique_ptr<Player> player, std::unique_ptr<Weapon> startWeapon);
	~ClassBarbarianLevel1() override final {}
	void PrintLevelBonusInfo() override final;
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) override final;
};

class ClassBarbarianLevel2 : public PlayerClassLevel
{
public:
	ClassBarbarianLevel2(std::unique_ptr<Player> player);
	~ClassBarbarianLevel2() override final {}
	void PrintLevelBonusInfo() override final;
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) override final;
};

class ClassBarbarianLevel3 : public PlayerClassLevel
{
public:
	ClassBarbarianLevel3(std::unique_ptr<Player> player);
	~ClassBarbarianLevel3() override final {}
	void PrintLevelBonusInfo() override final;
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) override final;

	bool abilityAccepted;
};