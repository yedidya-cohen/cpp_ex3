#ifndef EX3_PORT_H
#define EX3_PORT_H

#include <string>
#include <utility>
using namespace std;

class Port{ //TODO:
public:
    Port(string name, double fuel_production, double fuel): name(std::move(name)), fuel_production(fuel_production), fuel(fuel){}
    void update();
    void describe();
    double provide_fuel(double amount);

private:
    string name;
    const double fuel_production;
    double fuel;

};

#endif