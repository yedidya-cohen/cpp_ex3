#include "Freighter.h"

Freighter::Freighter(Data d, int max_capacity, int cargo, int resistance, weak_ptr<Port> destination):
CivilianShip(std::move(d), resistance), cargo(cargo),  max_capacity(max_capacity)  {}


void Freighter::update(){
    move_by_point();
}

void Freighter::describe() const{
    std::cout << "i am a freighter! i have your ali-express luxury items";
}

void Freighter::set_destination(weak_ptr<Port> dest, double speed){
    if (auto port = dest.lock()){
        angle_to(port->get_pos());
        current_speed = speed;
    }
}

void Freighter::set_course(double speed, double angle){
    Ship::angle = angle;
    current_speed = speed;
}
