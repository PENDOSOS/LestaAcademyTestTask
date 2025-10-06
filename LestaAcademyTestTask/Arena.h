#pragma once

//#include "Character.h"
#include "PlayerPromoter.h"

#include <memory>
#include <vector>

class Character;
class Spawner;
class Weapon;
class Printer;

enum GameStatus
{
	PLAYER_WON = 0,
	PLAYER_LOST
};

class Arena
{
public:
	Arena();
	void Battle();
	void AfterBattle();
	unsigned Start();

private:
	void SpawnPlayer();
	void SpawnEnemy();

	std::unique_ptr<Character> characters[(int)CharacterTypesEnum::TOTAL_CHARACTER_TYPES];

	std::unique_ptr<PlayerPromoter> playerPromoter;

	std::vector<std::unique_ptr<Spawner>> spawners;
	std::shared_ptr<Printer> printer;

	unsigned countDefeatedMonsters;
	unsigned numberOfDefeatedMonstersToWin = 3;
};