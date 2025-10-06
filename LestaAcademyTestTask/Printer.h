#pragma once

#include <memory>

class Character;
class Player;
class Monster;
class DamageInfo;
struct Weapon;

class Printer
{
public:
	void PrintStartMessage();

	void PrintTurnResult() {};
	void PrintBattleResult(std::unique_ptr<Character>* characters);

	void PrintPlayerSpawnInfo() {};
	void PrintMonsterSpawnInfo() {};

	void PrintPlayerPromoteInfo(unsigned* classLevels);

	void PrintGameWon();
	void PrintGameOver();

	void PrintPlayerStats(Player* player);
	void PrintMonsterName(Monster* monster);

	void PrintMonsterDrop(Monster* monster, Weapon* weapon);
	
	void PrintTurn(std::unique_ptr<Character>* characters, unsigned attacker, unsigned defender, DamageInfo* damage);
private:
	void PrintHeader();
};