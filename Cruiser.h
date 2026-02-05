#ifndef EX3_CRUISER_H
#define EX3_CRUISER_H


#include "CivilianShip.h"


class Cruiser: public Ship{
public:
    Cruiser(const Data& d,double range,double force);
    ~Cruiser() override = default;
    Cruiser(const Cruiser& other) = default;
    Cruiser& operator=(const Cruiser& other) = default;


    void update();
    void describe() const;

    void attack(const CivilianShip& s);
    double get_force() const;

private:
    double range;
    double force;
    string need_to_attack;
};


#endif //EX3_CRUISER_H
