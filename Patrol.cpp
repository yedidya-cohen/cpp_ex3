
#include "Patrol.h"

#include <assert.h>

Patrol::Patrol(Data& d,double fuel, double max_fuel, double consumption, double resistance)
        : CivilianShip(d, fuel, max_fuel, consumption, resistance),
          patrolState(NONE),
          current_target(nullptr),
          first_port(""){
    w_g.curr = 0;
    w_g.start = 0;
    w_g.len = 0;
    w_g.r_l = true;
}

void Patrol::describe() const {
    std::cout << "Patrol " << name << " at"  << position  << " fuel: "<< curr_fuel << " resistance: " << resistance
    << " Moving to " << current_target->get_name() << "on course "<< to_degrees(rad_angle)<<"deg , speed "<<curr_speed<< " nm/hr"<<endl;
}

void Patrol::update() {
    switch (state) {
        case DEAD:
            return;
        case MOVING:
            CivilianShip::update();// 1 hour pass
            if (dock_at(current_target)){
                patrolState = W_REFUEL;
                current_target = nullptr;
            }
        case DOCKED:
            //my inner state - 3 steps
            my_3_steps();
            break;
        case STOPPED:
            next_step();
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
        if (sp->get_position() == this->get_position()) continue;

        // CHECK C: Calculate Distance
        double d = dist(this->get_position(), sp->get_position());

        // CHECK D: Compare to find the best candidate
        if (d < min_dist) {
            // Found a strictly closer port
            min_dist = d;
            best_candidate = sp;
        }
        else if (d == min_dist) {
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
        if (first_port == "") {first_port = best_candidate->get_name();}
        set_destination(*best_candidate,curr_speed);
        current_target = best_candidate;
    }
    else {
        // Scenario B: No unvisited ports left (Vector empty or all visited)
        // Check if we are already back at the start
        auto start_port_sp = Model::get_instance().get_port_by_name(first_port);

        if (this->get_position() == start_port_sp->get_position()) {
            // Mission Complete
            //is_patrolling = false; // Turn off auto-pilot
            stop(); // Optional: ensure ship is stopped
            //state = DEAD;
        } else {
            // Loop finished, but we must return to base
            set_destination(*start_port_sp, curr_speed);
            current_target = start_port_sp;
        }
    }
}

void Patrol::my_3_steps() {
    //enum PatrolState {W_REFUEL=0, REFUEL=1,DOCK=2,DEST=3,NONE=4};
    switch (patrolState) {
        case W_REFUEL:
            refuel();
            patrolState = REFUEL;
            break;
        case REFUEL: //the port incharge
            break;
        case DOCK:
            patrolState = DEST;
            break;
        case DEST:
            state = MOVING;
            if (current_target == nullptr) {next_step();}
            patrolState = NONE;
            break;
        default:
            assert("something very bad happend here");
            break;
    }
}

void Patrol::refueling(double amount) {
    if (curr_fuel + amount <= max_fuel) {max_fuel = curr_fuel + amount;}
    patrolState = DOCK;
}


//
// void Patrol::stop() {
//     // Clear the queue
//     next = std::queue<std::pair<std::shared_ptr<Port>, double>>();
//
//     // Reset state
//     curr_speed = 0.0;
//     state = ShipState::STOPPED;
//     patrolState = NONE;
//     // todo: current_target = nullptr;
//
//     std::cout << name << " stopped\n";
// }
//
//
// void Patrol::update_after_dock() {
//     // Move to next index in circular pattern
//     if (w_g.r_l) {
//         w_g.curr = (w_g.curr + 1) % w_g.len;
//     } else {
//         w_g.curr = (w_g.curr - 1 + w_g.len) % w_g.len;
//     }
//
//     // Check if completed route
//     if (w_g.curr == w_g.start) {
//         std::cout << name << " completed patrol route\n";
//         patrolState = NONE;
//         state = ShipState::DOCKED;
//         return;
//     }
// }
//
// void Patrol::set_destination(std::weak_ptr<Port> port, double speed) {
//         auto port_ptr = port.lock();
//         if (!port_ptr) {
//             throw std::runtime_error("Invalid port");
//         }
//
//         if (speed <= 0.0 || speed > max_speed_) {
//             throw std::runtime_error("Invalid speed");
//         }
//
//         patrol_speed = speed;
//
//         // Initialize where_to if first destination
//         if (next.empty() && w_g.len == 0) {
//             initialize_where_to();
//         }
//
//         // Get the index of this port in Model
//         Model& model = Model::getInstance();
//         int port_index = model.getPortIndex(port_ptr->getName());
//
//         if (port_index >= 0) {
//             // Mark this port index in where_to
//             w_g.visited[port_index] = true;
//
//             // Set start index if this is the first port
//             if (next.empty() && !current_target) {
//                 w_g.start = port_index;
//                 w_g.curr = port_index;
//             }
//         }
//
// void Patrol::update() {
//     //continue to route
//     //if we got no port - 3 stages PatrolState - try to refuel, dock and update next move
//     //next move is if queue empty to the next index - if not to destination
//     //model will have a method where i will send the next index station and will get const port&
//
//     //decrese fuel acoording to civilianShip method
// }
//
// void Patrol::describe() const {
//     //in this kind of format:
//     // Patrol_boat Shikishima at (9.95, 1.00), fuel: 880.00 kl, resistance: 10, Moving to Nagoya on course 84.29 deg, speed 10.00 nm/hr
//     cout << "hello";
// }

/*

void Patrol::next_step() {
    auto all_ports = Model::get_instance().get_ports();
    double min_dist = 1e9; // Start with a very large number
    std::shared_ptr<Port> best_candidate = nullptr;

    int index = -1;

    for(int i=0; i<all_ports.size(); i++) {
        // Lock the weak_ptr to get shared_ptr
        auto port_ptr = all_ports[i].lock();
        if (!port_ptr) continue;  // Skip if port was destroyed

        index = i;

        for (auto& s: visited)
            if (port_ptr->get_name() == s) {index = -1; break;}

        if(index != -1) {
            if (dist(port_ptr->get_position(), position ) < min_dist) {//Tie breaker - according to lex
                min_dist = dist(port_ptr->get_position(), position );
                best_candidate = port_ptr;
            }
        }
    }
    if (best_candidate) {current_target = best_candidate;}
    //finished - go back to first and annouce <--
    //setDestiniation(port,curr_speed)
}


 */