cmake_minimum_required(VERSION 3.26)
project(ex3)

set(CMAKE_CXX_STANDARD 17)

add_executable(ex3 main.cpp
        View.h
        View.cpp
        Geometry.cpp
        Geometry.h
        Model.cpp
        Model.h
        Ship.h
        CivilianShip.h
        CivilianShip.cpp
        Cruiser.cpp
        Cruiser.h
        Freighter.cpp
        Freighter.h
        Patrol.h
        Patrol.cpp
        Port.h
        Port.cpp
        Controller.cpp
        Controller.h
        Ship.cpp
)
