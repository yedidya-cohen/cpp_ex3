//
// Created by yedid on 18/01/2026.
//

#ifndef EX3_PATROL_H
#define EX3_PATROL_H

#include <vector>
#include "CivilianShip.h"
#include <queue>


class Patrol : public CivilianShip{
public:
    Patrol(Data& d,double fuel, double max_fuel, double consumption, double resistance);
    Patrol(const Patrol& other) = default; //delete
    Patrol& operator=(const Patrol& other) = default; //delete

    void update() override;
    void describe() const override;

    void refueling(double amount);

    //data structure

private:
    void next_step();
    void my_3_steps();
    struct where_to {
        int curr;
        int start;
        int len;
        bool r_l; // true = right, false = left
        std::vector<bool> visited;  // Track visited ports by index
    };
    vector<string> visited;
    enum PatrolState {W_REFUEL=0, REFUEL=1,DOCK=2,DEST=3,NONE=4};
    PatrolState patrolState;
    where_to w_g;
    queue<pair<weak_ptr<Port>,double>> next;
    weak_ptr<Port> current_target;
    string first_port;
};

#endif //EX3_PATROL_H
