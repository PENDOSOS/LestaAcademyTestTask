#pragma once

#include <memory>

struct DamageInfo;

enum struct CharacterTypesEnum
{
	PLAYER = 0,
	MONSTER,
	TOTAL_CHARACTER_TYPES
};

enum struct CharactersEnum
{
	PLAYER = 0,
	GOBLIN,
	SKELETON,
	SLIME,
	GHOST,
	GOLEM,
	DRAGON,
	TOTAL_CHARACTERS
};

class Character
{
public:
	virtual ~Character() = 0 {}
	virtual void TakeDamage(std::unique_ptr<DamageInfo> damageInfo) = 0;
	virtual std::unique_ptr<DamageInfo> GiveDamage(int enemyAgility) = 0;
	virtual bool IsAttackSuccess(int enemyAgility) = 0;
	virtual bool IsAlive() = 0;
	virtual int GetAgility() = 0;
};