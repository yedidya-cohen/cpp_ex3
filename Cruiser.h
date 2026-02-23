#ifndef EX3_CRUISER_H
#define EX3_CRUISER_H

#include "Ship.h"

class CivilianShip;


class Cruiser: public Ship{
public:
    Cruiser(Data& d,double range,int force);
    ~Cruiser() = default;
    Cruiser(const Cruiser& other) = default;
    Cruiser& operator=(const Cruiser& other) = default;


    void update() override;
    void describe() const override;

    void attack(std::weak_ptr<CivilianShip> s);
    double get_force() const;

private:
    double range;
    int force;
    std::string need_to_attack;
};


#endif //EX3_CRUISER_H
