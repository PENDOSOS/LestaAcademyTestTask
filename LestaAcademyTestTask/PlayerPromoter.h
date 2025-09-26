#pragma once

#include "Player.h"

#include <memory>
#include <vector>

class Player;
class WeaponProducer;
class Wepaon;

class PlayerPromoter
{
public:
	PlayerPromoter(std::shared_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal);
	std::unique_ptr<Player> promotePlayer(std::unique_ptr<Player> player);
private:
	std::unique_ptr<Player> PromoteBandit(std::unique_ptr<Player> player);
	std::unique_ptr<Player> PromoteWarrior(std::unique_ptr<Player> player);
	std::unique_ptr<Player> PromoteBarbarian(std::unique_ptr<Player> player);

	std::shared_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal;

	unsigned classLevels[(int)PlayerClassesEnum::TOTAL_CLASSES];
};