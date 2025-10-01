#include "Printer.h"
#include "Character.h"
#include "Player.h"

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
