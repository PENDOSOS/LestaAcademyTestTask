#pragma once

#include "Character.h"
#include "PlayerPromoter.h"

#include <memory>
#include <vector>

class Character;
class Spawner;
class Weapon;

class Arena
{
public:
	Arena();
	void Initialize();
	void Battle();
	void AfterBattle();
private:
	void SpawnPlayer();
	void SpawnEnemy();

	std::unique_ptr<Character> characters[(int)CharacterTypesEnum::TOTAL_CHARACTER_TYPES];

	std::unique_ptr<PlayerPromoter> playerPromoter;

	std::vector<std::unique_ptr<Spawner>> spawners;
};