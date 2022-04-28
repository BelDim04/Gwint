cmake_minimum_required(VERSION 3.21)
project(Gwint)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Gwint main.cpp Animation.cpp Class_Card.h Class_Game.h Class_Card.cpp Class_Game.cpp)

target_link_libraries(Gwint sfml-graphics sfml-audio)
