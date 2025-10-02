#include "main.h"

#include <vector>
#include <memory>

using namespace std;

int main()
{
	Arena arena;

	bool continueGame = true;

	while (continueGame)
	{
		arena.Start();

		std::cout << "Start new game (1 - yes, 0 - no)? ";
		while (!(std::cin >> continueGame).good())
		{
			std::cout << std::endl;
			std::cout << "Invalid input. Try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	return 0;
}
