cmake_minimum_required(VERSION 3.9)
project(SFML VERSION 1.0 DESCRIPTION "SFML system for fender")
set(CMAKE_CXX_STANDARD 17)

# Fining OpenGL
find_package(OpenGL REQUIRED)
message(OpenGL Found: ${OPENGL_FOUND})
message(  Glu  Found: ${OPENGL_GLU_FOUND})
find_package(GLEW REQUIRED)
message( GLEW  Found: ${GLEW_FOUND})
find_library(SOIL SOIL HINTS ../../../libs/soil/lib)
message( Soil  Found: ${SOIL})
FILE (GLOB ENTITIES ../../Entities/*.hpp)
FILE (GLOB COMPONENTS ../../Components/*.hpp)
FILE (GLOB ISOSHAPES ./IsoShapes/*.hpp ./IsoShapes/*.cpp)
FILE (GLOB UTILS ./Utils/*.hpp ./Utils/*.cpp)
FILE (GLOB SOURCES ./*.cpp ./*.hpp ./Camera/*.cpp ./Camera/*.hpp ${ENTITIES} ${COMPONENTS} ${ISOSHAPES} ${UTILS})

# Trying this to link static into shared library
#SET(SFML -Wl,-all ${SOIL} -Wl,-notall)

include_directories(${OPENGL_INCLUDE_DIR} ../../../libs/soil/src glm ${GLEW_INCLUDE_DIRS})
file(GLOB SOIL_SOURCES ../../../libs/soil/src/*.c)
add_library(SFML SHARED ${SOURCES} ${SOIL_SOURCES})

target_link_libraries(SFML -lstdc++fs ${OPENGL_LIBRARIES} ${SOIL} ${GLEW_LIBRARIES})
set_target_properties(SFML PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(SFML PROPERTIES PUBLIC_HEADER SFML.hpp)