#pragma once

#include "Character.h"

#include <memory>
#include <vector>

class Character;
class PlayerPromoter;
class Spawner;

class Arena
{
public:
	Arena();
	void Initialize();
	void Battle();
private:
	void SpawnPlayer();
	void SpawnEnemy();

	// возможно здесь утечка памяти
	std::unique_ptr<Character> characters[(int)CharacterTypesEnum::TOTAL_CHARACTER_TYPES];

	//std::unique_ptr<PlayerPromoter> playerPromoter;

	std::vector<std::unique_ptr<Spawner>> spawners;
};