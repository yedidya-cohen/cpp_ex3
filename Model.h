#ifndef EX3_MODEL_H
#define EX3_MODEL_H

#include "Freighter.h"
#include "Patrol.h"
#include "Cruiser.h"
#include "Port.h"
#include <vector>
#include <algorithm>

using namespace std;

class Model{
public:
    static Model& get_instance(){
        static Model m;
        return m;
    }

    bool create_freighter_ship(Data d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo, Port& destination);
    bool create_patrol_ship(Data& d,double fuel, double max_fuel, double consumption, double resistance);
    bool create_pirate_ship( Data& d,double range,double force);

    bool create_port(string name,const Point& pos ,double fuel_production, double fuel);

    const vector<CivilianShip>& get_ships() {return ships;}
    const vector<Cruiser>& get_pirates() {return pirates;}
    const vector<Port>& get_ports() {return ports;}

    // void status();
    // void update();

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

private:
    Model() = default; //singleton
    ~Model() = default;
    vector<Cruiser> pirates;
    vector<CivilianShip> ships;
    vector<Port> ports; //save by order for patrol

    bool is_civil_exists(const string& o) const;
    bool is_pirate_exists(const string& o) const;
    bool is_port_exists(const string& o) const;

};

#endif //EX3_MODEL_H
