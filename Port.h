#ifndef EX3_PORT_H
#define EX3_PORT_H

#include "CivilianShip.h"
#include <string>
#include <utility>
#include <queue>
#include "Geometry.h"

class CivilianShip;
using namespace std;

class Port{
public:
    Port(string name,const Point& pos ,double fuel_production, double fuel): name(std::move(name)), pos(pos), fuel_production(fuel_production), fuel(fuel){
    }

    Port(const Port& rhs) = default;
    Port& operator=(const Port& rhs) = default;

    Port(Port&& rhs) = default;
    Port& operator=(Port&& rhs) = default;

    // void update(){
    //     fuel+=fuel_production;
    //     if(!ship_q.empty()){
    //         CivilianShip s = ship_q.pop();
    //
    //     }
    // }
    //
    void add_to_queue(CivilianShip& s) {
        //TODO: add to queue
    }
    //
    // void decreace_fuel(double amount){
    //     fuel-=amount;
    // }

    Point get_position()const {return pos;}
    string get_name() const {return name;}
    double get_available_fuel() const {return fuel;}

private:
    string name;
    Point pos;
    double fuel_production;
    double fuel;
    queue<shared_ptr<CivilianShip>> ship_q{};
};

#endif