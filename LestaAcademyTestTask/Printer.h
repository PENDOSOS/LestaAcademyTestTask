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
	static void PrintStartMessage();

	static void PrintBattleResult(std::unique_ptr<Character>* characters);

	static void PrintPlayerPromoteInfo(unsigned* classLevels);

	static void PrintGameWon();
	static void PrintGameOver();

	static void PrintPlayerStats(Player* player);
	static void PrintMonsterName(Monster* monster);

	static void PrintMonsterDrop(Monster* monster, Weapon* weapon);
	static void PrintChangeWeapon(Weapon* weapon);
	
	static void PrintTurn(std::unique_ptr<Character>* characters, unsigned attacker, unsigned defender, DamageInfo* damage);
private:
	static void PrintHeader();
};