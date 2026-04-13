#pragma once

#include <memory>

class Printer;

class Controller
{
public:
	Controller() : printer(nullptr) {}

	void SetPrinter(std::shared_ptr<Printer> printer);

	bool StartGame();
	static bool RestartGame();
	static int ControlPromotePlayer();
	static bool ControlChangeWeapon();
private:
	std::shared_ptr<Printer> printer;
};