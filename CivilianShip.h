#ifndef EX3_CIVILIANSHIP_H
#define EX3_CIVILIANSHIP_H


#include "Ship.h"



class CivilianShip : public Ship
{
public:
    ~CivilianShip() override = default; //abstract
    explicit CivilianShip(Data& d,double fuel, double max_fuel, double consumption, double resistance):
    Ship(d), curr_fuel(fuel), resistance(resistance), max_fuel(max_fuel), consumption(consumption),
        curr_port(Model::get_instance().defualt_port()) {}



    bool dock_at(shared_ptr<Port> p) {
        if (position == p->get_position()) {
            position = p->get_position();
            state = DOCKED;
            curr_port = p;
            curr_speed=0;
            return true;
        }
        return false;
    }
    void virtual update() {
        Ship::update();
        curr_fuel -= consumption;
        if (curr_fuel <= 0) {state = DEAD;}
    }

    void refuel() {
        if (state == DOCKED) {
            curr_port->add_to_queue(*this);
            state = W_REFUELING;
        }
    }

    void for_port() { //for port after refuel
        if (state == W_REFUELING) {
            state = DOCKED;
        }
    }

    void been_attacked(bool win_lose) { //true mean lose
        state = ShipState::STOPPED;
        win_lose ? resistance--:resistance++;
    }

    double get_resistance() const {return resistance;};
    //
    // void attacked(bool win_lose);
    // virtual void set_destination(const Port& dest, double speed) = 0;
    // virtual void refuel() = 0;
    // double fuel_missing() {return  max_fuel - curr_fuel;}
    //
    // double get_current_fuel() const { return curr_fuel;}
    // double get_max_tank() const {return max_fuel;}
    // double get_consumption_rate() {return consumption;}
    //
    // void update_fuel(){
    //     curr_fuel -= consumption;
    //     if(curr_fuel<=0)
    //     {
    //         state = ShipState::DEAD;
    //         curr_speed = 0;
    //         angle = 0;
    //     }
    // }

protected:
    double curr_fuel, resistance;
    double max_fuel, consumption;
    shared_ptr<Port> curr_port;
};


#endif