#include "CivilianShip.h"
#include "Model.h"
#include "Port.h"

CivilianShip::CivilianShip(Data& d, double fuel, double max_fuel, double consumption, double resistance)
    : Ship(d),
      curr_fuel(fuel),
      resistance(resistance),
      max_fuel(max_fuel),
      consumption(consumption),
      curr_port(Model::get_instance().defualt_port()) {}

bool CivilianShip::dock_at(shared_ptr<Port> p) {
    if (!p) {
        return false;
    }
    if (position == p->get_position()) {
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
        Model::get_instance().add_to_refueling(name, curr_port);
        state = W_REFUELING;
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
