cmake_minimum_required(VERSION 3.14)
project(CPendulum CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/6.0.tar.gz
)


set(SOURCES
        src/main.cpp
        src/constants.hpp
		src/utils.hpp
		src/pendulum/object/verlet_object.hpp
		src/pendulum/object/verlet_object.cpp
		src/pendulum/simulation/pendulum_simulation.hpp
		src/pendulum/simulation/pendulum_simulation.cpp
		src/pendulum/ui/pendulum_ui.hpp
		src/pendulum/ui/pendulum_ui.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
