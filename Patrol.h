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
    Patrol(const Patrol& other) = default;
    Patrol& operator=(const Patrol& other) = default;

    // void update() override;
    // void describe() const override;

    //data structure

private:
    struct where_to {
        int curr;
        int start;
        int len;
        bool r_l; // true = right, false = left
        std::vector<bool> visited;  // Track visited ports by index
    };
    enum PatrolState {REFUEL=0,DOCK=1,DEST=2,NONE=3};
    PatrolState patrolState;
    where_to w_g;
    queue<pair<shared_ptr<Port>,double>> next;
    std::shared_ptr<Port> current_target;
};

#endif //EX3_PATROL_H
