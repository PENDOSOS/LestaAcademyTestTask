cmake_minimum_required(VERSION 3.8)



# === Исходники основного проекта для линковки ===
set(CONTROLLER_SOURCES
    ${CMAKE_SOURCE_DIR}/LestaAcademyTestTask/Controller.cpp
    ${CMAKE_SOURCE_DIR}/LestaAcademyTestTask/Printer.cpp
)

set(TARGET_NAME 
    controller_tests
)

add_executable(${TARGET_NAME} controller_tests.cpp ${CONTROLLER_SOURCES})
    
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