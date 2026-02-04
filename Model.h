#ifndef EX3_MODEL_H
#define EX3_MODEL_H

#include "Freighter.h"
#include "Patrol.h"
#include "Cruiser.h"
#include "Port.h"
#include "Point.h"
#include <vector>

using namespace std;

class Model{
public:
    static Model& get_instance(){
        static Model m;
        return m;
    }

    bool create_freighter_ship(const string& name, Point position, int resistance, int container_capacity);
    bool create_patrol_ship(const string& name, Point position, int resistance);
    bool create_pirate_ship(const string& name, Point position, int attack_force, int attack_range);

    bool create_port();

    void status();
    void update();
    void sort_by_print();

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

    bool is_civil_exists(const string& o);
    bool is_pirate_exists(const string& o);
    bool is_port_exists(const string& o);

};

#endif //EX3_MODEL_H
