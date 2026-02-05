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
    auto freighter = make_shared<Freighter>(d, fuel, max_fuel, consumption, resistance, max_capacity, cargo, destination);
    ships.emplace_back(freighter);
    return true;
}

bool Model::create_patrol_ship(Data& d,double fuel, double max_fuel, double consumption, double resistance) {
    if (is_civil_exists(d.name)) {
        cout << "Ship with name:" << d.name << "already exists \n";
        return false;
    }
    //TODO - depens on patrol c'tors
    auto patrol = make_shared<Patrol>(d,fuel,max_fuel,consumption,resistance);
    ships.emplace_back(patrol);
    return true;
}

bool Model::create_pirate_ship (Data& d,double range,double force){
    if (is_pirate_exists(d.name)) {
        cout << "Ship with name:" << d.name << "already exists \n";
        return false;
    }
    //TODO - depens on C'tor of pirets!
    auto pirate = make_shared<Cruiser>(d,range,force);
    pirates.emplace_back(pirate);
    return true;

}

bool Model::create_port(string name,const Point& pos ,double fuel_production, double fuel) {
    if (is_port_exists(name)) {
        cout<< "Port with name:" << name << "already exists \n";
        return false;
    }
    //TODO -depens on C'tor of ports!
    auto port = make_shared<Port>(name,pos,fuel_production,fuel);
    ports.emplace_back(port);
    return true;
}

bool Model::is_civil_exists(const string &o)const{
    for (auto& s:ships) {
        if (s->get_name() == o) {return true;}
    }
    return false;
}

bool Model::is_pirate_exists(const string &o) const{
    for (auto& s: pirates)
    {
        if (s->get_name() == o) {return true;}
    }
    return false;
}

bool Model::is_port_exists(const string &o) const{
    for (auto& s: ports)
    {
        if (s->get_name()==o){return true;}
    }
    return false;
}

template<typename T>
vector<weak_ptr<T>> Model::toWeakPtrVector(const vector<shared_ptr<T>> &shared_vec) {

        std::vector<std::weak_ptr<T>> weak_vec;
        weak_vec.reserve(shared_vec.size());  // Pre-allocate for efficiency

        for (const auto& shared : shared_vec) {
            weak_vec.push_back(shared);  // Implicit conversion
        }

        return weak_vec;
}