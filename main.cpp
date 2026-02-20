#include <iostream>
#include "Model.h"
#include "Port.h"
#include "View.h"

using namespace std;

int main() {
    Model& m = Model::get_instance();

    // Create a port
    // Note: Model stores a copy, but create_freighter needs a reference.
    // We create a local port for the freighter's destination.
    Port haifa("Haifa", Point(10, 10), 100, 1000);
    m.create_port("Haifa", Point(10, 10), 100, 1000);

    // Create Freighter
    Data d_freighter;
    d_freighter.name = "Bertie";
    d_freighter.pos = Point(0, 0);
    d_freighter.max_speed = 20;
    d_freighter.curr_speed = 10;
    d_freighter.angle = 90;
    d_freighter.state = ShipState::MOVING;

    // Data d, double fuel, double max_fuel, double consumption, double resistance, int max_capacity, int cargo, Port& destination
    m.create_freighter_ship(d_freighter, 100, 500, 10, 5, 1000, 0);
    // Create Patrol
    Data d_patrol;
    d_patrol.name = "Police";
    d_patrol.pos = Point(5, 5);
    d_patrol.max_speed = 30;
    d_patrol.curr_speed = 10;
    d_patrol.angle = 0;
    d_patrol.state = ShipState::MOVING;

    // Data& d, double fuel, double max_fuel, double consumption, double resistance
    m.create_patrol_ship(d_patrol, 100, 200, 10, 5);

    // Create Pirate
    Data d_pirate;
    d_pirate.name = "Blackbeard";
    d_pirate.pos = Point(20, 20);
    d_pirate.max_speed = 40;
    d_pirate.curr_speed = 10;
    d_pirate.angle = 180;
    d_pirate.state = ShipState::MOVING;

    // Data& d, double range, double force
    m.create_pirate_ship(d_pirate, 50, 100);
    m.describe();
    View v(25,2.0,{-10,-10});
    v.draw();
    m.update();
    v.draw();
    m.describe();

    return 0;
}
