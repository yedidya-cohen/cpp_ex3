#ifndef EX3_PORT_H
#define EX3_PORT_H

#include <string>
#include <utility>
#include <queue>
#include "Point.h"
#include "CivilianShip.h"

using namespace std;

class Port{
public:
    Port(string name,const Point& pos ,double fuel_production, double fuel): name(std::move(name)), pos(pos), fuel_production(fuel_production), fuel(fuel){

    }
    void update(){
        fuel+=fuel_production;
        if(!ship_q.empty()){
            //TODO refuel - pop
        }
    }

    void add_to_queue(CivilianShip & s);

    void decreace_fuel(double amount){
        fuel-=amount;
    }

    Point get_pos()const {return pos;}
    string get_name() const{return name;}
    double get_available_fuel() const {return fuel;}

private:
    const string name;
    const Point pos;
    const double fuel_production;
    double fuel;
    queue<CivilianShip> ship_q;
};

#endif