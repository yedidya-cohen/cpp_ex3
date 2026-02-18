#ifndef EX3_MODEL_H
#define EX3_MODEL_H

#include <memory>
#include <string>
#include <vector>
#include "Ship.h"

class CivilianShip;
class Cruiser;
class Port;

using namespace std;

class Model{
public:
    static Model& get_instance(){
        static Model m;
        return m;
    }

    bool create_freighter_ship(Ship::Data& d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo);
    bool create_patrol_ship(Ship::Data& d,double fuel, double max_fuel, double consumption, double resistance);
    bool create_pirate_ship( Ship::Data& d,double range,double force);

    bool create_port(string name,const Point& pos ,double fuel_production, double fuel);

    vector<weak_ptr<CivilianShip>> get_ships() const;
    vector<weak_ptr<Cruiser>> get_pirates() const;
    vector<weak_ptr<Port>> get_ports() const;

    const shared_ptr<Port> get_port_by_name(const string& name);
    const shared_ptr<CivilianShip> get_ship_by_name(const string& name);

    // void status();
    void update();

    // void course(string& ship_name,double angle, double speed);
    // void position(string& ship_name, Point& p, double speed);
    // void destination(string& ship_name, string& name, double speed);
    //
    // void load_at(string& ship_name, string& port_name);
    // void unload_at(string& ship_name, string& port_name, int amount);
    // void dock_at(string& ship_name, string& port_name);
    // void attack(string& ship_name, string& ship_target);
    // void refuel(string& ship_name);
    // void stop(string& ship_name);
    //
    // const Port& get_port(int index) const;

    bool attacking(const string& attacked, int force);
    shared_ptr<Port> defualt_port();
    void add_to_refueling(const string& name, shared_ptr<Port> p);

private:
    Model() = default; //singleton
    ~Model() = default;
    vector<shared_ptr<Cruiser>> pirates;
    vector<shared_ptr<CivilianShip>> ships;
    vector<shared_ptr<Port>> ports;

    bool is_civil_exists(const string& o) const;
    bool is_pirate_exists(const string& o) const;
    bool is_port_exists(const string& o) const;
};



#endif //EX3_MODEL_H
