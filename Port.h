#ifndef EX3_PORT_H
#define EX3_PORT_H

#include <string>
#include <utility>
#include "Point.h"
using namespace std;

class Port{ //TODO: need to describe? what else missing on Port? - maybe finish -D
public:
    Port(string name,const Point& pos ,double fuel_production, double fuel): name(std::move(name)), pos(pos), fuel_production(fuel_production), fuel(fuel){}
    void update(){
        fuel+=fuel_production;
    }
    void describe();//TODO needed?

    void decreace_fuel(double amount){//when a ship enter to port she ask how many to take and than decrease it
        fuel-=amount;
    }
    Point get_pos()const {return pos;}
    string get_name() const{return name;}
    double get_available_fuel() const {return fuel;}

private:
    string name;
    const Point pos;
    const double fuel_production;
    double fuel;

};

#endif