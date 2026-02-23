#include "Model.h"
#include "Cruiser.h"
#include "CivilianShip.h"
#include "Freighter.h"
#include "Patrol.h"
#include "Port.h"

using namespace std;


Model::Model() {
    create_port("Nagoya",{50,5},1000,1000000);
}

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
    for (auto& p: pirates){p->update();}
    for (auto& s: ships){s->update();}
    for (auto& p: ports){p->update();}

}

bool Model::create_freighter_ship(Ship::Data& d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo) {
    if (is_civil_exists(d.name)) {
        cerr << "Ship with name:" << d.name << "already exists \n";
        return false;
    }
    //Data d, int max_capacity,int cargo, int resistance, Port& destination
    auto freighter = make_shared<Freighter>(d, fuel, max_fuel, consumption, resistance, max_capacity, cargo);
    ships.emplace_back(freighter);
    return true;
}

bool Model::create_patrol_ship(Ship::Data& d,double fuel, double max_fuel, double consumption, double resistance) {
    if (is_civil_exists(d.name)) {
        cerr << "Ship with name:" << d.name << "already exists \n";
        return false;
    }
    auto patrol = make_shared<Patrol>(d,fuel,max_fuel,consumption,resistance);
    ships.emplace_back(patrol);
    return true;
}

bool Model::create_pirate_ship (Ship::Data& d,double range,double force){
    if (is_pirate_exists(d.name)) {
        cerr << "Ship with name:" << d.name << "already exists \n";
        return false;
    }
    auto pirate = make_shared<Cruiser>(d,range,force);
    pirates.emplace_back(pirate);
    return true;

}

bool Model::create_port(string name,const Point& pos ,double fuel_production, double fuel) {
    if (is_port_exists(name)) {
        cerr << "Port with name:" << name << "already exists \n";
        return false;
    }
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

const shared_ptr<Cruiser> Model::get_pirate_ship_by_name(const string &name) {
    for (auto& p:pirates) {
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
    target->been_attacked(!win);
    return win;
}

void Model::describe() const {
    for (auto& s : ships) {s->describe();}
    for (auto& s : pirates) {s->describe();}
    for (auto& s : ports) {s->describe();}
}

void Model::course(const string &ship_name, double angle, double speed) {
    if (angle<0 || angle>360){cerr<<"Wrong angle, should be 0-360"<<endl;return;}
    if (auto s= get_ship_by_name(ship_name)) {s->set_course(angle,speed);}
    else if (auto v = get_pirate_ship_by_name(ship_name)) { v->set_course(angle, speed);}
    else {cerr<<"Cannot set course because " << ship_name << " doesn't exists" << endl;}
}

void Model::position(const string &ship_name, Point &p, double speed) {
    if (auto s= get_ship_by_name(ship_name)) {s->set_pos(p,speed);}
    else if (auto v = get_pirate_ship_by_name(ship_name)) {v->set_pos(p, speed);}
    else {cerr<<"Cannot set position because " << ship_name << " doesn't exists" << endl;}

}

void Model::destination(const string &ship_name, string &port_name, double speed) {
    shared_ptr<Port> p = get_port_by_name(port_name);
    if (!p) { cerr << "cannot find port named " << port_name << endl; return;}
    if (auto s= get_ship_by_name(ship_name)) {s->set_destination(p,speed);}
    else {cerr<<"Cannot set position because " << ship_name << " doesn't exists" << endl;}
}


void Model::load_at(const string &ship_name, string &port_name) {
    auto p = get_port_by_name(port_name);
    if (!p) {cerr << "cannot find port named " << port_name << endl; return;}
    //what do i do
    if(const auto f = dynamic_pointer_cast<Freighter>(get_ship_by_name(ship_name))) {f->load_at(p);}
    else {cerr << "Cannot find Freighter ship by name " << ship_name  << endl;}
}


void Model::unload_at(const string &ship_name, string &port_name, int amount) {
    auto p = get_port_by_name(port_name);
    if (!p) {cerr << "cannot find port named " << port_name << endl; return;}
    if(const auto f = dynamic_pointer_cast<Freighter>(get_ship_by_name(ship_name))) {f->unload_at(p,amount);}
    else {cerr << "Cannot find Freighter ship by name " << ship_name  << endl;}
}

void Model::dock_at(const string &ship_name, string &port_name) {
    auto p = get_port_by_name(port_name);
    if (!p) {cerr << "cannot find port named " << port_name << endl; return;}
    if (auto s= get_ship_by_name(ship_name)) {s->dock_at(p);}
    else {cerr << "Cannot find ship by name " << ship_name  << endl;}
}

void Model::attack(const string &ship_name, const string &ship_target) {
    auto pirate = get_pirate_ship_by_name(ship_name);
    if (!pirate) {cerr<<"Cannot find Cruiser by name " << ship_name << endl; return;}
    auto target = get_ship_by_name(ship_target);
    if (!target) {cerr<<"Cannot find Ship by name " << ship_target << endl; return;}
    pirate->attack(target);
}

void Model::refuel(const string &ship_name) {
    if (auto s= get_ship_by_name(ship_name)){
        if (s->get_state() == Ship::ShipState::DOCKED){
            auto p = s->get_docked_port();
            if (p) {
                p->add_to_queue(s);
                s->refuel();
            }
        }
    }
    else {cerr << "Cannot find ship by name " << ship_name;}
}

void Model::stop(const string &ship_name) {
    if (auto s= get_ship_by_name(ship_name)) {s->stop();}
    else if (auto v = get_pirate_ship_by_name(ship_name)) {v->stop();}
    else {cerr<<"Cannot find ship by name " << ship_name << endl;}
}





