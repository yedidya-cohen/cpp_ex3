#include "Port.h"
#include "CivilianShip.h"

using namespace std;

void Port::update() {
    fuel += fuel_production;

    while (!ship_q.empty()) {

    auto ws = ship_q.front();
    ship_q.pop();
    //check that valid
    auto ship = ws.lock();
    if (!ship) {continue;}

    double needed = ship->missing_fuel();
    double supplied = (fuel > needed) ? needed : fuel;

    ship->add_fuel(supplied);
    fuel -= supplied;
        break; // make sure we only serve one
    }
}

void Port::add_to_queue(const shared_ptr<CivilianShip>& s) {
    ship_q.push(s);
}

void Port::describe() const {
    std::cout << "Port " << name << " at "  << pos  << " fuel: "<< fuel << endl;
}
