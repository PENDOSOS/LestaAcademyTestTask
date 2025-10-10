add_executable (LestaAcademyTestTask "main.cpp"  "Weapon.h" "Weapon.cpp" "Monster.h" "Monster.cpp" "Character.h" "Player.h" "Player.cpp" "Spawner.h" "Spawner.cpp" "Arena.h" "Arena.cpp" "PlayerPromoter.h" "PlayerPromoter.cpp" "Printer.h" "Printer.cpp" "Controller.h" "Controller.cpp" "Character.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LestaAcademyTestTask PROPERTY CXX_STANDARD 20)
endif()