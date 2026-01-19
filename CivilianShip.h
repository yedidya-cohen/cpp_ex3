#ifndef EX3_CIVILIANSHIP_H
#define EX3_CIVILIANSHIP_H

#include "Ship.h"

class CivilianShip : public Ship
{
public:
    ~CivilianShip() override = default; //abstract

    explicit CivilianShip(Data d, double resistance): Ship(d), resistance(resistance) {}

    double get_resistance() const {return resistance;};
    virtual void attacked(bool win_lose) = 0;
    virtual void set_destination(weak_ptr<Port> dest, double speed) = 0;
private:
    double resistance;
};

#endif