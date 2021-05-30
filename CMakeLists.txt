cmake_minimum_required(VERSION 3.0)

set(ENGINE_DIR ${CMAKE_SOURCE_DIR}/Engine)
set(GAME_DIR ${CMAKE_SOURCE_DIR}/Sokoban)

project(Engine VERSION 1.0)
set(PROJECT_DIR ${ENGINE_DIR})
include(${PROJECT_DIR}/CMakeLists.txt)

project(Sokoban VERSION 1.0)
set(PROJECT_DIR ${GAME_DIR})
include(${PROJECT_DIR}/CMakeLists.txt)
