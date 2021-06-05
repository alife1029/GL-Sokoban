cmake_minimum_required(VERSION 3.0)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)

# Directories
set(DEPENDENCIES_DIR ${CMAKE_SOURCE_DIR}/Dependencies)
set(ENGINE_DIR ${CMAKE_SOURCE_DIR}/Engine)
set(GAME_DIR ${CMAKE_SOURCE_DIR}/Sokoban)

# Handle dependencies
include(${DEPENDENCIES_DIR}/CMakeLists.txt)

# Engine Project
project(Engine VERSION 1.0)
set(PROJECT_DIR ${ENGINE_DIR})
include(${PROJECT_DIR}/CMakeLists.txt)

# Game Project
project(Sokoban VERSION 1.0)
set(PROJECT_DIR ${GAME_DIR})
include(${PROJECT_DIR}/CMakeLists.txt)
