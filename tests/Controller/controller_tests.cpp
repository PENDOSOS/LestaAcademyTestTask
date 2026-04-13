#include <gtest/gtest.h>
#include <sstream>
#include <memory>

#include "Controller.h"
#include "Printer.h"

// Моковый Printer для тестов Controller
class MockPrinter : public Printer {
public:
    void PrintStartMessage()  {
        startMessageCalled = true;
    }
    
    void PrintCharacterStats(const Character* character)  {
        (void)character;
    }
    
    void PrintBattleResult(bool playerWon, const std::string& opponentName)  {
        (void)playerWon;
        (void)opponentName;
    }
    
    void PrintLevelUpOptions()  {
        levelUpOptionsCalled = true;
    }
    
    void PrintWeaponOffer(const Weapon* weapon) {
        (void)weapon;
    }
    
    void PrintGameWon()  {
        gameWonCalled = true;
    }
    
    void PrintGameOver()  {
        gameOverCalled = true;
    }
    
    bool startMessageCalled = false;
    bool levelUpOptionsCalled = false;
    bool gameWonCalled = false;
    bool gameOverCalled = false;
};

Controller controller;
auto printer = std::make_shared<MockPrinter>();

// ===== Тесты для Controller =====
TEST(ControllerTest, StartGame_WithNullPrinter_ReturnsFalse) {
    Controller controller;
    // printer не установлен
    EXPECT_FALSE(controller.StartGame());
}

TEST(ControllerTest, StartGame_WithPrinter_CallsPrintStartMessage) {
    controller.SetPrinter(printer);
    
    // Перехватываем cin для RestartGame
    std::stringstream input("0\n");  // "no" для новой игры
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    bool result = controller.StartGame();
    
    std::cin.rdbuf(originalCin);  // восстанавливаем cin
    
    EXPECT_TRUE(printer->startMessageCalled);
    EXPECT_FALSE(result);  // пользователь выбрал "не начинать"
}

TEST(ControllerTest, RestartGame_ValidInputYes_ReturnsTrue) {
    controller.SetPrinter(printer);
    
    std::stringstream input("1\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    bool result = controller.RestartGame();
    
    std::cin.rdbuf(originalCin);
    EXPECT_TRUE(result);
}

TEST(ControllerTest, RestartGame_ValidInputNo_ReturnsFalse) {
    controller.SetPrinter(printer);
    
    std::stringstream input("0\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    bool result = controller.RestartGame();
    
    std::cin.rdbuf(originalCin);
    EXPECT_FALSE(result);
}

TEST(ControllerTest, RestartGame_InvalidInputThenValid_HandlesCorrectly) {
    controller.SetPrinter(printer);
    
    // Сначала невалидный ввод, потом "1"
    std::stringstream input("abc\n1\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    bool result = controller.RestartGame();
    
    std::cin.rdbuf(originalCin);
    EXPECT_TRUE(result);
}

TEST(ControllerTest, ControlPromotePlayer_ValidClass1_Returns0) {
    Controller controller;
    
    std::stringstream input("1\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    int result = controller.ControlPromotePlayer();
    
    std::cin.rdbuf(originalCin);
    EXPECT_EQ(result, 0);  // 1 -> индекс 0
}

TEST(ControllerTest, ControlPromotePlayer_ValidClass3_Returns2) {   
    std::stringstream input("3\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    int result = controller.ControlPromotePlayer();
    
    std::cin.rdbuf(originalCin);
    EXPECT_EQ(result, 2);  // 3 -> индекс 2
}

TEST(ControllerTest, ControlPromotePlayer_InvalidThenValid_HandlesCorrectly) {
    std::stringstream input("5\n2\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    int result = controller.ControlPromotePlayer();
    
    std::cin.rdbuf(originalCin);
    EXPECT_EQ(result, 1);  // 2 -> индекс 1
}

TEST(ControllerTest, ControlPromotePlayer_NonNumericInput_HandlesCorrectly) {
    std::stringstream input("abc\n1\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    int result = controller.ControlPromotePlayer();
    
    std::cin.rdbuf(originalCin);
    EXPECT_EQ(result, 0);
}

TEST(ControllerTest, ControlChangeWeapon_ValidTrue_ReturnsTrue) {
    std::stringstream input("1\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    bool result = controller.ControlChangeWeapon();
    
    std::cin.rdbuf(originalCin);
    EXPECT_TRUE(result);
}

TEST(ControllerTest, ControlChangeWeapon_ValidFalse_ReturnsFalse) {
    std::stringstream input("0\n");
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    bool result = controller.ControlChangeWeapon();
    
    std::cin.rdbuf(originalCin);
    EXPECT_FALSE(result);
}

TEST(ControllerTest, ControlChangeWeapon_InvalidInput_HandlesCorrectly) {
    std::stringstream input("2\n0\n");  // 2 - невалидно, 0 - валидно
    std::streambuf* originalCin = std::cin.rdbuf(input.rdbuf());
    
    bool result = controller.ControlChangeWeapon();
    
    std::cin.rdbuf(originalCin);
    EXPECT_FALSE(result);
}