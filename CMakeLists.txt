cmake_minimum_required(VERSION 3.10)

project(harmonic-oscillation-simulator)

find_package(SFML 2.6.1 COMPONENTS system window graphics network audio REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

add_library(Graph graph.cpp)

add_library(Button ./button/Button.cpp)

target_link_libraries(harmonic-oscillation-simulator sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
target_link_libraries(Graph sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
target_link_libraries(Button sfml-system sfml-window sfml-graphics sfml-network sfml-audio)
target_link_libraries(harmonic-oscillation-simulator Graph)
target_link_libraries(harmonic-oscillation-simulator Button)



