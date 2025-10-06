#include "main.h"

#include <vector>
#include <memory>

using namespace std;

int main()
{
	Controller controller;
	Arena arena(&controller);

	bool continueGame = controller.StartGame();

	while (continueGame)
	{
		arena.Start();

		continueGame = controller.RestartGame();
	}

	//controller.EndGame();

	return 0;
}
