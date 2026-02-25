#include "CivilianShip.h"
#include "Model.h"
#include "Port.h"

using namespace std;

CivilianShip::~CivilianShip() = default;

CivilianShip::CivilianShip(Data& d, double fuel, double max_fuel, double consumption, int resistance)
    : Ship(d),
      curr_fuel(fuel),
      max_fuel(max_fuel),
      consumption(consumption),
      resistance(resistance),
      refuel_completed(false),
      next_port(),docked_port() {}


bool CivilianShip::dock_at(shared_ptr<Port>& p) { //check who is calling than change base on if its weak/shared
    if (!p) {return false;} // if port is nullptr
    if (dist(position,p->get_position()) <= 0.1) { //checks if within distance
        position = p->get_position();
        state = DOCKED;
        next_port = p;
        docked_port = p;
        curr_speed = 0;
        return true;
    }
    return false; //if we cannot docked we return false
}

void CivilianShip::update(){ //generic update for all civilianships
    curr_fuel -= consumption;
    if (curr_fuel <= 0) { //checks for sufficient fuel
        state = DEAD;
        return;
    }
    // saving start and end point to check if we passed the port
    Point p_start = position;
    Ship::update();
    Point p_end = position;
    auto port = next_port.lock();
    if (!port) {return;}
    Point p_port = port->get_position();
    if (is_on_segment(p_start, p_end, p_port)) { //if the port is on the way we dock there
        position = p_port;
        state = DOCKED;
        docked_port = next_port;
        next_port.reset();
    }
}

double CivilianShip::missing_fuel() const { return max_fuel - curr_fuel; } //returns the amount of fuel we can refuel

void CivilianShip::add_fuel(double f) { //adding fuel (checks for not more then the max)
    curr_fuel = f + curr_fuel < max_fuel ? curr_fuel + f : max_fuel;
    if (state == W_REFUELING) {refuel_completed = true;}
}

void CivilianShip::refuel() { // if we are docked we can refuel at that port, so we join the queue
    if (state == DOCKED) {
        if (auto p = docked_port.lock()) {
            p->add_to_queue(dynamic_pointer_cast<CivilianShip>(Model::get_instance().get_ship_by_name(name)));
            state = W_REFUELING;
            refuel_completed = false;
        }
    }
}


void CivilianShip::been_attacked(bool win_lose) { //gets if we lost the battle and update the resistance
    state = ShipState::STOPPED;
    win_lose ? resistance++ : resistance--;
}

double CivilianShip::get_resistance() const {return resistance;}

std::shared_ptr<Port> CivilianShip::get_docked_port() const {  return docked_port.lock();}


void CivilianShip::set_destination(weak_ptr<Port> p, double speed) {
    auto sp = p.lock();
    if (!sp) return; //checks if the port exists
    Point p_dest = sp->get_position(); //setting dest
    Ship::set_pos(p_dest,speed); // setting angle and speed
     next_port = p; //setting the target
}

// Returns true if port lies on the straight line segment from start to end
// used to detect cases where the ship moves past a port in one step without landing exactly on it
bool CivilianShip::is_on_segment(Point start, Point end, Point port) {
    // checks that port is within the bounding box of the segment

    bool in_box_x = port.x >= std::min(start.x, end.x) && port.x <= std::max(start.x, end.x);
    bool in_box_y = port.y >= std::min(start.y, end.y) && port.y <= std::max(start.y, end.y);
    if (!in_box_x || !in_box_y) return false;

    //checks steep using cross product =0
    double cross_product = (port.y - start.y) * (end.x - start.x) - (port.x - start.x) * (end.y - start.y);
    return std::abs(cross_product) < 0.1;
}
