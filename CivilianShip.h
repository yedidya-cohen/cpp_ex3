#ifndef EX3_CIVILIANSHIP_H
#define EX3_CIVILIANSHIP_H

#include "Port.h"
# include "Ship.h"

class CivilianShip : public Ship
{
public:
    explicit CivilianShip(Data& d,double fuel, double max_fuel, double consumption, int resistance);
    ~CivilianShip() override = 0; //abstract


    bool dock_at(std::shared_ptr<Port>& p); // dock_at cmd
    void update() override; // update 1hr time

    double missing_fuel() const; // amount of fuel we can refuel
    void add_fuel(double f); // refueling the ship
    void refuel(); // add to queue of port for refuel if we docked there

    void been_attacked(bool win_lose); //if we got attacked when true means we won

    void describe() const override = 0; //details of the ship

    double get_resistance() const; // returns resistance

    std::shared_ptr<Port> get_docked_port() const; // returns current port

    void set_destination(std::weak_ptr<Port> p, double speed); //set next mission of destination


protected:
    double curr_fuel, max_fuel, consumption;; // current amount of fuel, max amount of fuel we can hold, how much we use per hour
    int resistance;  // how strong our ship against attackes
    bool refuel_completed;
    std::weak_ptr<Port> next_port, docked_port; // next mission , if we are docked right now we hold the port

    static bool is_on_segment(Point start, Point end, Point port); // checks if we passed the port on the way
};


#endif
