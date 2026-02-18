#include "Freighter.h"


Freighter::Freighter(Data& d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo)
:CivilianShip(d,fuel,max_fuel,consumption,resistance),
max_capacity(max_capacity),cargo(cargo){}


void Freighter::update(){
    switch (state) {
        case DEAD:
            return;
        case STOPPED:
            return;
        case ShipState::DOCKED:
            update_cargo();
            break;
        case ShipState::MOVING:
            CivilianShip::update();
            dock_at(curr_port);
            break;
        case W_REFUELING:
            return;
    }
}

void Freighter::update_cargo() {
    int i = is_exists(curr_port);
    if(i == -1) {return;}
    int mis = missions[i].second;
    if (mis > 0) {cargo = max_capacity;}
    else {
        if (cargo + mis >= 0) {
            cargo += mis;
        }else {
            //TODO: error -couerr
        }
    }
    missions.erase(missions.begin() + i);
}

void Freighter::describe() const{
    std::cout << "Freighter " << name << " at"  << position  << " fuel: "<< curr_fuel << " resistance: " << resistance
        << " Moving to " << curr_port->get_name() << "on course "<< to_degrees(rad_angle)<<"deg , speed "<<curr_speed<< " nm/hr moving to"<<
           "loadin/unloding dest" <<endl; //TODO need to finish
}

void Freighter::load_at(shared_ptr<Port>& p) {
    int i = is_exists(p);
    if(i == -1){missions.emplace_back(p,1);}
    else {missions[i].second = 1;}

}

void Freighter::unload_at(shared_ptr<Port>& p,int amount) {
    int i = is_exists(p);
    if(i == -1){missions.emplace_back(p,amount);}
    else {missions[i].second = missions[i].second > 0 ? 1 : missions[i].second-amount;}
}

int Freighter::is_exists(shared_ptr<Port> &p) const{
    for (int i =0; i<missions.size(); i++) {
        if (p == missions[i].first) { return i;}
    }
    return -1;
}

//
// void Freighter::set_destination(weak_ptr<Port> dest, double speed){
//     if (auto port = dest.lock()){
//         angle_to(port->get_pos());
//         current_speed = speed;
//     }
// }
//
// void Freighter::set_course(double speed, double angle){
//     Ship::angle = angle;
//     current_speed = speed;
// }
//
// void Freighter::set_destination(const Port &dest, double speed) {
//     curr_speed = speed < max_speed ? speed : max_speed;
//
// }
