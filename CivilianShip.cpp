#include "CivilianShip.h"
#include "Model.h"
#include "Port.h"

CivilianShip::CivilianShip(Data& d, double fuel, double max_fuel, double consumption, double resistance)
    : Ship(d),
      curr_fuel(fuel),
      resistance(resistance),
      max_fuel(max_fuel),
      consumption(consumption),
      next_port(),docked_port() {}


bool CivilianShip::dock_at(shared_ptr<Port> p) { //check who is calling than change base on if its weak/shared
    if (!p) {
        return false;
    }
    if (dist(position,p->get_position()) <= 0.1) {
        position = p->get_position();
        state = DOCKED;
        next_port = p;
        curr_speed = 0;
        return true;
    }
    return false;
}

void CivilianShip::update(){
    curr_fuel -= consumption;
    if (curr_fuel <= 0) {
        state = DEAD;
        return;
    }
    Point p_start = position;
    Ship::update(); //notice we did update!
    Point p_end = position;
    auto port = next_port.lock();
    if (!port) {return;}
    Point p_port = port->get_position();
    bool is_withX = (p_port.x >= std::min(p_start.x, p_end.x)) && (p_port.x <= std::max(p_start.x, p_end.x));
    bool is_WithY = (p_port.y >= std::min(p_start.y, p_end.y)) && (p_port.y <= std::max(p_start.y, p_end.y));
    if (is_withX && is_WithY) {
        position = p_port;
        state = DOCKED;
        docked_port = next_port;
        next_port.reset();
    }
}

double CivilianShip::missing_fuel() const {
    return max_fuel - curr_fuel;
}

void CivilianShip::add_fuel(double f) {
    curr_fuel = f + curr_fuel < max_fuel ? curr_fuel + f : max_fuel;
    if (state == W_REFUELING) {
        state = DOCKED;
    }
}

void CivilianShip::refuel() {
    if (state == DOCKED) {
        if (auto p = docked_port.lock()) {
            Model::get_instance().add_to_refueling(name, p);
            state = W_REFUELING;
        }
    }
}



void CivilianShip::been_attacked(bool win_lose) {
    state = ShipState::STOPPED;
    win_lose ? resistance++ : resistance--;
}

double CivilianShip::get_resistance() const {
    return resistance;
}

void CivilianShip::load_at(shared_ptr<Port> &p) {

}

void CivilianShip::unload_at(shared_ptr<Port> &p, int amount) {

}

void CivilianShip::set_destination(weak_ptr<Port> p, double speed) {

    auto sp = p.lock();
    if (!sp) return;
    Point p_dest = sp->get_position();
    Ship::set_pos(p_dest,speed);
    next_port = p;
}