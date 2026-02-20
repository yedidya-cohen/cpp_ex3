#ifndef EX3_CIVILIANSHIP_H
#define EX3_CIVILIANSHIP_H

# include "Ship.h"

class CivilianShip : public Ship
{
public:
    explicit CivilianShip(Data& d,double fuel, double max_fuel, double consumption, double resistance);
    ~CivilianShip() override = default; //abstract


    bool dock_at(shared_ptr<Port> p);
    virtual void update();

    double missing_fuel() const;
    void add_fuel(double f);

    void refuel();

    void for_port(); //for port after refuel

    void been_attacked(bool win_lose); //true mean lose
    virtual void describe() const = 0;

    double get_resistance() const;
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
    weak_ptr<Port> curr_port;
};


#endif
