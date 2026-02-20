#ifndef EX3_PORT_H
#define EX3_PORT_H

#include <string>
#include <utility>
#include <queue>
#include "Geometry.h"
#include <memory>



using namespace std;
class CivilianShip;

class Port{
public:
    Port(string name,const Point& pos ,double fuel_production, double fuel): name(std::move(name)), pos(pos), fuel_production(fuel_production), fuel(fuel){
    }

    Port(const Port& rhs) = default;
    Port& operator=(const Port& rhs) = default;

    Port(Port&& rhs) = default;
    Port& operator=(Port&& rhs) = default;

    void update();

    void add_to_queue(const shared_ptr<CivilianShip>& s);

    Point get_position()const {return pos;}
    string get_name() const {return name;}
    double get_available_fuel() const {return fuel;}

private:
    string name;
    Point pos;
    double fuel_production;
    double fuel;
    queue<weak_ptr<CivilianShip>> ship_q{};
};

#endif
