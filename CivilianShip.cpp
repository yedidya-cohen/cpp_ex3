#include "CivilianShip.h"
#include "Model.h"
#include "Port.h"

CivilianShip::CivilianShip(Data& d, double fuel, double max_fuel, double consumption, double resistance)
    : Ship(d),
      curr_fuel(fuel),
      resistance(resistance),
      max_fuel(max_fuel),
      consumption(consumption),
      curr_port() {}


bool CivilianShip::dock_at(shared_ptr<Port> p) { //check who is calling than change base on if its weak/shared
    if (!p) {
        return false;
    }
    if (dist(position,p->get_position()) <= 0.1) { //change because dist should be 0.1
        position = p->get_position();
        state = DOCKED;
        curr_port = p;
        curr_speed = 0;
        return true;
    }
    return false;
}

void CivilianShip::update(){
    Ship::update();
    curr_fuel -= consumption;
    if (curr_fuel <= 0) {
        state = DEAD;
    }
}

double CivilianShip::missing_fuel() const {
    return max_fuel - curr_fuel;
}

void CivilianShip::add_fuel(double f) {
    curr_fuel = f + curr_fuel < max_fuel ? curr_fuel + f : max_fuel;
}

void CivilianShip::refuel() {
    if (state == DOCKED) {
        if (auto p = curr_port.lock()) {
            Model::get_instance().add_to_refueling(name, p);
            state = W_REFUELING;
        }
    }
}

void CivilianShip::for_port() {
    if (state == W_REFUELING) {
        state = DOCKED;
    }
}

void CivilianShip::been_attacked(bool win_lose) {
    state = ShipState::STOPPED;
    win_lose ? resistance-- : resistance++;
}

double CivilianShip::get_resistance() const {
    return resistance;
}
