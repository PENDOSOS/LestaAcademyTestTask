#pragma once

#include <memory>
#include <vector>

class Character;
class WeaponProducer;

class Spawner
{
public:
	Spawner();

	virtual std::unique_ptr<Character> Spawn() = 0;
protected:
	// не нужно его здесь хранить
	std::vector<std::unique_ptr<WeaponProducer>> arsenal;
};

class PlayerSpawner : public Spawner
{
public:
	std::unique_ptr<Character> Spawn() override final;
};

class GoblinSpawner : public Spawner
{
public:
	std::unique_ptr<Character> Spawn() override final;
private:
	int goblinHealth = 5;
	int goblinDamage = 2;
	int goblinStrength = 1;
	int goblinAgility = 1;
	int goblinStamina = 1;
};

class SkeletonSpawner : public Spawner
{
public:
	std::unique_ptr<Character> Spawn() override final;
private:
	int skeletonHealth = 10;
	int skeletonDamage = 2;
	int skeletonStrength = 2;
	int skeletonAgility = 2;
	int skeletonStamina = 1;
};

class GhostSpawner : public Spawner
{
public:
	std::unique_ptr<Character> Spawn() override final;
private:
	int ghostHealth = 6;
	int ghostDamage = 3;
	int ghostStrength = 1;
	int ghostAgility = 3;
	int ghostStamina = 1;
};

class SlimeSpawner : public Spawner
{
public:
	std::unique_ptr<Character> Spawn() override final;
private:
	int slimeHealth = 8;
	int slimeDamage = 1;
	int slimeStrength = 3;
	int slimeAgility = 1;
	int slimeStamina = 2;
};

class GolemSpawner : public Spawner
{
public:
	std::unique_ptr<Character> Spawn() override final;
private:
	int golemHealth = 10;
	int golemDamage = 1;
	int golemStrength = 3;
	int golemAgility = 1;
	int golemStamina = 3;
};

class DragonSpawner : public Spawner
{
public:
	std::unique_ptr<Character> Spawn() override final;
private:
	int dragonHealth = 20;
	int dragonDamage = 4;
	int dragonStrength = 3;
	int dragonAgility = 3;
	int dragonStamina = 3;
};