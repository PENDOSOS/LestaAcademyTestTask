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
	virtual ~Monster() override;
	virtual std::unique_ptr<Weapon> DropWeapon();
	virtual void AcceptAbility(DamageInfo* damageInfo) = 0;
	virtual int GetAgility() override final { return agility; }
	virtual std::unique_ptr<DamageInfo> GiveDamage(int enemyAgility) override final;
	virtual void TakeDamage(std::unique_ptr<DamageInfo> damageInfo) override final;
	virtual bool IsAttackSuccess(int enemyAgility) override final;
	bool IsAlive() override final { return health > 0; }

	const std::string& GetName() { return name; }
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
	virtual ~Goblin() override {}
	virtual void AcceptAbility(DamageInfo* damageInfo) override final {}
};

class Skeleton : public Monster
{
public:
	Skeleton(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	virtual ~Skeleton() override final {}
	virtual void AcceptAbility(DamageInfo* damageInfo) override final;
};

class Slime : public Monster
{
public:
	Slime(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	virtual ~Slime() override final {};
	virtual void AcceptAbility(DamageInfo* damageInfo) override final;
};

class Ghost : public Monster
{
public:
	Ghost(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	virtual ~Ghost() override final {};
	virtual void AcceptAbility(DamageInfo* damageInfo) override final;
};

class Golem : public Monster
{
public:
	Golem(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	virtual ~Golem() override final {};
	virtual void AcceptAbility(DamageInfo* damageInfo) override final;
};

class Dragon : public Monster
{
public:
	Dragon(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	~Dragon() override final {}
	virtual void AcceptAbility(DamageInfo* damageInfo) override final;
protected:
	unsigned currentTurn;
};