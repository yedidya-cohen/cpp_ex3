cmake_minimum_required(VERSION 3.26)
project(ex3)

set(CMAKE_CXX_STANDARD 17)

add_executable(ex3 main.cpp
        Ship.h
        Point.h
        Freighter.h
        Port.h
        Patrol.cpp
        Patrol.h
        Cruiser.cpp
        Cruiser.h
        Port.cpp
        CivilianShip.h
        Freighter.cpp
)
