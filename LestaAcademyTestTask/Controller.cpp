#include "Controller.h"
#include "Printer.h"

#include <iostream>

Controller::Controller(std::shared_ptr<Printer> printer) : printer(printer)
{}

void Controller::StartGame()
{
	printer->PrintStartMessage();
	RestartGame();
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

