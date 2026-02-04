#include "Model.h"

#include <string>
#include "Geometry.h"

// void Model::update() {
//     for (auto& s: ships){s.update();}
//     for (auto& p: pirates){p.update();}
//     for (auto& p: ports){p.update();}
//
// }



// void Model::status() {
//     for (auto& s: ships){s.status();}
//     for (auto& p: pirates){p.status();}
//     for (auto& p: ports){p.status();}
// }


bool Model::create_freighter_ship(Data d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo, Port& destination) {
    if (is_civil_exists(d.name)) {
        cout << "Ship with name:" << d.name << "already exists \n";
        return false;
    }
    // TODO: create class of freighter - depens on class
    //Data d, int max_capacity,int cargo, int resistance, Port& destination
    ships.emplace_back(Freighter(d, fuel, max_fuel, consumption, resistance, max_capacity, cargo, destination));
    return true;
}

bool Model::create_patrol_ship(Data& d,double fuel, double max_fuel, double consumption, double resistance) {
    if (is_civil_exists(d.name)) {
        cout << "Ship with name:" << d.name << "already exists \n";
        return false;
    }
    //TODO - depens on patrol c'tors

    ships.emplace_back(Patrol(d,fuel,max_fuel,consumption,resistance));
    return true;
}

bool Model::create_pirate_ship (Data& d,double range,double force){
    if (is_pirate_exists(d.name)) {
        cout << "Ship with name:" << d.name << "already exists \n";
        return false;
    }
    //TODO - depens on C'tor of pirets!
    pirates.emplace_back(Cruiser(d, range, force));
    return true;

}

bool Model::create_port(string name,const Point& pos ,double fuel_production, double fuel) {
    if (is_port_exists(name)) {
        cout<< "Port with name:" << name << "already exists \n";
        return false;
    }
    //TODO -depens on C'tor of ports!

    ports.emplace_back(Port(name, pos, fuel_production,fuel));
    return true;
}

bool Model::is_civil_exists(const string &o)const{
    for (auto& s:ships) {
        if (s.get_name() == o) {return true;}
    }
    return false;
}

bool Model::is_pirate_exists(const string &o) const{
    for (auto& s: pirates)
    {
        if (s.get_name() == o) {return true;}
    }
    return false;
}

bool Model::is_port_exists(const string &o) const{
    for (auto& s: ports)
    {
        if (s.get_name()==o){return true;}
    }
    return false;
}