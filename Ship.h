#ifndef EX3_SHIP_H
#define EX3_SHIP_H

#include <string>
#include "Geometry.h"


class Port;
//this class represent abstract of a ship - all the ships have them
class Ship {
public:
    //enum to control states -
    enum ShipState{
        STOPPED = 0,
        DOCKED = 1,
        W_REFUELING = 2, //wait for refuel
        DEAD = 3,
        MOVING = 4,
    };
//for convient - there are many argument if not implemented
    struct Data{
        std::string name;
        double curr_speed,angle,max_speed;
        Point pos;
        ShipState state;
    };

    virtual ~Ship() = default;

    //default c'tor
    explicit Ship(const Data& d):name(d.name),curr_speed(d.curr_speed)
        ,rad_angle(to_radians(d.angle)),max_speed(d.max_speed), position(d.pos),pending_moving(false), state(d.state) {}

//move next step - its virtual - in ship only responsible for movment
    virtual void update();

    //getters
    std::string get_name() const{return name;}
    Point get_position() const {return position;}
    ShipState get_state() const {return state;}

    //course command - where to go
    void set_course(double angle,double speed);
    //stop command
    void stop();
    //set pos - where to go postion wise
    void set_pos(Point p,double speed);
    //create abstract class
    virtual void describe() const = 0;
    //if not dead we allow to change in spesic state
    void set_state(const ShipState s) {
        if (state!=DEAD)
            state = s;
    }

protected:
    std::string name;
    double curr_speed, rad_angle; // angle is save in radiants, to cout need to convert to degree and add 90
    double max_speed;
    Point position;
    bool pending_moving;
    ShipState state;

    void set_speed(double speed);

};



#endif
