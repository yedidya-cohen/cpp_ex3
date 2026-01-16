#ifndef EX3_SHIP_H
#define EX3_SHIP_H

#include <string>
#include <utility>

#include "Point.h"
using namespace std;

enum ShipState{
    STOPPED = 0,
    DOCKED = 1,
    DEAD = 2,
    MOVING = 3,
    ON_COURSE = 4
};


class Ship{
public:
    virtual ~Ship() = default; //abstract

    Ship(string name, double consumpsion, double max_speed , double fuel, double current_speed, double angle, Point position) :
    name(std::move(name)), fuel(fuel), consumpsion(consumpsion), max_speed(max_speed), current_speed(current_speed), angle(angle), position(position) {state = STOPPED;}

    virtual void update() = 0;
    virtual void describe() const = 0;
    virtual void set_destination() = 0;
    virtual void set_course() = 0;
    virtual void stop() = 0;
    virtual void attack(Ship* o) = 0;
    virtual void receive_damage(double damage) = 0 ;


protected:
    const string name;
    const double consumpsion, max_speed;
    double fuel, current_speed, angle;
    Point position;
    weak_ptr<Port> destination; //TODO: weak_ptr or shared_ptr?
    ShipState state;


};

#endif