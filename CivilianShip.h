#ifndef EX3_CIVILIANSHIP_H
#define EX3_CIVILIANSHIP_H

#include "Ship.h"

class CivilianShip : public Ship
{
public:
    ~CivilianShip() override = default; //abstract

    explicit CivilianShip(Data d,double fuel, double max_fuel, double consumption, double resistance):
    Ship(d), curr_fuel(fuel), resistance(resistance), max_fuel(max_fuel), consumption(consumption) {}

    double get_resistance() const {return resistance;};
    void attacked(bool win_lose);
    virtual void set_destination(const Port& dest, double speed) = 0;
    virtual void refuel() = 0;
    double fuel_missing() {return  max_fuel - curr_fuel;}

    double get_current_fuel() const { return curr_fuel;}
    double get_max_tank() const {return max_fuel;}
    double get_consumption_rate() {return consumption;}

private:
    double curr_fuel, resistance;
    const double max_fuel, consumption;
};

#endif