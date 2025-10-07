#include "PlayerPromoter.h"
#include "Player.h"
#include "Weapon.h"
#include "Printer.h"
#include "Controller.h"

#include <iostream>

PlayerPromoter::PlayerPromoter(std::shared_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal, std::shared_ptr<Printer> printer, Controller* controller)
	: arsenal(arsenal), printer(printer), controller(controller)
{
	ReinitLevels();
}

std::unique_ptr<Player> PlayerPromoter::PromotePlayer(std::unique_ptr<Player> player)
{
	printer->PrintPlayerPromoteInfo(classLevels);

	int chosenClass = controller->ControlPromotePlayer();

	switch (chosenClass)
	{
	case (int)PlayerClassesEnum::BANDIT:
		player = PromoteBandit(std::move(player));
		classLevels[(int)PlayerClassesEnum::BANDIT]++;
		break;
	case (int)PlayerClassesEnum::WARRIOR:
		player = PromoteWarrior(std::move(player));
		classLevels[(int)PlayerClassesEnum::WARRIOR]++;
		break;
	case (int)PlayerClassesEnum::BARBARIAN:
		player = PromoteBarbarian(std::move(player));
		classLevels[(int)PlayerClassesEnum::BARBARIAN]++;
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
	{
		promoted = std::make_unique<ClassBanditLevel1>(std::move(player));
		
		std::unique_ptr<Weapon> startWeapon = arsenal->data()[DAGGER]->GiveWeapon();
		bool changeWeapon = true;
		if (promoted->GetWeapon() != nullptr)
		{
			printer->PrintChangeWeapon(startWeapon.get());
			changeWeapon = controller->ControlChangeWeapon();
		}
		if (changeWeapon)
			promoted->ChangeWeapon(std::move(startWeapon));

		break;
	}
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
	{
		promoted = std::make_unique<ClassWarriorLevel1>(std::move(player));
		
		std::unique_ptr<Weapon> startWeapon = arsenal->data()[SWORD]->GiveWeapon();
		bool changeWeapon = true;
		if (promoted->GetWeapon() != nullptr)
		{
			printer->PrintChangeWeapon(startWeapon.get());
			changeWeapon = controller->ControlChangeWeapon();
		}
		if (changeWeapon)
			promoted->ChangeWeapon(std::move(startWeapon));

		break;
	}
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
	int currentClassLevel = classLevels[(int)PlayerClassesEnum::BARBARIAN] + 1;
	std::unique_ptr<Player> promoted;
	switch (currentClassLevel)
	{
	case (int)PlayerClassLevelsEnum::LEVEL_1:
	{
		promoted = std::make_unique<ClassBarbarianLevel1>(std::move(player));

		std::unique_ptr<Weapon> startWeapon = arsenal->data()[CUDGEL]->GiveWeapon();
		bool changeWeapon = true;
		if (promoted->GetWeapon() != nullptr)
		{
			printer->PrintChangeWeapon(startWeapon.get());
			changeWeapon = controller->ControlChangeWeapon();
		}
		if (changeWeapon)
			promoted->ChangeWeapon(std::move(startWeapon));
		
		break;
	}
	case (int)PlayerClassLevelsEnum::LEVEL_2:
		promoted = std::make_unique<ClassBarbarianLevel2>(std::move(player));
		break;
	case (int)PlayerClassLevelsEnum::LEVEL_3:
		promoted = std::make_unique<ClassBarbarianLevel3>(std::move(player));
		break;
	default:
		break;
	}

	return std::move(promoted);
}

void PlayerPromoter::ReinitLevels()
{
	memset(&classLevels, 0, sizeof(classLevels));
}
