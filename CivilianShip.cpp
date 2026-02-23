#include "CivilianShip.h"
#include "Model.h"
#include "Port.h"

using namespace std;

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
    if (is_on_segment(p_start, p_end, p_port)) {
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
    if (state == W_REFUELING) {state = DOCKED;}
}

void CivilianShip::refuel() {
    if (state == DOCKED) {
        if (auto p = docked_port.lock()) {

            state = W_REFUELING// MODIE;
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

std::shared_ptr<Port> CivilianShip::get_docked_port() const {  return docked_port.lock();}


void CivilianShip::set_destination(weak_ptr<Port> p, double speed) {

    auto sp = p.lock();
    if (!sp) return;
    Point p_dest = sp->get_position();
    Ship::set_pos(p_dest,speed);
    next_port = p;
}

bool CivilianShip::is_on_segment(Point start, Point end, Point port) {

    bool in_box_x = port.x >= std::min(start.x, end.x) && port.x <= std::max(start.x, end.x);
    bool in_box_y = port.y >= std::min(start.y, end.y) && port.y <= std::max(start.y, end.y);
    if (!in_box_x || !in_box_y) return false;

    double cross_product = (port.y - start.y) * (end.x - start.x) - (port.x - start.x) * (end.y - start.y);

    return std::abs(cross_product) < 0.1;
}
