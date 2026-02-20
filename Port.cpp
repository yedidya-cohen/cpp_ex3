#include "Port.h"
#include "CivilianShip.h"


void Port::update() {
    fuel += fuel_production;

    if (ship_q.empty()) { return;}

    auto ws = ship_q.front();
    ship_q.pop();
    //check that valid
    auto ship = ws.lock();
    if (!ship) {return;} //actually should not happend but maybe a while than we always serve someone?


    double needed = ship->missing_fuel();
    double supplied = (fuel > needed) ? needed : fuel;

    ship->add_fuel(supplied);
    fuel -= supplied;

    ship->for_port();
}

void Port::add_to_queue(const shared_ptr<CivilianShip>& s) {
    ship_q.push(s);
}

void Port::describe() const {
    std::cout << "Port " << name << " at "  << pos  << " fuel: "<< fuel << endl;
}
