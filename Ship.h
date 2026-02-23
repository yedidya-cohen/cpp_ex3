#ifndef EX3_SHIP_H
#define EX3_SHIP_H

#include <string>
#include <utility>
#include <memory>
#include <iostream>
#include <cmath>
#include "Geometry.h"


class Port;

class Ship {
public:
    enum ShipState{
        STOPPED = 0,
        DOCKED = 1,
        W_REFUELING = 2,
        DEAD = 3,
        MOVING = 4,
    };

    struct Data{
        std::string name;
        double curr_speed,angle,max_speed;
        Point pos;
        ShipState state;
    };

    virtual ~Ship() = default; //abstract

    explicit Ship(const Data& d):name(d.name),curr_speed(d.curr_speed)
        ,rad_angle(to_radians(d.angle)),max_speed(d.max_speed), position(d.pos),state(d.state),pending_moving(false) {}

    Ship(const Ship& other) = default;

    Ship& operator=(const Ship& other)=default;

    // static inline double calc_dist(const Ship& s1,const Ship& s2){
    //     return sqrt( pow(s1.position.get_x()-s2.position.get_x(),2) + pow(s1.position.get_y()-s2.position.get_y(),2));
    // }
    //

    // virtual void describe() const{}
    // virtual void stop() = 0;
//move next step
    virtual void update() {
        //angel - radiants
        //speed
         position =  calculate_next_pos(position,rad_angle,curr_speed);
    }

    //getters
    std::string get_name() const{return name;}
    Point get_position() const {return position;}
    ShipState get_state() const {return state;}

    //course command
    void set_course(double angle,double speed) {
        if (state!=W_REFUELING && state!=DEAD) {state = MOVING;}
        if (state == W_REFUELING) {pending_moving = true;}
        this->rad_angle = to_radians(angle);
        set_speed(speed);
    }

    void stop() {
        state = STOPPED;
        curr_speed= 0;
        rad_angle= 0;
    }

    void set_pos(Point p,double speed) {
        //calc the angle to this pos - set target
        if (state!=W_REFUELING && state!=DEAD) {state = MOVING;}
        if (state == W_REFUELING) {pending_moving = true;}
        set_speed(speed);
        rad_angle = std::atan2(p.y-position.y,p.x-position.x);
    }

    virtual void describe() const = 0;

    void set_state(const ShipState s) {
        if (state!=DEAD)
            state = s;
    }

protected:
    std::string name;
    double curr_speed, rad_angle; // angle is save in radiants, to output need to convert to degree and add 90 (to clock wise turn)
    double max_speed;
    Point position;
    bool pending_moving;
    ShipState state;

    void set_speed(double speed);

};



using ShipState = Ship::ShipState;
using Data = Ship::Data;

#endif
