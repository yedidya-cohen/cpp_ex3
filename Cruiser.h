//
// Created by yedid on 18/01/2026.
//

#ifndef EX3_CRUISER_H
#define EX3_CRUISER_H



#include "CivilianShip.h"

class Cruiser: public Ship{
public:
    Cruiser(const Data& d,double range,double force);
    ~Cruiser() override = default;
    // void update() override;
    // void describe() const override;
    // void stop() override;
    // void attack(CivilianShip& s);
    // void set_course(double speed, double angle) ;
    // double get_force() const;

private:
    double range;
    double force;
};


#endif //EX3_CRUISER_H
