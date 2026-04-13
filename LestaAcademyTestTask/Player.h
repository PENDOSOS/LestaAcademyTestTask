#pragma once

#include "Character.h"

#include <memory>

struct Weapon;

class Player : public Character
{
public:
	virtual ~Player() override = 0;
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

	std::unique_ptr<DamageInfo> GiveDamage(int enemyAgility) final;
	void TakeDamage(std::unique_ptr<DamageInfo> damageInfo) final;
	int GetAgility() final { return player->GetAgility(); }
	int GetStrength() final { return player->GetStrength(); }
	int GetStamina() final { return player->GetStamina(); }
	bool IsAttackSuccess(int enemyAgility) final;
	bool IsAlive() final { return player->IsAlive(); }
	void ChangeWeapon(std::unique_ptr<Weapon> weapon) final;
	const Weapon* GetWeapon() final { return player->GetWeapon(); }

	void UpdateTurn() final { player->UpdateTurn(); }
	void SetHealth(int health) final { player->SetHealth(healthByLevel + health); }
	void IncreaseStrength(int strength) final { player->IncreaseStrength(strength); }
	void IncreaseAgility(int agility) final { player->IncreaseAgility(agility); }
	void IncreaseStamina(int stamina) final { player->IncreaseStamina(stamina); }
	int GetCurrentTurn() override { return player->GetCurrentTurn(); }

	const std::string& GetName() final { return player->GetName(); }
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
	explicit ClassBanditLevel1(std::unique_ptr<Player> player);
	~ClassBanditLevel1() final {}
private:
	void AcceptAbility(DamageInfo* damageInfo, int enemyAgility) final;
};

class ClassBanditLevel2 : public PlayerClassLevel
{
public:
	explicit ClassBanditLevel2(std::unique_ptr<Player> player);
	~ClassBanditLevel2() final {}
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) final;

	bool abilityAccepted;
};

class ClassBanditLevel3 : public PlayerClassLevel
{
public:
	explicit ClassBanditLevel3(std::unique_ptr<Player> player);
	~ClassBanditLevel3() final {}
private:
	void AcceptAbility(DamageInfo* damageInfo, int enemyAgility = -1) final;
};


class ClassWarriorLevel1 : public PlayerClassLevel
{
public:
	explicit ClassWarriorLevel1(std::unique_ptr<Player> player);
	~ClassWarriorLevel1() final {}
private:
	void AcceptAbility(DamageInfo* damageInfo, int enemyAgility = -1) final;
};

class ClassWarriorLevel2 : public PlayerClassLevel
{
public:
	explicit ClassWarriorLevel2(std::unique_ptr<Player> player);
	~ClassWarriorLevel2() final {}
private:
	void AcceptAbility(DamageInfo* damageInfo, int enemyAgility = -1) final;
};

class ClassWarriorLevel3 : public PlayerClassLevel
{
public:
	explicit ClassWarriorLevel3(std::unique_ptr<Player> player);
	~ClassWarriorLevel3() final {}
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) final;

	bool abilityAccepted;
};

class ClassBarbarianLevel1 : public PlayerClassLevel
{
public:
	explicit ClassBarbarianLevel1(std::unique_ptr<Player> player);
	~ClassBarbarianLevel1() final {}
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) final;
};

class ClassBarbarianLevel2 : public PlayerClassLevel
{
public:
	explicit ClassBarbarianLevel2(std::unique_ptr<Player> player);
	~ClassBarbarianLevel2() final {}
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) final;
};

class ClassBarbarianLevel3 : public PlayerClassLevel
{
public:
	explicit ClassBarbarianLevel3(std::unique_ptr<Player> player);
	~ClassBarbarianLevel3() final {}
private:
	void AcceptAbility(DamageInfo* damageInfo = nullptr, int enemyAgility = -1) final;

	bool abilityAccepted;
};