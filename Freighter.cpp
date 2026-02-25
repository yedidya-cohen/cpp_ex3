#include "Freighter.h"
#include "Port.h"

using namespace std;


Freighter::Freighter(Data& d,double fuel, double max_fuel, double consumption, int resistance ,int max_capacity,int cargo)
:CivilianShip(d,fuel,max_fuel,consumption,resistance),
max_capacity(max_capacity),cargo(cargo){}


void Freighter::update(){ // update the ship by 1hr
    switch (state) {
        case DEAD: //if we dead there is nothing to do
            return;
        case STOPPED: //only when attack/start
            state = MOVING;
            return;
        case ShipState::DOCKED: //if we docked check for missions of load\unload
            update_cargo();
            break;
        case ShipState::MOVING: // just move the ship by 1hr drive
            CivilianShip::update();
            break;
        case W_REFUELING: // we are waiting for refuel at a port
            if (refuel_completed) {
                state = DOCKED;
                refuel_completed = false;
            }
            break;
        default:
            cerr<< "Freighter::update reached invalid state";
            break;
    }
}

void Freighter::update_cargo() {
    auto cp = docked_port.lock();
    if (!cp) return; //checks if the port we are docked right now is still exists
    int i = is_exists(cp->get_name()); // checks if there is a mission at the port
    if(i == -1) {  // if there is not a mission and there is a next mission move at the next turn
        if (pending_moving) {pending_moving = false; state = MOVING;}
        return;
    }
    // if there is a mission, if the second is >0 load till max and if 0< unload as the value
    int mis = missions[i].second;
    if (mis > 0) {cargo = max_capacity;}  // 1 so load till max
    else { // unload cargo
        if (cargo + mis >= 0) { //checks if we need to unload less then we have
            cargo += mis;
        }else { // if we need to unload more then we have, unload as much as possible and print error
            cargo = 0;
            cerr<<"try to unload more than exsist - WARNING"<<endl;
        }
    }
    missions.erase(missions.begin() + i); //erase the mission - complete!
}

void Freighter::describe() const {
    //some argiment that not always exsist so we print them if exist
    const auto cp = next_port.lock();
    const string target_name = cp ? cp->get_name() : "None";
    string mission_desc = "";
    int idx = is_exists(target_name);
    if (idx != -1) {
        int m = missions[idx].second;
        mission_desc = m > 0 ? " loading at " + target_name : " unloading at " + target_name;
    }
    std::cout << "Freighter " << name << " at "  << position   <<" fuel: "<< curr_fuel << " resistance: " << resistance<< " cargo: "<<cargo
        << " Moving to " << target_name << " on course "<< to_degrees(rad_angle)<<" deg , speed "<<curr_speed<< " nm/hr"<<
           mission_desc <<endl;
}

void Freighter::load_at(shared_ptr<Port>& p) {
    int i = is_exists(p->get_name()); //checks if the port exists
    if(i == -1){missions.emplace_back(weak_ptr<Port>(p),1);} //if mission doesnt exists add a new one
    else {missions[i].second = 1;} // if its exists update to load till max (1)
}

void Freighter::unload_at(shared_ptr<Port>& p,int amount) {
    int i = is_exists(p->get_name());//checks if the port exists
    if(i == -1){missions.emplace_back(weak_ptr<Port>(p),-amount);} //if mission doesnt exists add a new one
    else {missions[i].second = missions[i].second > 0 ? 1 : missions[i].second-amount;}
    //if its exists update to unload, if threre is load mission, keep it as we need to end with max cargo else add the amount we need to unload
}

//check if the mission exsist
int Freighter::is_exists(const string& port_name) const{
    for (size_t i =0; i<missions.size(); i++) {
        const auto mp = missions[i].first.lock(); if (!mp) continue;
        if (port_name == mp->get_name()) { return i;}
    }
    return -1;
}

