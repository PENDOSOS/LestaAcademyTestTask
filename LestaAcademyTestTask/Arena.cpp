#include "Arena.h"
#include "Character.h"
#include "Spawner.h"
#include "Weapon.h"
#include "Printer.h"
#include "Monster.h"
#include "Controller.h"

#include <random>
#include <iostream>

Arena::Arena(Controller* controller) : countDefeatedMonsters(0), controller(controller)
{
	printer = std::make_shared<Printer>();

	std::shared_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal = std::make_shared<std::vector<std::shared_ptr<WeaponProducer>>>();
	arsenal->emplace_back(std::make_shared<SwordProducer>());
	arsenal->emplace_back(std::make_shared<CudgelProducer>());
	arsenal->emplace_back(std::make_shared<DaggerProducer>());
	arsenal->emplace_back(std::make_shared<AxeProducer>());
	arsenal->emplace_back(std::make_shared<LanceProducer>());
	arsenal->emplace_back(std::make_shared<LegendarySwordProducer>());

	playerPromoter = std::make_unique<PlayerPromoter>(arsenal, printer, controller);

	spawners.push_back(std::make_unique<PlayerSpawner>(arsenal));
	spawners.push_back(std::make_unique<GoblinSpawner>(arsenal));
	spawners.push_back(std::make_unique<SkeletonSpawner>(arsenal));
	spawners.push_back(std::make_unique<SlimeSpawner>(arsenal));
	spawners.push_back(std::make_unique<GhostSpawner>(arsenal));
	spawners.push_back(std::make_unique<GolemSpawner>(arsenal));
	spawners.push_back(std::make_unique<DragonSpawner>(arsenal));

	controller->SetPrinter(printer);
}

void Arena::Battle()
{
	bool isCharactersAlive = true;

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);

	unsigned attacker = dist(rng);	
	unsigned defender = (attacker + 1) % 2;

	SpawnEnemy();

	while (isCharactersAlive)
	{
		std::unique_ptr<DamageInfo> damageInfo = characters[attacker]->GiveDamage(characters[defender]->GetAgility());
		printer->PrintTurn(characters, attacker, defender, damageInfo.get());
		characters[defender]->TakeDamage(std::move(damageInfo));
		isCharactersAlive = characters[attacker]->IsAlive() && characters[defender]->IsAlive();

		attacker = (attacker + 1) % 2;
		defender = (defender + 1) % 2;
	}
}

void Arena::SpawnPlayer()
{
	characters[(int)CharacterTypesEnum::PLAYER] = spawners[(int)CharactersEnum::PLAYER]->Spawn();

	Character* characterRawPtr = characters[(int)CharacterTypesEnum::PLAYER].release();
	std::unique_ptr<Player> player = std::unique_ptr<Player>(static_cast<Player*>(characterRawPtr));
	printer->PrintPlayerStats(player.get());

	characters[(int)CharacterTypesEnum::PLAYER] = playerPromoter->PromotePlayer(std::move(player));
}

void Arena::SpawnEnemy()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist((int)CharactersEnum::GOBLIN, (int)CharactersEnum::TOTAL_CHARACTERS - 1);

	int chosenEnemy = dist(rng);

	characters[(int)CharacterTypesEnum::MONSTER] = spawners[chosenEnemy]->Spawn();

	printer->PrintMonsterName(static_cast<Monster*>(characters[(int)CharacterTypesEnum::MONSTER].get()));
}

void Arena::AfterBattle()
{
	printer->PrintBattleResult(characters);
	if (characters[(int)CharacterTypesEnum::PLAYER]->IsAlive())
	{
		countDefeatedMonsters++;
		if (countDefeatedMonsters < numberOfDefeatedMonstersToWin)
		{
			Monster* monster = static_cast<Monster*>(characters[(int)CharacterTypesEnum::MONSTER].get());
			std::unique_ptr<Weapon> monsterDrop = monster->DropWeapon();
			printer->PrintMonsterDrop(monster, monsterDrop.get());

			Character* characterRawPtr = characters[(int)CharacterTypesEnum::PLAYER].release();
			std::unique_ptr<Player> player = std::unique_ptr<Player>(static_cast<Player*>(characterRawPtr));

			printer->PrintChangeWeapon(monsterDrop.get());
			bool changeWeapon = controller->ControlChangeWeapon();
			if (changeWeapon || player->GetWeapon() == nullptr)
				player->ChangeWeapon(std::move(monsterDrop));

			player->UpdateTurn();
			characters[(int)CharacterTypesEnum::PLAYER] = playerPromoter->PromotePlayer(std::move(player));
		}
	}
}

void Arena::Start()
{
	playerPromoter->ReinitLevels();
	countDefeatedMonsters = 0;

	SpawnPlayer();

	while (characters[(int)CharacterTypesEnum::PLAYER]->IsAlive() && countDefeatedMonsters < numberOfDefeatedMonstersToWin)
	{
		Battle();
		AfterBattle();
	}

	if (countDefeatedMonsters == numberOfDefeatedMonstersToWin)
	{
		printer->PrintGameWon();
	}
	else
	{
		printer->PrintGameOver();
	}
}

