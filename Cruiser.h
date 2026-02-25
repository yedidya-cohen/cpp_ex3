#ifndef EX3_CRUISER_H
#define EX3_CRUISER_H

#include "Ship.h"
#include <memory>

class CivilianShip;


class Cruiser: public Ship{
public:
    Cruiser(Data& d,double range,int force);

    void update() override;
    void describe() const override;

    void attack(std::weak_ptr<CivilianShip> s); //attacking ship
    double get_force() const;

private:
    double range; // firing range
    int force; // how strong we are
    std::string need_to_attack; // ship we are goona try to attack
};


#endif //EX3_CRUISER_H
