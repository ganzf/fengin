cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 17)
project(fengin)

execute_process(
        COMMAND git submodule update --remote --init
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)

SET(INCLUDED_DIRECTORIES include modules src)
include_directories(${INCLUDED_DIRECTORIES})
add_subdirectory(src/Systems/Log)
add_subdirectory(src/Systems/SFML)
add_subdirectory(src/Systems/Fysix)