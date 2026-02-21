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
    enum PatrolState {REFUEL=0,DOCK=1,DEST=2,NONE=3};
    PatrolState patrolState;
    where_to w_g;
    queue<pair<weak_ptr<Port>,double>> next;
    string first_port;
};

#endif //EX3_PATROL_H
