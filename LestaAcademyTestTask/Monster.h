#pragma once

#include "Character.h"

#include <memory>
#include <string>

struct Weapon;
struct DamageInfo;

class Monster : public Character
{
public:
	Monster(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon, std::string name);
	~Monster() override;
	virtual std::unique_ptr<Weapon> DropWeapon();
	virtual void AcceptAbility(DamageInfo* damageInfo) = 0;
	virtual int GetAgility() final { return agility; }
	std::unique_ptr<DamageInfo> GiveDamage(int enemyAgility) final;
	void TakeDamage(std::unique_ptr<DamageInfo> damageInfo) final;
	bool IsAttackSuccess(int enemyAgility) final;
	bool IsAlive() final { return health > 0; }

	const std::string& GetName() final { return name; }
protected:
	int health;
	int damage;
	int strength;
	int agility;
	int stamina;
	std::unique_ptr<Weapon> drop;
	std::string name;
};

class Goblin : public Monster
{
public:
	Goblin(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	~Goblin() final {}
	void AcceptAbility(DamageInfo* damageInfo) final {}
};

class Skeleton : public Monster
{
public:
	Skeleton(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	~Skeleton() final {}
	void AcceptAbility(DamageInfo* damageInfo) final;
};

class Slime : public Monster
{
public:
	Slime(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	~Slime()final {};
	void AcceptAbility(DamageInfo* damageInfo) final;
};

class Ghost : public Monster
{
public:
	Ghost(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	~Ghost() final {};
	void AcceptAbility(DamageInfo* damageInfo) final;
};

class Golem : public Monster
{
public:
	Golem(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	~Golem() final {};
	void AcceptAbility(DamageInfo* damageInfo) final;
};

class Dragon : public Monster
{
public:
	Dragon(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	~Dragon() final {}
	void AcceptAbility(DamageInfo* damageInfo) final;
protected:
	unsigned currentTurn;
};