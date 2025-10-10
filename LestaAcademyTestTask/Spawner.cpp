#include "Spawner.h"
#include "Character.h"
#include "Player.h"
#include "Weapon.h"
#include "Monster.h"

#include <random>

Spawner::Spawner(std::weak_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal) : arsenal(arsenal)
{}

PlayerSpawner::PlayerSpawner(std::weak_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal)
	: Spawner(arsenal)
{}

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

GoblinSpawner::GoblinSpawner(std::weak_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal)
	: Spawner(arsenal)
{}

std::unique_ptr<Character> GoblinSpawner::Spawn()
{
	return std::make_unique<Goblin>(goblinHealth, goblinDamage, goblinStrength, goblinAgility, goblinStamina, arsenal.lock()->data()[DAGGER]->GiveWeapon());
}

SkeletonSpawner::SkeletonSpawner(std::weak_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal)
	: Spawner(arsenal)
{}

std::unique_ptr<Character> SkeletonSpawner::Spawn()
{
	return std::make_unique<Skeleton>(skeletonHealth, skeletonDamage, skeletonStrength, skeletonAgility, skeletonStamina, arsenal.lock()->data()[CUDGEL]->GiveWeapon());
}

GhostSpawner::GhostSpawner(std::weak_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal)
	: Spawner(arsenal)
{}

std::unique_ptr<Character> GhostSpawner::Spawn()
{
	return std::make_unique<Ghost>(ghostHealth, ghostDamage, ghostStrength, ghostAgility, ghostStamina, arsenal.lock()->data()[SWORD]->GiveWeapon());
}

SlimeSpawner::SlimeSpawner(std::weak_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal)
	: Spawner(arsenal)
{}

std::unique_ptr<Character> SlimeSpawner::Spawn()
{
	return std::make_unique<Slime>(slimeHealth, slimeDamage, slimeStrength, slimeAgility, slimeStamina, arsenal.lock()->data()[LANCE]->GiveWeapon());
}

GolemSpawner::GolemSpawner(std::weak_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal)
	: Spawner(arsenal)
{}

std::unique_ptr<Character> GolemSpawner::Spawn()
{
	return std::make_unique<Golem>(golemHealth, golemDamage, golemStrength, golemAgility, golemStamina, arsenal.lock()->data()[AXE]->GiveWeapon());
}

DragonSpawner::DragonSpawner(std::weak_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal)
	: Spawner(arsenal)
{}

std::unique_ptr<Character> DragonSpawner::Spawn()
{
	return std::make_unique<Dragon>(dragonHealth, dragonDamage, dragonStrength, dragonAgility, dragonStamina, arsenal.lock()->data()[LEGENDARY_SWORD]->GiveWeapon());
}
