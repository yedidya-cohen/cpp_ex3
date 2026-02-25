#include "Port.h"
#include "CivilianShip.h"

using namespace std;

void Port::update() {
    fuel += fuel_production; //first we add fuel
    while (!ship_q.empty()) { //check if we can serve anyone
        auto ws = ship_q.front();
        ship_q.pop();
        //check that valid
        auto ship = ws.lock();
        if (!ship) {continue;} //do another one - that why while

        double needed = ship->missing_fuel(); //how much fuel to give
        double supplied = (fuel > needed) ? needed : fuel;

        ship->add_fuel(supplied); //add fuel to this ship (and get out from state refuel)
        fuel -= supplied;
            break; // make sure we only serve one
        }
}
//we add this ship to queue - convert to weakptr
void Port::add_to_queue(const shared_ptr<CivilianShip>& s) {
    ship_q.push(s);
}

void Port::describe() const {
    std::cout << "Port " << name << " at "  << pos  << " fuel: "<< fuel << endl;
}
