

#include "Cruiser.h"

Cruiser::Cruiser(Data d, double range, double force): Ship(d), range(range), force(force) {}
//pirates!

void Cruiser::update() {
    double new_x, new_y;
    new_x = Ship::position.get_x() + Ship::current_speed * sin(angle);
    new_y = Ship::position.get_y() + Ship::current_speed * cos(angle);
    Point p (new_x, new_y);
    Ship::position = p;
}

void Cruiser::set_course(double speed, double angle) {
    current_speed = speed;
    this->angle = angle;
}

void Cruiser::describe() const {

}

void Cruiser::attack(const weak_ptr<Ship>& s) {
    if(force > s.get_force())

}


Cruiser::stop(){
    Ship::state = STOPPED;
    current_speed = 0;
    angle = 0;
}




