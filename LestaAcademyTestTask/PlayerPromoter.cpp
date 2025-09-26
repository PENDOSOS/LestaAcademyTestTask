#include "PlayerPromoter.h"
#include "Player.h"
#include "Weapon.h"

#include <iostream>

PlayerPromoter::PlayerPromoter(std::shared_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal)
	: arsenal(arsenal)
{
	memset(&classLevels, 0, sizeof(classLevels));
}

std::unique_ptr<Player> PlayerPromoter::promotePlayer(std::unique_ptr<Player> player)
{
	int chosenClass = -1;
	std::cout << "You can promote your character. Choose class to promote\n"
		<< "(1 - Bandit, 2 - Warrior, 3 - Barbarian): ";
	std::cin >> chosenClass;
	std::cout << chosenClass << std::endl;
	chosenClass--;

	switch (chosenClass)
	{
	case (int)PlayerClassesEnum::BANDIT:
		player = PromoteBandit(std::move(player));
		break;
	case (int)PlayerClassesEnum::WARRIOR:
		player = PromoteWarrior(std::move(player));
		break;
	case (int)PlayerClassesEnum::BARBARIAN:
		player = PromoteBarbarian(std::move(player));
		break;
	default:
		break;
	}

	return std::move(player);
}

std::unique_ptr<Player> PlayerPromoter::PromoteBandit(std::unique_ptr<Player> player)
{
	int currentClassLevel = classLevels[(int)PlayerClassesEnum::BANDIT] + 1;
	std::unique_ptr<Player> promoted;
	switch (currentClassLevel)
	{
	case (int)PlayerClassLevelsEnum::LEVEL_1:
		promoted = std::make_unique<ClassBanditLevel1>(std::move(player), arsenal->data()[DAGGER]->GiveWeapon());
		break;
	case (int)PlayerClassLevelsEnum::LEVEL_2:
		promoted = std::make_unique<ClassBanditLevel2>(std::move(player));
		break;
	case (int)PlayerClassLevelsEnum::LEVEL_3:
		promoted = std::make_unique<ClassBanditLevel3>(std::move(player));
		break;
	default:
		break;
	}

	return std::move(promoted);
}

std::unique_ptr<Player> PlayerPromoter::PromoteWarrior(std::unique_ptr<Player> player)
{
	int currentClassLevel = classLevels[(int)PlayerClassesEnum::WARRIOR] + 1;
	std::unique_ptr<Player> promoted;
	switch (currentClassLevel)
	{
	case (int)PlayerClassLevelsEnum::LEVEL_1:
		promoted = std::make_unique<ClassWarriorLevel1>(std::move(player), arsenal->data()[SWORD]->GiveWeapon());
		break;
	case (int)PlayerClassLevelsEnum::LEVEL_2:
		promoted = std::make_unique<ClassWarriorLevel2>(std::move(player));
		break;
	case (int)PlayerClassLevelsEnum::LEVEL_3:
		promoted = std::make_unique<ClassWarriorLevel3>(std::move(player));
		break;
	default:
		break;
	}

	return std::move(promoted);
}

std::unique_ptr<Player> PlayerPromoter::PromoteBarbarian(std::unique_ptr<Player> player)
{
	return std::unique_ptr<Player>();
}
