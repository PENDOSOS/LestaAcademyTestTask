#pragma once

#include "Character.h"

#include <memory>

struct Weapon;
struct DamageInfo;

class Monster : public Character
{
public:
	Monster(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	virtual ~Monster() override;
	virtual std::unique_ptr<Weapon> DropWeapon();
	virtual void AcceptAbility(DamageInfo* damageInfo) = 0;
	virtual int GetAgility() override final { return agility; }
	virtual DamageInfo* GiveDamage(int enemyAgility) override final;
	virtual void TakeDamage(DamageInfo* damageInfo) override final;
	virtual bool IsAttackSuccess(int enemyAgility) override final;
	bool IsAlive() override final { return health > 0; }
protected:
	int health;
	int damage;
	int strength;
	int agility;
	int stamina;
	std::unique_ptr<Weapon> drop;
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
	Dragon(int health, int damage, int strength, int agility, int stamina, std::unique_ptr<Weapon> weapon);
	virtual ~Dragon() override final {};
	virtual void AcceptAbility(DamageInfo* damageInfo) override final;
private:
	unsigned currentTurn;
};