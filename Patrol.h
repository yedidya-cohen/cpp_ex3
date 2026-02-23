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


private:
    void next_step();
    void my_3_steps();
    std::vector<std::string> visited;
    enum PatrolState {REFUEL=0,DOCK=1,DEST=2,NONE=3};
    PatrolState patrolState;
    std::queue<std::pair<std::weak_ptr<Port>,double>> next;
    std::string first_port;
};

#endif //EX3_PATROL_H
