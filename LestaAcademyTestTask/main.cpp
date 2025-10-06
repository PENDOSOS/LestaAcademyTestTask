#include "main.h"

#include <vector>
#include <memory>

using namespace std;

int main()
{
	Arena arena;
	Controller controller;

	controller.StartGame();

	bool continueGame = true;

	while (continueGame)
	{
		arena.Start();

		continueGame = controller.RestartGame();
	}

	//controller.EndGame();

	return 0;
}
