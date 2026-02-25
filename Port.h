#ifndef EX3_PORT_H
#define EX3_PORT_H

#include <string>
#include <utility>
#include <queue>
#include "Geometry.h"
#include <memory>

class CivilianShip;
//this class represent a port with cpacity and able to produce fuel - i wish all the ports were like this
class Port{

public:
    Port(std::string name,const Point& pos ,double fuel_production, double fuel): name(std::move(name)), pos(pos), fuel_production(fuel_production), fuel(fuel){
    }
    //main function that happen each tick of the timer
    void update();
    //the port hold queue for thos who he need to serve
    void add_to_queue(const std::shared_ptr<CivilianShip>& s);
    //getters
    Point get_position()const {return pos;}
    std::string get_name() const {return name;}
    double get_available_fuel() const {return fuel;}
    //function that print who am i
    void describe() const;

private:
    std::string name;
    Point pos;
    double fuel_production;
    double fuel;
    std::queue<std::weak_ptr<CivilianShip>> ship_q{};
};

#endif
