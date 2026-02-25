#ifndef EX3_MODEL_H
#define EX3_MODEL_H

#include <memory>
#include <string>
#include <vector>

#include "CivilianShip.h"
#include "Ship.h"

class Cruiser;
class Port;

//this class responsible for keep the simulation alive - it holds all the ships, all the ports and she knows how to do a tick of clock and update everyone!
//Model is a singletone
class Model{
public:
    //how to create singletone nicely - better because we dont need to detect d'tor
    static Model& get_instance(){
        static Model m;
        return m;
    }
//singleTone there are no copy or other copies of this class
    Model(const Model&) = delete;
    Model(Model&&) = delete;
    Model& operator=(const Model&) = delete;
    Model& operator=(Model&&) = delete;
    //commands to do all that given
    //create ships/ports
    bool create_freighter_ship(Ship::Data& d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo);
    bool create_patrol_ship(Ship::Data& d,double fuel, double max_fuel, double consumption, double resistance);
    bool create_pirate_ship( Ship::Data& d,double range,double force);

    bool create_port(std::string name,const Point& pos ,double fuel_production, double fuel);
    //return the vector for each one - but by weakptr - basically for view
    std::vector<std::weak_ptr<CivilianShip>> get_ships() const;
    std::vector<std::weak_ptr<Cruiser>> get_pirates() const;
    std::vector<std::weak_ptr<Port>> get_ports() const;

    //check to see by name
    const std::shared_ptr<Port> get_port_by_name(const std::string& name);
    const std::shared_ptr<CivilianShip> get_ship_by_name(const std::string& name);
    const std::shared_ptr<Cruiser> get_pirate_ship_by_name(const std::string& name);
    //main function
    void update();
    void describe() const;

    //command that needed
    void course(const std::string& ship_name,double angle, double speed);
    void position(const std::string& ship_name, Point& p, double speed);
    void destination(const std::string& ship_name, std::string& port_name, double speed);

    void load_at(const std::string& ship_name, std::string& port_name);
    void unload_at(const std::string& ship_name, std::string& port_name, int amount);
    void dock_at(const std::string& ship_name, std::string& port_name);
    void attack(const std::string& ship_name, const std::string& ship_target);
    void refuel(const std::string& ship_name);
    void stop(const std::string& ship_name);
    //for pirets
    bool attacking(const std::string& attacked, int force);


private:
    Model(); //singleton
    ~Model() = default;
    std::vector<std::shared_ptr<Cruiser>> pirates;
    std::vector<std::shared_ptr<CivilianShip>> ships;
    std::vector<std::shared_ptr<Port>> ports;

    //private func to see if exsist
    bool is_civil_exists(const std::string& o) const;
    bool is_pirate_exists(const std::string& o) const;
    bool is_port_exists(const std::string& o) const;
};



#endif //EX3_MODEL_H
