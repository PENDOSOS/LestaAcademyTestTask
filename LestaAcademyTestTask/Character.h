#pragma once

struct DamageInfo;

class Character
{
public:
	virtual ~Character() = 0 {};
	virtual void TakeDamage(DamageInfo* damageInfo) = 0;
	virtual DamageInfo* GiveDamage(int enemyAgility) = 0;
	virtual bool IsAttackSuccess(int enemyAgility) = 0;
	virtual bool IsAlive() = 0;
	virtual int GetAgility() = 0;
};