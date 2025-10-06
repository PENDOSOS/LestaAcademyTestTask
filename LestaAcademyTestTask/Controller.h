#pragma once

#include <memory>

class Printer;

class Controller
{
public:
	Controller() : printer(nullptr) {}

	void SetPrinter(std::shared_ptr<Printer> printer);

	bool StartGame();
	bool RestartGame();
	int ControlPromotePlayer();
private:
	std::shared_ptr<Printer> printer;
};