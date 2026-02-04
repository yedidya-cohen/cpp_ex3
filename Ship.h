#ifndef EX3_SHIP_H
#define EX3_SHIP_H

#include <string>
#include <utility>
#include <memory>
#include "Port.h"
#include <iostream>
#include <cmath>
#include "Geometry.h"

using namespace std;

enum ShipState{
    STOPPED = 0,
    DOCKED = 1,
    W_REFUELING = 2,
    DEAD = 3,
    MOVING = 4,
    ON_COURSE = 5
};

struct Data{
    string name;
    double curr_speed,angle,max_speed;
    Point pos;
    ShipState state;
};


class Ship {
public:
    virtual ~Ship() = default; //abstract

    explicit Ship(const Data& d):name(d.name),curr_speed(d.curr_speed)
        ,rad_angle(to_radians(d.angle)),max_speed(d.max_speed), position(d.pos),state(d.state) {}

    Ship(const Ship& other) = default;

    Ship& operator=(const Ship& other)=default;

    // static inline double calc_dist(const Ship& s1,const Ship& s2){
    //     return sqrt( pow(s1.position.get_x()-s2.position.get_x(),2) + pow(s1.position.get_y()-s2.position.get_y(),2));
    // }
    //
    // virtual void update() =0 ;
    // virtual void describe() const{}
    // virtual void stop() = 0;

    //getters
    string get_name() const{return name;}
    Point get_position() const {return position;}
    ShipState get_state() const {return state;}

    //course command
    void set_course(double angle,double speed) {
        this->rad_angle = to_radians(angle);
        this->curr_speed = speed;
    }

    void stop() {
        state = STOPPED;
        curr_speed= 0;
        rad_angle= 0;
    }

    void set_pos(Point p,double speed) {
        //calc the angle to this pos - set target
        state = MOVING;
        curr_speed = speed;
        rad_angle = std::atan2(p.y-position.y,p.x-position.x);

    }

    void set_destination(Port& p, double speed) {
        Point p_dest = p.get_position();
        set_pos(p_dest,speed);
    }

    void set_state(const ShipState s) {
        if (state!=DEAD)
            state = s;
    }

protected:
    string name;
    double curr_speed, rad_angle; // angle is save in radiants, to output need to convert to degree and add 90 (to clock wise turn)
    double max_speed;
    Point position;
    ShipState state;

    // void move_by_point() //update
    // {
    //     //TODO: check if outside boarder
    //     double new_x = Ship::position.get_x() + Ship::curr_speed * sin(angle);
    //     double new_y = Ship::position.get_y() + Ship::curr_speed * cos(angle);
    //     Point p (new_x, new_y);
    //     position = p;
    // }
    //


};

#endif
