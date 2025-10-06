#include "Controller.h"
#include "Printer.h"

#include <iostream>

void Controller::SetPrinter(std::shared_ptr<Printer> printer)
{
	this->printer = printer;
}

bool Controller::StartGame()
{
	if (printer == nullptr)
		return false;
	
	printer->PrintStartMessage();
	return RestartGame();
}

bool Controller::RestartGame()
{
	bool continueGame;

	std::cout << "Start new game (1 - yes, 0 - no)? ";
	while (!(std::cin >> continueGame).good())
	{
		std::cout << std::endl;
		std::cout << "Invalid input. Try again." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return continueGame;
}

int Controller::ControlPromotePlayer()
{
	int chosenClass = -1;
	bool isInputCorrect = false;
	while (!isInputCorrect)
	{
		if ((std::cin >> chosenClass).good())
		{
			if (chosenClass >= 1 && chosenClass <= 3)
			{
				isInputCorrect = true;
			}
			else
			{
				std::cout << "Invalid class number. Please try again.\n";
			}
		}
		else
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a number.\n";
		}
	}

	chosenClass--;
	return chosenClass;
}

