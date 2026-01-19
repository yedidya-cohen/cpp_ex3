//
// Created by yedid on 18/01/2026.
//

#ifndef EX3_PATROL_H
#define EX3_PATROL_H

#include <vector>
#include "CivilianShip.h"

class Patrol : public CivilianShip{
public:

    Patrol(Data d,vector<weak_ptr<Port>> ports,double resistance);
    void update() override;
    void describe() const override;
    void set_destination(weak_ptr<Port> dest, double speed) override;
    void set_course(double speed, double angle) override;
    void wait_at_dock();//3 time steps -
    void attacked(bool win_lose) override;
    double get_force() const override;

private:
    struct where_to{
        int curr;
        int start;
        bool r_l;
    };
//    static constexpr double maxCapacity = 900.0; //900,000 wtf?
//    static constexpr double maxVelocity = 15.0;
//    static constexpr double fuel_per_nm = 2.0;
    static vector<weak_ptr<Port>> ports;
    where_to w_g;
};


#endif //EX3_PATROL_H
