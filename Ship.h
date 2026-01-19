#ifndef EX3_SHIP_H
#define EX3_SHIP_H

#include <string>
#include <utility>
#include <memory>
#include "Point.h"
#include "Port.h"
#include <iostream>
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
    double curr_speed,angle,max_speed;
    Point pos;
    ShipState state;
};

class Ship{
public:
    virtual ~Ship() = default; //abstract

    explicit Ship(const Data& d):name(d.name),curr_speed(d.curr_speed)
        ,angle(d.angle),max_speed(d.max_speed), position(d.pos),state(d.state) {}


    virtual void update() = 0;
    virtual void describe() const = 0;
    virtual void stop() = 0;



protected:
    const string name;
    double curr_speed, angle;
    const double max_speed;
    Point position;
    ShipState state;

    void move_by_point()
    {
        //TODO: check if outside boarder
        double new_x = Ship::position.get_x() + Ship::curr_speed * sin(angle);
        double new_y = Ship::position.get_y() + Ship::curr_speed * cos(angle);
        Point p (new_x, new_y);
        position = p;
    }

    void angle_to(const Point o)
    {
        double dx = o.get_x() - Ship::position.get_x();
        double dy = o.get_y() - Ship::position.get_y();
        double tmp = atan2(dy,dx) * 180 / M_PI;
        angle = tmp > 0 ? tmp : 360 + tmp;
    }

};

#endif