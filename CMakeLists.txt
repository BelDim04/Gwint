cmake_minimum_required(VERSION 3.21)
project(TP_Gwint)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(TP_Gwint main.cpp Animation.cpp Class_Card.cpp Class_Game.cpp Class_Card.h Bot_Logic.h Card_src.h Bot_decks.h Player_decks.h Animation.h)

target_link_libraries(TP_Gwint sfml-graphics)