#ifndef EX3_PORT_H
#define EX3_PORT_H

#include <string>
#include <utility>
#include <queue>
#include "Geometry.h"
#include <memory>




class CivilianShip;

class Port{
public:
    Port(std::string name,const Point& pos ,double fuel_production, double fuel): name(std::move(name)), pos(pos), fuel_production(fuel_production), fuel(fuel){
    }

    Port(const Port& rhs) = default;
    Port& operator=(const Port& rhs) = default;

    Port(Port&& rhs) = default;
    Port& operator=(Port&& rhs) = default;

    void update();

    void add_to_queue(const std::shared_ptr<CivilianShip>& s);

    Point get_position()const {return pos;}
    std::string get_name() const {return name;}
    double get_available_fuel() const {return fuel;}
    void describe() const;

private:
    std::string name;
    Point pos;
    double fuel_production;
    double fuel;
    std::queue<std::weak_ptr<CivilianShip>> ship_q{};
};

#endif
