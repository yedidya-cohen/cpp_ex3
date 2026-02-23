#include "Patrol.h"
#include "Model.h"
#include "Port.h"
#include <assert.h>

using namespace std;

Patrol::Patrol(Data& d,double fuel, double max_fuel, double consumption, double resistance)
        : CivilianShip(d, fuel, max_fuel, consumption, resistance),
          patrolState(NONE),
          first_port(){
    w_g.curr = 0;
    w_g.start = 0;
    w_g.len = 0;
    w_g.r_l = true;
}

void Patrol::describe() const {
    auto t = next_port.lock();
    auto d = docked_port.lock();
    const string target_name = t ? t->get_name() : (d ? d->get_name() : "None");
    std::cout << "Patrol " << name << " at "  << position  << " fuel: "<< curr_fuel << " resistance: " << resistance
    << " Moving to " << target_name << " on course "<< to_degrees(rad_angle)<<" deg , speed "<<curr_speed<< " nm/hr"<<endl;
}

void Patrol::update() {
    switch (state) {
        case DEAD:
            return;
        case MOVING:
            CivilianShip::update();// 1 hour pass
            if (state == DOCKED) {
                patrolState = REFUEL;
                auto ptr_port = docked_port.lock();
                assert(ptr_port != nullptr);//
                visited.push_back(ptr_port->get_name());
            }
            break;
        case DOCKED:
            //my inner state - 3 steps
            my_3_steps();
            break;
        case  W_REFUELING:
            break;
        case STOPPED:
            state = MOVING;
            if (next_port.expired()) {next_step();}
            break;
        default:
            assert(false && "Patrol::update reached invalid ShipState");
            break;
    }
}

void Patrol::next_step() {
    std::vector<std::weak_ptr<Port>> all_ports_weak = Model::get_instance().get_ports();

    // 2. Setup variables to track the best option found so far
    double min_dist = 1e9;                   // Infinity
    std::shared_ptr<Port> best_candidate = nullptr; // Starts empty

    // 3. Loop through all ports in the system
    for (auto& wp : all_ports_weak) {
        // LOCK the weak pointer to verify it exists and get access
        std::shared_ptr<Port> sp = wp.lock();

        if (!sp) continue; // Skip if the port no longer exists (safety check)

        std::string p_name = sp->get_name();

        // CHECK A: Is this port in my 'visited' list?
        bool is_visited = false;
        for (const auto& v_name : visited) {
            if (p_name == v_name) {
                is_visited = true;
                break;
            }
        }
        if (is_visited) continue; // Skip visited ports

        // CHECK B: Is this the port I am CURRENTLY at?
        // (Distance is 0, so we must skip it, otherwise we never leave)
        // if (sp->get_position() == this->get_position()) continue;
        //
        // CHECK C: Calculate Distance
        double d = dist(this->get_position(), sp->get_position());

        // CHECK D: Compare to find the best candidate
        if (d < min_dist) {
            // Found a strictly closer port
            min_dist = d;
            best_candidate = sp;
        }
        else if (fabs(d-min_dist) < 1e-6) {
            // Tie-Breaker: Distance is equal, check Alphabetical Order
            // Assignment Requirement: "choose the first one alphabetically"
            if (best_candidate == nullptr || p_name < best_candidate->get_name()) {
                best_candidate = sp;
            }
        }
    }

    // 4. Action: Decide where to go
    if (best_candidate != nullptr) {
        // Scenario A: Found a valid next target
        // We do NOT add to 'visited' yet (only on arrival), but we set the course.
        // Assuming set_destination takes a shared_ptr and speed
        if (first_port.empty()) {first_port = best_candidate->get_name();}
        set_destination(best_candidate,curr_speed);
        next_port = best_candidate;
    }
    else {
        // Scenario B: No unvisited ports left (Vector empty or all visited)
        // Check if we are already back at the start
        auto start_port_sp = Model::get_instance().get_port_by_name(first_port);

        if (this->get_position() == start_port_sp->get_position()) {
            // Mission Complete
            //is_patrolling = false; // Turn off auto-pilot
            stop();
            state = DEAD;
        } else {
            // Loop finished, but we must return to base
            set_destination(start_port_sp, curr_speed);
            next_port = start_port_sp;
        }
    }
}

void Patrol::my_3_steps() {
    //enum PatrolState {W_REFUEL=0, REFUEL=1,DOCK=2,DEST=3,NONE=4};
    switch (patrolState) {
        case REFUEL:
            refuel();
            patrolState = DOCK;
            break;
        case PatrolState::DOCK:
            patrolState = DEST;
            break;
        case DEST:
            state = MOVING;
            if (next_port.expired()) {next_step();}
            patrolState = NONE;
            break;
        default:
            assert("something very bad happend here");
            break;
    }
}

// (M,N) -> (D,W_F) -> (W_re,D) -> ...->(D,D) ->(D,Dest) -> (M,N)
