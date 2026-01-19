//
// Created by yedid on 18/01/2026.
//

#ifndef EX3_PATROL_H
#define EX3_PATROL_H

#include <vector>
#include "CivilianShip.h"

class Patrol : public CivilianShip{
public:
    Patrol(Data d,vector<weak_ptr<Port>> ports);
    void update() override;
    void describe() const override;
    void stop() override;

private:
    struct where_to{
        int curr;
        int start;
        bool r_l;
    };
    enum PatrolState{REFUEL=0,DOCK=1,DEST=2,NONE=3};
    PatrolState patrolState;
    where_to w_g;
};

#endif //EX3_PATROL_H
