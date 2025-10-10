#include "Weapon.h"
#include "Spawner.h"
#include "Arena.h"
#include "Controller.h"

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

	return 0;
}
