//
// Created by yedid on 18/01/2026.
//

#ifndef EX3_CRUISER_H
#define EX3_CRUISER_H


#include "Ship.h"
#include <memory>

class Cruiser: public Ship{
public:

    Cruiser();
    void update() override;
    void describe() const override;
    void set_destination() override;
    void set_course() override;
    void search_for_victims();
    void attack(shared_ptr<Ship> s);

private:
    static constexpr double max_velocity = 75.0;
    double range;
    double force;
    shared_ptr<Ship> target;


};


#endif //EX3_CRUISER_H
