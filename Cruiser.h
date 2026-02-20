#ifndef EX3_CRUISER_H
#define EX3_CRUISER_H

#include "Ship.h"

class CivilianShip;


class Cruiser: public Ship{
public:
    Cruiser(Data& d,double range,double force);
    ~Cruiser() = default;
    Cruiser(const Cruiser& other) = default;
    Cruiser& operator=(const Cruiser& other) = default;


    void update() override;
    void describe() const override;

    void attack(const CivilianShip& s);
    double get_force() const;

private:
    double range;
    double force;
    string need_to_attack;
};


#endif //EX3_CRUISER_H
