#include "Ship.h"
#include <cmath>

void Ship::set_speed(double speed)
{
    //speed is legit
    if (speed < 0.0) { curr_speed = 0.0;}
    else if (speed > max_speed) {curr_speed = max_speed;}
    else {curr_speed = speed;}
}

void Ship::update() {
    position =  calculate_next_pos(position,rad_angle,curr_speed);
}

void Ship::set_course(double angle, double speed) {
    if (state!=W_REFUELING && state!=DEAD) {state = MOVING;} //if we are not dead or waiting foe refeul than we move
    if (state == W_REFUELING) {pending_moving = true;} //if someone tell us in the refuel we save and later we will move
    this->rad_angle = to_radians(angle);
    set_speed(speed);
}

void Ship::stop() {
    state = STOPPED;
    curr_speed= 0;
    rad_angle= 0;
}

void Ship::set_pos(Point p, double speed) {
    //calc the angle to this pos - set target
    if (state!=W_REFUELING && state!=DEAD) {state = MOVING;} //same as set course
    if (state == W_REFUELING) {pending_moving = true;}
    set_speed(speed);
    rad_angle = std::atan2(p.y-position.y,p.x-position.x); //the angle between the 2 postions
}
