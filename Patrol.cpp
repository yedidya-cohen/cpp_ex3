#include "Patrol.h"
#include "Model.h"
#include "Port.h"
#include <assert.h>
#include <memory>
#include <cmath>

using namespace std;

Patrol::Patrol(Data& d,double fuel, double max_fuel, double consumption, double resistance)
        : CivilianShip(d, fuel, max_fuel, consumption, resistance),
          patrolState(NONE),
          first_port(){
}
//what to print
void Patrol::describe() const {
    auto t = next_port.lock();
    auto d = docked_port.lock();
    const string target_name = t ? t->get_name() : (d ? d->get_name() : "None");
    std::cout << "Patrol " << name << " at "  << position  <<" fuel: "<< curr_fuel << " resistance: " << resistance
    << " Moving to " << target_name << " on course "<< to_degrees(rad_angle)<<" deg , speed "<<curr_speed<< " nm/hr"<<endl;
}
//main function - each tick happen
void Patrol::update() {
    switch (state) {
        case DEAD: //do nothing
            return;
        case MOVING:
            CivilianShip::update();// 1 hour pass - we move and check if we arrive
            if (state == DOCKED) { //if we arrive
                patrolState = REFUEL; //now wait to refuel
                auto ptr_port = docked_port.lock();
                visited.push_back(ptr_port->get_name()); //we tell we been here
            }
            break;
        case DOCKED:
            //my inner state - 3 steps, to track this
            my_3_steps();
            break;
        case  W_REFUELING: //wait for refuel from port - come on refuel me

            if (refuel_completed) {//we got fuel last tick (not now - because port update after ship - we see it after)
                state = DOCKED; //go back to dock and continue with your travel - goodluck ith the sailor going around
                refuel_completed = false; //inizilaize for next
                patrolState = DOCK; //inner state
            }
            break;
        case STOPPED: //only when we attack or at start - we waste a tick and continue to move
            state = MOVING;
            if (next_port.expired()) {next_step();} //there is no next_port - no one put to us something - continue to the nearest one
            break;
        default:
            cerr << "Patrol::update reached invalid ShipState";
            break;
    }
}

void Patrol::next_step() {
    //all ports
    std::vector<std::weak_ptr<Port>> all_ports_weak = Model::get_instance().get_ports();

    //  variables to track the best option found so far
    double min_dist = 1e9;                   // big
    std::shared_ptr<Port> best_candidate = nullptr; // starts empty

    // all ports in the system
    for (auto& wp : all_ports_weak) {
        std::shared_ptr<Port> sp = wp.lock();
        if (!sp) continue; // Skip if the port no longer exists safety

        std::string p_name = sp->get_name();

        // is this port in my visited
        bool is_visited = false;
        for (const auto& v_name : visited) {
            if (p_name == v_name) {
                is_visited = true;
                break;
            }
        }
        if (is_visited) continue; // skip -we been there

        // is this the port I am at?
        // distance is 0, so we must skip it, or we never leave
        if (sp->get_position() == this->get_position()) continue;

        //Calculate Distance
        double d = dist(this->get_position(), sp->get_position());

        if (d<min_dist) {
            // Found a closer port
            min_dist = d;
            best_candidate = sp;
        }
        else if (fabs(d-min_dist) < 1e-6) { //same distance - double so basically the same
            // distance is equal, check lex order
            if (best_candidate == nullptr || p_name < best_candidate->get_name()) {
                best_candidate = sp;
            }
        }
    }

    // decide where to go
    if (best_candidate != nullptr) {
        if (first_port.empty()) {first_port = best_candidate->get_name();}
        set_destination(best_candidate,curr_speed);
        next_port = best_candidate;
    }
    else {
        // No unvisited ports left
        // check if we are already back at the start
        auto start_port_sp = Model::get_instance().get_port_by_name(first_port);

        if (this->get_position() == start_port_sp->get_position()) {
            // mission complete
            // Turn off auto-pilot
            state = DEAD; //show like this trip over
        } else {
            // finished, but we must return to base
            set_destination(start_port_sp, curr_speed);
            next_port = start_port_sp;
        }
    }
}

void Patrol::my_3_steps() {
    //enum PatrolState {W_REFUEL=0, REFUEL=1,DOCK=2,DEST=3,NONE=4};
    switch (patrolState) {
        //first tick - refuel
        case REFUEL:
            refuel();
            patrolState = DOCK; //move to dock
            break;
        case PatrolState::DOCK: //waste tick when thw sailor are parting
            patrolState = DEST;
            break;
        case DEST: //decide where to go
            state = MOVING;
            if (next_port.expired()) {next_step();} //if someone put next port we go to where he told us
            patrolState = NONE;
            break;
        default:
            assert("something very bad happend here");
            break;
    }
}
