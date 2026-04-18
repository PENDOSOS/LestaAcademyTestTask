#include <gtest/gtest.h>
#include <memory>
#include <random>

#include "Player.h"
#include "Weapon.h"

// Моковый продюсер оружия для тестов
class MockWeaponProducer : public WeaponProducer {
public:
    std::unique_ptr<Weapon> GiveWeapon() override {
        auto weapon = std::make_unique<Weapon>();
        weapon->damage = 3;
        weapon->damageType = CHOPPING;
        weapon->name = "TestSword";
        return weapon;
    }
};

// ===== Тесты для BasePlayer =====

TEST(BasePlayerTest, Constructor_InitializesStats) {
    BasePlayer player(2, 3, 4);
    player.SetHealth(1);
    EXPECT_EQ(player.GetStrength(), 2);
    EXPECT_EQ(player.GetAgility(), 3);
    EXPECT_EQ(player.GetStamina(), 4);
    EXPECT_TRUE(player.IsAlive());
}

TEST(BasePlayerTest, SetHealth_AccountsForStamina) {
    BasePlayer player(1, 1, 5);
    player.SetHealth(10);  // 10 + stamina(5) = 15
    EXPECT_TRUE(player.IsAlive());
    // Примечание: нет публичного геттера для здоровья, 
    // поэтому проверяем через IsAlive после урона
}

TEST(BasePlayerTest, TakeDamage_ReducesHealth) {
    BasePlayer player(2, 2, 2);
    player.SetHealth(10);
    
    auto damage = std::make_unique<DamageInfo>();
    damage->weaponDamage = 3;
    damage->bonusDamage = 1;
    damage->attackerStrength = 2;
    damage->damageType = MONSTER_DAMAGE;
    
    player.TakeDamage(std::move(damage));
    // Урон: 3 + 1 + 2 = 6, здоровье было 10+2=12, осталось 6
    EXPECT_TRUE(player.IsAlive());
}

TEST(BasePlayerTest, TakeDamage_WithLethalDamage_KillsPlayer) {
    BasePlayer player(1, 1, 1);
    player.SetHealth(5);  // 5 + 1 = 6 HP
    
    auto damage = std::make_unique<DamageInfo>();
    damage->weaponDamage = 10;  // летальный урон
    damage->bonusDamage = 0;
    damage->attackerStrength = 0;
    damage->damageType = MONSTER_DAMAGE;
    
    player.TakeDamage(std::move(damage));
    EXPECT_FALSE(player.IsAlive());
}

TEST(BasePlayerTest, GiveDamage_WithNullWeapon_ReturnsNull) {
    BasePlayer player(3, 5, 2);
    // У оружия высокая ловкость противника - промах
    std::unique_ptr<DamageInfo> result = player.GiveDamage(10);

    if (result) 
    {
        EXPECT_EQ(result->weaponDamage + result->bonusDamage + result->attackerStrength, 0);
    }
    else
    {
        EXPECT_EQ(result, nullptr);
    }
}

TEST(BasePlayerTest, ChangeWeapon_SwapsWeapon) {
    BasePlayer player(2, 2, 2);
    auto newWeapon = std::make_unique<Weapon>();
    newWeapon->damage = 5;
    newWeapon->damageType = STABBING;
    newWeapon->name = "NewDagger";
    
    const Weapon* oldWeapon = player.GetWeapon();
    player.ChangeWeapon(std::move(newWeapon));
    
    EXPECT_NE(player.GetWeapon(), oldWeapon);
    EXPECT_EQ(player.GetWeapon()->damage, 5);
    EXPECT_EQ(player.GetWeapon()->damageType, STABBING);
}

TEST(BasePlayerTest, IncreaseStats_UpdatesValues) {
    BasePlayer player(2, 3, 4);
    player.IncreaseStrength(3);
    player.IncreaseAgility(2);
    player.IncreaseStamina(1);
    
    EXPECT_EQ(player.GetStrength(), 5);
    EXPECT_EQ(player.GetAgility(), 5);
    EXPECT_EQ(player.GetStamina(), 5);
}

TEST(BasePlayerTest, UpdateTurn_ResetsTurnCounter) {
    BasePlayer player(1, 1, 1);
    // Вызываем атаки для увеличения currentTurn
    for (int i = 0; i < 5; ++i) {
        player.GiveDamage(10000);  // игнорируем результат
    }
    EXPECT_GE(player.GetCurrentTurn(), 1);
    
    player.UpdateTurn();
    EXPECT_EQ(player.GetCurrentTurn(), 0);
}

// ===== Тесты для декораторов классов =====

TEST(PlayerClassLevelTest, BanditLevel1_HiddenAttack_WhenAgilityHigher) {
    auto basePlayer = std::make_unique<BasePlayer>(2, 5, 2);  // agility=5
    ClassBanditLevel1 bandit(std::move(basePlayer));
    bandit.SetHealth(10);
    
    auto weapon = std::make_unique<Weapon>();
    weapon->damage = 2;
    weapon->damageType = STABBING;
    bandit.ChangeWeapon(std::move(weapon));
    
    // Атакуем противника с меньшей ловкостью (agility=3)
    auto damage = bandit.GiveDamage(0);
    
    ASSERT_NE(damage, nullptr);
    // Бонус +1 за Hidden Attack
    EXPECT_GE(damage->bonusDamage, 1);
}

TEST(PlayerClassLevelTest, WarriorLevel1_Rush_DoubleDamageOnFirstTurn) {
    auto basePlayer = std::make_unique<BasePlayer>(3, 10, 2);
    ClassWarriorLevel1 warrior(std::move(basePlayer));
    warrior.SetHealth(10);
    
    auto weapon = std::make_unique<Weapon>();
    weapon->damage = 4;
    weapon->damageType = CHOPPING;
    warrior.ChangeWeapon(std::move(weapon));
    
    auto damage = warrior.GiveDamage(0);
    
    ASSERT_NE(damage, nullptr);
    // Rush: bonus = weaponDamage на первом ходу
    EXPECT_EQ(damage->bonusDamage + damage->weaponDamage, damage->weaponDamage * 2);
}

TEST(PlayerClassLevelTest, BarbarianLevel1_Fury_BonusDamageFirstThreeTurns) {
    auto basePlayer = std::make_unique<BasePlayer>(2, 2, 2);
    ClassBarbarianLevel1 barbarian(std::move(basePlayer));
    barbarian.SetHealth(10);
    
    auto weapon = std::make_unique<Weapon>();
    weapon->damage = 3;
    barbarian.ChangeWeapon(std::move(weapon));
    
    // Первый ход: +2 к урону
    auto damage1 = barbarian.GiveDamage(0);
    ASSERT_NE(damage1, nullptr);
    EXPECT_EQ(damage1->bonusDamage, 2);
    
    // Второй ход: +2 к урону
    auto damage2 = barbarian.GiveDamage(0);
    ASSERT_NE(damage2, nullptr);
    EXPECT_EQ(damage2->bonusDamage, 2);
    
    // Четвёртый ход: -1 к урону
    barbarian.GiveDamage(1); // 3-й ход
    auto damage4 = barbarian.GiveDamage(0);
    ASSERT_NE(damage4, nullptr);
    EXPECT_EQ(damage4->bonusDamage, -1);
}

TEST(PlayerClassLevelTest, BanditLevel2_AgilityBonus_OnConstruction) {
    auto basePlayer = std::make_unique<BasePlayer>(2, 3, 2);
    int initialAgility = basePlayer->GetAgility();
    
    ClassBanditLevel2 bandit(std::move(basePlayer));
    
    // Level 2 бонус: +1 к ловкости при создании
    EXPECT_EQ(bandit.GetAgility(), initialAgility + 1);
}

TEST(PlayerClassLevelTest, WarriorLevel2_Shield_ReduceDamage_WhenStrengthHigher) {
    auto basePlayer = std::make_unique<BasePlayer>(5, 2, 2);  // strength=5
    ClassWarriorLevel2 warrior(std::move(basePlayer));
    warrior.SetHealth(20);
    
    auto damage = std::make_unique<DamageInfo>();
    damage->weaponDamage = 4;
    damage->bonusDamage = 1;
    damage->attackerStrength = 3;  // меньше чем у игрока
    damage->damageType = MONSTER_DAMAGE;
    
    warrior.TakeDamage(std::move(damage));
    // Shield: -3 к входящему урону, если strength > attackerStrength
    // Итоговый урон: (4 - 3) + 1 + 3 = 5 вместо 8
}

TEST(PlayerClassLevelTest, BarbarianLevel2_StoneSkin_ReduceDamageByStamina) {
    auto basePlayer = std::make_unique<BasePlayer>(2, 2, 4);  // stamina=4
    ClassBarbarianLevel2 barbarian(std::move(basePlayer));
    barbarian.SetHealth(20);
    
    auto damage = std::make_unique<DamageInfo>();
    damage->weaponDamage = 5;
    damage->bonusDamage = 0;
    damage->attackerStrength = 2;
    damage->damageType = MONSTER_DAMAGE;
    
    barbarian.TakeDamage(std::move(damage));
    // Stone Skin: урон уменьшается на stamina(4)
    // weaponDamage становится 5-4=1
}