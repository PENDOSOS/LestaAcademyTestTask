#include "Printer.h"
#include "Character.h"
#include "Player.h"
#include "Monster.h"
#include "Weapon.h"

#include <iostream>

void Printer::PrintStartMessage()
{
	std::cout << "Welcome to autobattler game!" << std::endl;
}

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
	PrintHeader();
	std::cout << "You can promote your character. Choose class to promote\n"
		<< "(1 - Bandit level " << classLevels[(int)PlayerClassesEnum::BANDIT] + 1
		<< ", 2 - Warrior level " << classLevels[(int)PlayerClassesEnum::WARRIOR] + 1
		<< ", 3 - Barbarian level " << classLevels[(int)PlayerClassesEnum::BARBARIAN] + 1 << "): ";
}

void Printer::PrintGameWon()
{
	PrintHeader();
	std::cout << "Congratulations! You win the game!" << std::endl;
}

void Printer::PrintGameOver()
{
	PrintHeader();
	std::cout << "Game over." << std::endl;
}

void Printer::PrintPlayerStats(Player* player)
{
	PrintHeader();
	std::cout << "Player got " << player->GetStrength() << " strength, "
		<< player->GetAgility() << " agility, " << player->GetStamina() << " stamina." << std::endl;
}

void Printer::PrintMonsterName(Monster* monster)
{
	PrintHeader();
	std::cout << "Player's opponent is " << monster->GetName() << "." << std::endl;
}

void Printer::PrintMonsterDrop(Monster* monster, Weapon* weapon)
{
	std::cout << monster->GetName() << " dropped " << weapon->name << "." << "Change your character's weapon to it?" << std::endl;
}

void Printer::PrintTurn(std::unique_ptr<Character>* characters, unsigned attacker, unsigned defender, DamageInfo* damage)
{
	if (damage != nullptr)
	{
		std::cout << characters[attacker]->GetName() << " gave " << damage->weaponDamage + damage->bonusDamage + damage->attackerStrength
			<< " damage." << std::endl;
	}
	else
		std::cout << characters[attacker]->GetName() << "'s attack unsuccess." << std::endl;
}

void Printer::PrintHeader()
{
	std::cout << std::endl;
	std::cout << "=========================================================================" << std::endl;
}
