#pragma once

#include "Character.h"

#include <memory>

struct Weapon;

class Player : public Character
{
public:
	virtual ~Player() = 0;
	virtual const Weapon* GetWeapon() = 0;
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

class BasePlayer : public Player
{
public:
	BasePlayer(int strength, int agility, int stamina);
	~BasePlayer() override final;

	void TakeDamage(std::unique_ptr<DamageInfo> damageInfo) override final;
	std::unique_ptr<DamageInfo> GiveDamage(int enemyAgility) override final;
	bool IsAttackSuccess(int enemyAgility) override final;
	bool IsAlive() override final { return currentHealth > 0; }
	int GetAgility() override final { return agility; }
	int GetStrength() override final { return strength; }
	int GetStamina() override final { return stamina; }

	const Weapon* GetWeapon() override final { return weapon.get(); }
	void ChangeWeapon(std::unique_ptr<Weapon> weapon) override final;
	void UpdateTurn() override final { currentTurn = 0; }
	void SetHealth(int health) override final { currentHealth = health + stamina; }
	void IncreaseStrength(int strength) override final { this->strength += strength; }
	void IncreaseAgility(int agility) override final { this->agility += agility; }
	void IncreaseStamina(int stamina) override final { this->stamina += stamina; this->currentHealth += stamina; }
	int GetCurrentTurn() override final { return this->currentTurn; }

	const std::string& GetName() override final { return name; }
private:
	int currentHealth;
	int strength;
	int agility;
	int stamina;

	unsigned currentTurn;
	std::unique_ptr<Weapon> weapon;

	std::string name;
};

enum struct PlayerClassesEnum
{
	BANDIT = 0,
	WARRIOR,
	BARBARIAN,

	TOTAL_CLASSES
};

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
	const Weapon* GetWeapon() override final { return player->GetWeapon(); }

	void UpdateTurn() override final { player->UpdateTurn(); }
	void SetHealth(int health) override final { player->SetHealth(healthByLevel + health); }
	void IncreaseStrength(int strength) override final { player->IncreaseStrength(strength); }
	void IncreaseAgility(int agility) override final { player->IncreaseAgility(agility); }
	void IncreaseStamina(int stamina) override final { player->IncreaseStamina(stamina); }
	int GetCurrentTurn() { return player->GetCurrentTurn(); }

	const std::string& GetName() override final { return player->GetName(); }
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
	ClassBanditLevel1(std::unique_ptr<Player> player);
	~ClassBanditLevel1() override final {}
private:
	void AcceptAbility(DamageInfo* damageInfo, int enemyAgility) override final;
};

class ClassBanditLevel2 : public PlayerClassLevel
{
public:
	ClassBanditLevel2(std::unique_ptr<Player> player);
	~ClassBanditLevel2() override final {}
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) override final;

	bool abilityAccepted;
};

class ClassBanditLevel3 : public PlayerClassLevel
{
public:
	ClassBanditLevel3(std::unique_ptr<Player> player);
	~ClassBanditLevel3() override final {}
private:
	void AcceptAbility(DamageInfo* damageInfo, int enemyAgility = -1) override final;
};


class ClassWarriorLevel1 : public PlayerClassLevel
{
public:
	ClassWarriorLevel1(std::unique_ptr<Player> player);
	~ClassWarriorLevel1() override final {}
private:
	void AcceptAbility(DamageInfo* damageInfo, int enemyAgility = -1) override final;
};

class ClassWarriorLevel2 : public PlayerClassLevel
{
public:
	ClassWarriorLevel2(std::unique_ptr<Player> player);
	~ClassWarriorLevel2() override final {}
private:
	void AcceptAbility(DamageInfo* damageInfo, int enemyAgility = -1) override final;
};

class ClassWarriorLevel3 : public PlayerClassLevel
{
public:
	ClassWarriorLevel3(std::unique_ptr<Player> player);
	~ClassWarriorLevel3() override final {}
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) override final;

	bool abilityAccepted;
};

class ClassBarbarianLevel1 : public PlayerClassLevel
{
public:
	ClassBarbarianLevel1(std::unique_ptr<Player> player);
	~ClassBarbarianLevel1() override final {}
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) override final;
};

class ClassBarbarianLevel2 : public PlayerClassLevel
{
public:
	ClassBarbarianLevel2(std::unique_ptr<Player> player);
	~ClassBarbarianLevel2() override final {}
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) override final;
};

class ClassBarbarianLevel3 : public PlayerClassLevel
{
public:
	ClassBarbarianLevel3(std::unique_ptr<Player> player);
	~ClassBarbarianLevel3() override final {}
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) override final;

	bool abilityAccepted;
};