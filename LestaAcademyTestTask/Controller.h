#pragma once

#include <memory>

class Printer;

class Controller
{
public:
	Controller(std::shared_ptr<Printer> printer = nullptr);

	void StartGame();
	bool RestartGame();
	void PromotePlayer();
private:
	std::shared_ptr<Printer> printer;
};