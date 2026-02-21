#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

#include "Model.h"
#include "Port.h"

using namespace std;

int main() {
    Model& m = Model::get_instance();

    // 1) Singleton sanity check.
    Model& m2 = Model::get_instance();
    assert(&m == &m2);

    // 2) Create ports and validate lookup/duplicate behavior.
    assert(m.create_port("Haifa_T", Point(10, 10), 100, 1000));
    assert(m.create_port("Ashdod_T", Point(30, 10), 50, 500));
    assert(!m.create_port("Haifa_T", Point(10, 10), 100, 1000)); // duplicate name must fail

    auto haifa = m.get_port_by_name("Haifa_T");
    auto ashdod = m.get_port_by_name("Ashdod_T");
    assert(haifa);
    assert(ashdod);
    assert(m.get_ports().size() >= 2);

    // 3) Create ships and validate lookup/duplicate behavior.
    Data f_data{"Freighter_T", 0.0, 0.0, 40.0, Point(0, 0), ShipState::STOPPED};
    Data p_data{"Patrol_T", 0.0, 0.0, 15.0, Point(5, 5), ShipState::STOPPED};
    Data c_data{"Cruiser_T", 0.0, 0.0, 75.0, Point(40, 40), ShipState::STOPPED};

    assert(m.create_freighter_ship(f_data, 300.0, 500.0, 10.0, 8.0, 100, 0));
    assert(!m.create_freighter_ship(f_data, 300.0, 500.0, 10.0, 8.0, 100, 0)); // duplicate name
    assert(m.create_patrol_ship(p_data, 700.0, 900.0, 10.0, 10.0));
    assert(m.create_pirate_ship(c_data, 100.0, 20.0));

    auto freighter = m.get_ship_by_name("Freighter_T");
    auto patrol = m.get_ship_by_name("Patrol_T");
    auto cruiser = m.get_pirate_ship_by_name("Cruiser_T");
    assert(freighter);
    assert(patrol);
    assert(cruiser);
    assert(m.get_ships().size() >= 2);
    assert(m.get_pirates().size() >= 1);

    // 4) position command: should set MOVING and advance after update.
    string freighter_name = "Freighter_T";
    Point p1(0, 20);
    m.position(freighter_name, p1, 10.0);
    assert(freighter->get_state() == ShipState::MOVING);
    Point before_move = freighter->get_position();
    m.update();
    Point after_move = freighter->get_position();
    assert(dist(before_move, after_move) > 0.0);

    // 5) course command: while moving, course update should influence next movement direction.
    m.course(freighter_name, 90.0, 10.0); // 90 = east by spec convention
    Point before_course = freighter->get_position();
    m.update();
    Point after_course = freighter->get_position();
    assert(after_course.x > before_course.x);

    // 6) destination command: target a named port and verify distance decreases after update.
    string haifa_name = "Haifa_T";
    Point freighter_pre_dest = freighter->get_position();
    double d_before = dist(freighter_pre_dest, haifa->get_position());
    m.destination(freighter_name, haifa_name, 10.0);
    m.update();
    double d_after = dist(freighter->get_position(), haifa->get_position());
    assert(d_after <= d_before);

    // 7) dock_at command: place ship at port and dock explicitly.
    Point same_as_haifa = haifa->get_position();
    m.position(freighter_name, same_as_haifa, 0.0); // move command to exact location
    m.dock_at(freighter_name, haifa_name);
    assert(freighter->get_state() == ShipState::DOCKED);

    // 8) refuel command + update: should move through W_REFUELING back to DOCKED after port service.
    m.refuel(freighter_name);
    assert(freighter->get_state() == ShipState::W_REFUELING);
    m.update(); // port serves queue at end of tick
    assert(freighter->get_state() == ShipState::DOCKED);

    // 9) load/unload commands: currently no direct public cargo getter,
    // so we assert command path is callable and update does not crash.
    m.load_at(freighter_name, haifa_name);
    m.unload_at(freighter_name, haifa_name, 10);
    m.update();

    // 10) stop command: stop and ensure no movement on following update.
    m.stop(freighter_name);
    assert(freighter->get_state() == ShipState::STOPPED);
    Point before_stop_update = freighter->get_position();
    m.update();
    Point after_stop_update = freighter->get_position();
    assert(dist(before_stop_update, after_stop_update) < 1e-9);

    // 11) attacking() direct API: should return true with overwhelming force and stop target.
    m.position(freighter_name, p1, 5.0); // put target back into movement state
    assert(freighter->get_state() == ShipState::MOVING);
    assert(m.attacking("Freighter_T", 1000));
    assert(freighter->get_state() == ShipState::STOPPED);

    // 12) attack command (cruiser queued attack) + update.
    string cruiser_name = "Cruiser_T";
    m.position(freighter_name, p1, 5.0);
    assert(freighter->get_state() == ShipState::MOVING);
    m.attack(cruiser_name, freighter_name);
    m.update(); // cruiser executes queued attack in update()
    assert(freighter->get_state() == ShipState::STOPPED);

    // 13) describe() smoke test for all entities.
    m.describe();

    cout << "All Model.h command checks passed." << endl;
    return 0;
}
