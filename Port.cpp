#include "Port.h"
#include "CivilianShip.h"


void Port::update() {
    fuel += fuel_production;

    if (ship_q.empty()) { return;}

    shared_ptr<CivilianShip> ship = ship_q.front();
    ship_q.pop();
    //check that valid
    if (!ship) {  return;}

    double needed = ship->missing_fuel();
    double supplied = fuel > needed ? needed : fuel;

    ship->add_fuel(supplied);
    fuel -= supplied;

    ship->for_port();
}

void Port::add_to_queue(const shared_ptr<CivilianShip>& s) {
    ship_q.push(s);
}
