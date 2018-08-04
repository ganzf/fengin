cmake_minimum_required(VERSION 3.9)
project(Fysix VERSION 1.0 DESCRIPTION "Fysix system for fender")
include_directories(${INCLUDED_DIRECTORIES} ${CMAKE_CURRENT_SOURCE_DIR}/../../)
add_library(Fysix SHARED Fysix.cpp Fysix.hpp Collision.cpp Collision.hpp RigidBody.cpp RigidBody.hpp)
target_include_directories(Fysix PUBLIC include utils)
set_target_properties(Fysix PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(Fysix PROPERTIES PUBLIC_HEADER Fysix.hpp)

#target_include_directories(Log PUBLIC ${INCLUDED_DIRECTORIES})