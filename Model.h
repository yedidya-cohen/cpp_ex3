#ifndef EX3_MODEL_H
#define EX3_MODEL_H

#include <memory>
#include <string>
#include <vector>

#include "CivilianShip.h"
#include "Ship.h"

class CivilianShip;
class Cruiser;
class Port;


class Model{
public:
    static Model& get_instance(){
        static Model m;
        return m;
    }

    Model(const Model&) = delete;
    Model(Model&&) = delete;
    Model& operator=(const Model&) = delete;
    Model& operator=(Model&&) = delete;

    bool create_freighter_ship(Ship::Data& d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo);
    bool create_patrol_ship(Ship::Data& d,double fuel, double max_fuel, double consumption, double resistance);
    bool create_pirate_ship( Ship::Data& d,double range,double force);

    bool create_port(std::string name,const Point& pos ,double fuel_production, double fuel);

    std::vector<std::weak_ptr<CivilianShip>> get_ships() const;
    std::vector<std::weak_ptr<Cruiser>> get_pirates() const;
    std::vector<std::weak_ptr<Port>> get_ports() const;


    const std::shared_ptr<Port> get_port_by_name(const std::string& name);
    const std::shared_ptr<CivilianShip> get_ship_by_name(const std::string& name);
    const std::shared_ptr<Cruiser> get_pirate_ship_by_name(const std::string& name);

    void update();
    void describe() const;


    void course(const std::string& ship_name,double angle, double speed);
    void position(const std::string& ship_name, Point& p, double speed);
    void destination(const std::string& ship_name, std::string& port_name, double speed);
    //
    void load_at(const std::string& ship_name, std::string& port_name);
    void unload_at(const std::string& ship_name, std::string& port_name, int amount);
    void dock_at(const std::string& ship_name, std::string& port_name);
    void attack(const std::string& ship_name, const std::string& ship_target);
    void refuel(const std::string& ship_name);
    void stop(const std::string& ship_name);
    //
    // const Port& get_port(int index) const; //not needed

    bool attacking(const std::string& attacked, int force);


private:
    Model(); //singleton
    ~Model() = default;
    std::vector<std::shared_ptr<Cruiser>> pirates;
    std::vector<std::shared_ptr<CivilianShip>> ships;
    std::vector<std::shared_ptr<Port>> ports;

    bool is_civil_exists(const std::string& o) const;
    bool is_pirate_exists(const std::string& o) const;
    bool is_port_exists(const std::string& o) const;
};



#endif //EX3_MODEL_H
