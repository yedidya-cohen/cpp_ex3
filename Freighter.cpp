#include "Freighter.h"
#include <assert.h>
#include "Port.h"

using namespace std;


Freighter::Freighter(Data& d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo)
:CivilianShip(d,fuel,max_fuel,consumption,resistance),
max_capacity(max_capacity),cargo(cargo){}


void Freighter::update(){
    switch (state) {
        case DEAD:
            return;
        case STOPPED: //only when attack/start
            state = MOVING;
            return;
        case ShipState::DOCKED:
            update_cargo();
            break;
        case ShipState::MOVING:
            CivilianShip::update();
            break;
        case W_REFUELING:
            break;
        default:
            cerr<< "Freighter::update reached invalid state";
            break;

    }
    // set dest - nextport,pos - setpos - position
}

void Freighter::update_cargo() {
    auto cp = docked_port.lock(); //
    if (!cp) return;
    int i = is_exists(cp->get_name());
    if(i == -1) {
        if (pending_moving) {pending_moving = false; state = MOVING;}
        return;
    }
    int mis = missions[i].second;
    if (mis > 0) {cargo = max_capacity;}
    else {
        if (cargo + mis >= 0) { //mis is negative
            cargo += mis;
        }else {
            cargo = 0;
            cerr<<"try to unload more than exsist - WARNING"<<endl;
        }
    }
    missions.erase(missions.begin() + i);
}

void Freighter::describe() const {
    const auto cp = next_port.lock();
    const string target_name = cp ? cp->get_name() : "None";
    string mission_desc = "";
    int idx = is_exists(target_name);
    if (idx != -1) {
        int m = missions[idx].second;
        mission_desc = m > 0 ? " loading at " + target_name : " unloading at " + target_name;
    }
    std::cout << "Freighter " << name << " at "  << position  << " status "<< state <<" fuel: "<< curr_fuel << " resistance: " << resistance<< " cargo: "<<cargo
        << " Moving to " << target_name << " on course "<< to_degrees(rad_angle)<<" deg , speed "<<curr_speed<< " nm/hr"<<
           mission_desc <<endl;
    //
}

void Freighter::load_at(shared_ptr<Port>& p) {
    int i = is_exists(p->get_name());
    if(i == -1){missions.emplace_back(weak_ptr<Port>(p),1);}
    else {missions[i].second = 1;}
}

void Freighter::unload_at(shared_ptr<Port>& p,int amount) {
    int i = is_exists(p->get_name());
    if(i == -1){missions.emplace_back(weak_ptr<Port>(p),-amount);}
    else {missions[i].second = missions[i].second > 0 ? 1 : missions[i].second-amount;}
}

int Freighter::is_exists(const string& port_name) const{
    for (int i =0; i<missions.size(); i++) {
        const auto mp = missions[i].first.lock(); if (!mp) continue;
        if (port_name == mp->get_name()) { return i;}
    }
    return -1;
}

