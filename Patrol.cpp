
#include "Patrol.h"

Patrol::Patrol(Data& d,double fuel, double max_fuel, double consumption, double resistance)
        : CivilianShip(d, fuel, max_fuel, consumption, resistance),
          patrolState(NONE),
          current_target(nullptr) {
    w_g.curr = 0;
    w_g.start = 0;
    w_g.len = 0;
    w_g.r_l = true;
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