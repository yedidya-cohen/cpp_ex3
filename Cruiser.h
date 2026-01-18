//
// Created by yedid on 18/01/2026.
//

#ifndef EX3_CRUISER_H
#define EX3_CRUISER_H


#include "Ship.h"
#include <memory>

class Cruiser: public Ship{
public:
    Cruiser(Data d,double range,double force);
    ~Cruiser() = default;
    void update() override;
    void describe() const override;
    void set_course(double speed, double angle) override;
    void attack(const weak_ptr<Ship>& s);

private:
    //static constexpr double max_velocity = 75.0;
    double range;
    double force;
//    weak_ptr<Ship> target;


};


#endif //EX3_CRUISER_H
