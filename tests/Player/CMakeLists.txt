cmake_minimum_required(VERSION 3.8)

# === Исходники основного проекта для линковки ===
set(PLAYER_SOURCES
    ${CMAKE_SOURCE_DIR}/LestaAcademyTestTask/Player.cpp
    ${CMAKE_SOURCE_DIR}/LestaAcademyTestTask/Character.cpp
    ${CMAKE_SOURCE_DIR}/LestaAcademyTestTask/Weapon.cpp
)

set(TARGET_NAME 
    player_tests
)

# # === Общие настройки компиляции для тестов ===
# macro(configure_test_target TARGET_NAME SOURCES)
#     add_executable(${TARGET_NAME} ${SOURCES})
    
#     target_include_directories(${TARGET_NAME} PUBLIC 
#         ${CMAKE_SOURCE_DIR}/LestaAcademyTestTask
#     )
    
#     # Линкуем GTest + потоки (обязательно для Linux)
#     target_link_libraries(${TARGET_NAME} PRIVATE
#         LestaAcademyCore 
#         GTest::gtest_main
#         Threads::Threads
#     )
    
#     set_target_properties(${TARGET_NAME} PROPERTIES 
#         CXX_STANDARD 20
#         CXX_STANDARD_REQUIRED ON
#     )
    
#     # Регистрация тестов в CTest
#     include(GoogleTest)
#     gtest_discover_tests(${TARGET_NAME})
# endmacro()

# # === Создаём тесты ===
# configure_test_target(player_tests 
#     player_tests.cpp
#     ${PLAYER_SOURCES}
# )

add_executable(${TARGET_NAME} player_tests.cpp ${PLAYER_SOURCES})
    
target_include_directories(${TARGET_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}/LestaAcademyTestTask
)
    
# Линкуем GTest + потоки (обязательно для Linux)
target_link_libraries(${TARGET_NAME} PRIVATE
    LestaAcademyCore 
    GTest::gtest_main
    Threads::Threads
)
    
set_target_properties(${TARGET_NAME} PROPERTIES 
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)
    
# Регистрация тестов в CTest
include(GoogleTest)
gtest_discover_tests(${TARGET_NAME})