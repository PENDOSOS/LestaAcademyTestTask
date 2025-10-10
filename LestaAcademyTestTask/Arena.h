#pragma once

//#include "Character.h"
#include "PlayerPromoter.h"

#include <memory>
#include <vector>

class Character;
class Spawner;
class Weapon;
class Printer;
class Controller;

class Arena
{
public:
	Arena(Controller* controller);
	void Battle();
	void AfterBattle();
	void Start();

private:
	void SpawnPlayer();
	void SpawnEnemy();

	std::unique_ptr<Character> characters[(int)CharacterTypesEnum::TOTAL_CHARACTER_TYPES];

	std::unique_ptr<PlayerPromoter> playerPromoter;

	std::vector<std::unique_ptr<Spawner>> spawners;
	std::shared_ptr<Printer> printer;

	unsigned countDefeatedMonsters;
	unsigned numberOfDefeatedMonstersToWin = 3;

	Controller* controller;
};