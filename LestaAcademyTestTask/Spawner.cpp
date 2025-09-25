#include "Spawner.h"
#include "Character.h"
#include "Player.h"
#include "Weapon.h"
#include "Monster.h"

#include <random>

Spawner::Spawner()
{
	// вынести отсюда и передавать по weak_ptr
	arsenal.resize(WeaponEnum::TOTAL_WEAPONS);
	arsenal[WeaponEnum::SWORD] = std::make_unique<SwordProducer>();
	arsenal[WeaponEnum::CUDGEL] = std::make_unique<CudgelProducer>();
	arsenal[WeaponEnum::DAGGER] = std::make_unique<DaggerProducer>();
	arsenal[WeaponEnum::AXE] = std::make_unique<AxeProducer>();
	arsenal[WeaponEnum::LANCE] = std::make_unique<LanceProducer>();
	arsenal[WeaponEnum::LEGENDARY_SWORD] = std::make_unique<LegendarySwordProducer>();
}

std::unique_ptr<Character> PlayerSpawner::Spawn()
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(1, 3);

	int strength = dist(rng);
	int agility = dist(rng);
	int stamina = dist(rng);

	return std::make_unique<BasePlayer>(strength, agility, stamina);
}

std::unique_ptr<Character> GoblinSpawner::Spawn()
{
	return std::make_unique<Goblin>(goblinHealth, goblinDamage, goblinStrength, goblinAgility, goblinStamina, arsenal[DAGGER]->GiveWeapon());
}

std::unique_ptr<Character> SkeletonSpawner::Spawn()
{
	return std::make_unique<Skeleton>(skeletonHealth, skeletonDamage, skeletonStrength, skeletonAgility, skeletonStamina, arsenal[CUDGEL]->GiveWeapon());
}

std::unique_ptr<Character> GhostSpawner::Spawn()
{
	return std::make_unique<Ghost>(ghostHealth, ghostDamage, ghostStrength, ghostAgility, ghostStamina, arsenal[SWORD]->GiveWeapon());
}

std::unique_ptr<Character> SlimeSpawner::Spawn()
{
	return std::make_unique<Slime>(slimeHealth, slimeDamage, slimeStrength, slimeAgility, slimeStamina, arsenal[LANCE]->GiveWeapon());
}

std::unique_ptr<Character> GolemSpawner::Spawn()
{
	return std::make_unique<Golem>(golemHealth, golemDamage, golemStrength, golemAgility, golemStamina, arsenal[AXE]->GiveWeapon());
}

std::unique_ptr<Character> DragonSpawner::Spawn()
{
	return std::make_unique<Dragon>(dragonHealth, dragonDamage, dragonStrength, dragonAgility, dragonStamina, arsenal[LEGENDARY_SWORD]->GiveWeapon());
}
