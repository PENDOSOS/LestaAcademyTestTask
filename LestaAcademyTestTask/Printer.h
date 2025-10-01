#pragma once

#include <memory>

class Character;

class Printer
{
public:
	void PrintTurnResult() {};
	void PrintBattleResult(std::unique_ptr<Character>* characters);

	void PrintPlayerSpawnInfo() {};
	void PrintMonsterSpawnInfo() {};

	void PrintPlayerPromoteInfo(unsigned* classLevels);

	void PrintGameWon();
	void PrintGameOver();
};