#include "Arena.h"
#include "Character.h"
#include "Spawner.h"
#include "Weapon.h"

#include <random>

Arena::Arena()
{
	spawners.push_back(std::make_unique<PlayerSpawner>());
	spawners.push_back(std::make_unique<GoblinSpawner>());
	spawners.push_back(std::make_unique<SkeletonSpawner>());
	spawners.push_back(std::make_unique<SlimeSpawner>());
	spawners.push_back(std::make_unique<GhostSpawner>());
	spawners.push_back(std::make_unique<GolemSpawner>());
	spawners.push_back(std::make_unique<DragonSpawner>());
}

void Arena::Initialize()
{
	
}

void Arena::Battle()
{
	bool isEnemiesAlive = true;
	unsigned attacker = 0;
	unsigned defender = 1;
	while (isEnemiesAlive)
	{
		characters[defender]->TakeDamage(characters[attacker]->GiveDamage(characters[defender]->GetAgility()));
		isEnemiesAlive = characters[attacker]->IsAlive() && characters[defender]->IsAlive();
		attacker = (attacker + 1) % 2;
		defender = (defender + 1) % 2;
	}
}

void Arena::SpawnPlayer()
{
	characters[(int)CharacterTypesEnum::PLAYER] = spawners[(int)CharactersEnum::PLAYER]->Spawn();
}

void Arena::SpawnEnemy()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist((int)CharactersEnum::GOBLIN, (int)CharactersEnum::TOTAL_CHARACTERS - 1);

	int chosenEnemy = dist(rng);

	characters[(int)CharacterTypesEnum::MONSTER] = spawners[chosenEnemy]->Spawn();
}

