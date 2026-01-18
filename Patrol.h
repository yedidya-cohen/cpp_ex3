//
// Created by yedid on 18/01/2026.
//

#ifndef EX3_PATROL_H
#define EX3_PATROL_H
#include <memory>
#include "Port.h"
#include "Ship.h"
#include <vector>
class Patrol : public Ship{
public:

    Patrol(string name,double consumpsion,double fuel,double current_speed,double angle,Point position,
           vector<shared_ptr<Port>> ports,int resistance);
    void update() override;
    void describe() const override;
    void set_destination() override;
    void set_course() override;
    void wait_for_dock();//3 time steps -
    void atteckd(bool win_lose);

private:
    struct where_to{
        //TODO think about keep the size of array -D
        int curr;
        int start;
        bool r_l;
    };
    static constexpr double maxCapacity = 900.0; //900,000 wtf?
    static constexpr double maxVelocity = 15.0;
    static constexpr double fuel_per_nm = 2000.0;
    int resistance; //TODO resistance is int or double? -D
    std::shared_ptr<Port> ports;//
    std::shared_ptr<where_to> w_g; //dont know why pointer
};


#endif //EX3_PATROL_H
