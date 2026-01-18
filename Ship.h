#ifndef EX3_SHIP_H
#define EX3_SHIP_H

#include <string>
#include <utility>
#include <memory>
#include "Point.h"
#include "Port.h"
#include <cmath>
using namespace std;

enum ShipState{
    STOPPED = 0,
    DOCKED = 1,
    DEAD = 2,
    MOVING = 3,
    ON_COURSE = 4
};

struct Data{
    string name;
    double consumpsion;
    double max_speed;
    double max_fuel;
    double curr_fuel;
    double curr_speed;
    double angle;
    Point position;
};

class Ship{
public:
    virtual ~Ship() = default; //abstract

    Ship(Data d) :
    name(std::move(d.name)), fuel(d.curr_fuel), consumpsion(d.consumpsion), max_speed(d.max_speed), max_fuel(d.max_fuel),
    current_speed(d.curr_speed), angle(d.angle), position(d.position) {state = STOPPED;}

    virtual void update() = 0;
    virtual void describe() const = 0;
    virtual void set_course(double speed, double angle) = 0;
    virtual void stop() = 0;
    virtual double get_force() const = 0;



protected:

    const string name;
    const double consumpsion, max_speed,max_fuel;
    double fuel, current_speed, angle;
    Point position;
    weak_ptr<Port> destination;
    ShipState state;


};

#endif