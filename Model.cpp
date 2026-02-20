#include "Model.h"
#include "Cruiser.h"
#include "CivilianShip.h"
#include "Freighter.h"
#include "Patrol.h"
#include "Port.h"

vector<weak_ptr<CivilianShip>> Model::get_ships() const {
    vector<weak_ptr<CivilianShip>> out;
    out.reserve(ships.size());
    for (const auto& s : ships) {
        out.push_back(s);
    }
    return out;
}

vector<weak_ptr<Cruiser>> Model::get_pirates() const {
    vector<weak_ptr<Cruiser>> out;
    out.reserve(pirates.size());
    for (const auto& p : pirates) {
        out.push_back(p);
    }
    return out;
}

vector<weak_ptr<Port>> Model::get_ports() const {
    vector<weak_ptr<Port>> out;
    out.reserve(ports.size());
    for (const auto& p : ports) {
        out.push_back(p);
    }
    return out;
}

void Model::update() {
    for (auto& s: ships){s->update();}
    for (auto& p: pirates){p->update();}
    for (auto& p: ports){p->update();}
}

//note - save but i intentd not to use default - everything is pointers - no need to check default
// shared_ptr<Port> Model::defualt_port() {
//     shared_ptr<Port> p = make_shared<Port>("", Point(-1,-1), -1, -1 );
//     return p;
// }


// void Model::status() {
//     for (auto& s: ships){s.status();}
//     for (auto& p: pirates){p.status();}
//     for (auto& p: ports){p.status();}
// }


bool Model::create_freighter_ship(Ship::Data& d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo) {
    if (is_civil_exists(d.name)) {
        cout << "Ship with name:" << d.name << "already exists \n";
        return false;
    }
    // TODO: create class of freighter - depens on class
    //Data d, int max_capacity,int cargo, int resistance, Port& destination
    auto freighter = make_shared<Freighter>(d, fuel, max_fuel, consumption, resistance, max_capacity, cargo);
    ships.emplace_back(freighter);
    return true;
}

bool Model::create_patrol_ship(Ship::Data& d,double fuel, double max_fuel, double consumption, double resistance) {
    if (is_civil_exists(d.name)) {
        cout << "Ship with name:" << d.name << "already exists \n";
        return false;
    }
    //TODO - depens on patrol c'tors
    auto patrol = make_shared<Patrol>(d,fuel,max_fuel,consumption,resistance);
    ships.emplace_back(patrol);
    return true;
}

bool Model::create_pirate_ship (Ship::Data& d,double range,double force){
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

const shared_ptr<Port> Model::get_port_by_name(const string &name) {
    for (auto& p:ports) {
        if (p->get_name() == name) {return p;}
    }
    return nullptr;
}

const shared_ptr<CivilianShip> Model::get_ship_by_name(const string &name) {
    for (auto& p:ships) {
        if (p->get_name() == name) {return p;}
    }
    return nullptr;
}

bool Model::attacking(const string& attacked, int force) {
    shared_ptr<CivilianShip> target = get_ship_by_name(attacked);
    if (!target) {
        return false;
    }

    const bool win = force > target->get_resistance();
    target->been_attacked(win);
    return win;
}

void Model::add_to_refueling(const string &name, shared_ptr<Port> p) {
    shared_ptr<CivilianShip> s = get_ship_by_name(name);
    if (!s) {return; }
    p->add_to_queue(s);
}


