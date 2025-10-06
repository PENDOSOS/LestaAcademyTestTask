#pragma once

#include "Player.h"

#include <memory>
#include <vector>

class Player;
class WeaponProducer;
struct Wepaon;
class Printer;

class PlayerPromoter
{
public:
	PlayerPromoter(std::shared_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal, std::shared_ptr<Printer> printer);
	std::unique_ptr<Player> PromotePlayer(std::unique_ptr<Player> player);

	void ReinitLevels();
private:
	std::unique_ptr<Player> PromoteBandit(std::unique_ptr<Player> player);
	std::unique_ptr<Player> PromoteWarrior(std::unique_ptr<Player> player);
	std::unique_ptr<Player> PromoteBarbarian(std::unique_ptr<Player> player);

	std::shared_ptr<std::vector<std::shared_ptr<WeaponProducer>>> arsenal;
	std::shared_ptr<Printer> printer;

	unsigned classLevels[(int)PlayerClassesEnum::TOTAL_CLASSES];
};