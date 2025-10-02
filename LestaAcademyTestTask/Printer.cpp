#include "Printer.h"
#include "Character.h"
#include "Player.h"
#include "Monster.h"
#include "Weapon.h"

#include <iostream>

void Printer::PrintBattleResult(std::unique_ptr<Character>* characters)
{
	if (characters[(int)CharacterTypesEnum::PLAYER]->IsAlive())
	{
		std::cout << "Player won." << std::endl;
	}
	else
	{
		std::cout << "Player lost." << std::endl;
	}
}

void Printer::PrintPlayerPromoteInfo(unsigned* classLevels)
{
	std::cout << "You can promote your character. Choose class to promote\n"
		<< "(1 - Bandit level " << classLevels[(int)PlayerClassesEnum::BANDIT] + 1
		<< ", 2 - Warrior level " << classLevels[(int)PlayerClassesEnum::WARRIOR] + 1
		<< ", 3 - Barbarian level " << classLevels[(int)PlayerClassesEnum::BARBARIAN] + 1 << "): ";
}

void Printer::PrintGameWon()
{
	std::cout << "Congratulations! You win the game!" << std::endl;
}

void Printer::PrintGameOver()
{
	std::cout << "Game over." << std::endl;
}

void Printer::PrintPlayerStats(Player* player)
{
	std::cout << "Player got " << player->GetStrength() << " strength, "
		<< player->GetAgility() << " agility, " << player->GetStamina() << " stamina." << std::endl;
}

void Printer::PrintMonsterName(Monster* monster)
{
	std::cout << "Player's opponent is " << monster->GetName() << "." << std::endl;
}

void Printer::PrintTurn(std::unique_ptr<Character>* characters, unsigned attacker, unsigned defender, DamageInfo* damage)
{
	if (damage != nullptr)
	{
		std::cout << characters[attacker] << "gave " << damage->weaponDamage + damage->bonusDamage + damage->attackerStrength
			<< " damage." << std::endl;
	}
	else
		std::cout << "Attack unsuccess." << std::endl;
}
