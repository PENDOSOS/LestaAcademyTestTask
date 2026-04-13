set(CORE_SOURCES
  "Weapon.h" 
  "Weapon.cpp" 
  "Monster.h" 
  "Monster.cpp" 
  "Character.h" 
  "Player.h" 
  "Player.cpp" 
  "Spawner.h" 
  "Spawner.cpp" 
  "Arena.h" 
  "Arena.cpp" 
  "PlayerPromoter.h" 
  "PlayerPromoter.cpp" 
  "Printer.h" 
  "Printer.cpp" 
  "Controller.h" 
  "Controller.cpp" 
  "Character.cpp"
)

add_library(LestaAcademyCore STATIC ${CORE_SOURCES})

# Заголовки будут доступны всем, кто линкует эту библиотеку
target_include_directories(LestaAcademyCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable (LestaAcademyTestTask "main.cpp")

target_link_libraries(LestaAcademyTestTask PRIVATE LestaAcademyCore)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LestaAcademyTestTask PROPERTY CXX_STANDARD 20)
endif()