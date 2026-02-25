#ifndef EX3_FREIGHTER_H
#define EX3_FREIGHTER_H

#include "CivilianShip.h"
#include <vector>


class Freighter: public CivilianShip{
public:
    Freighter(Ship::Data& d,double fuel, double max_fuel, double consumption, int resistance ,int max_capacity,int cargo);

// commands
    void update() override; // update ther  ship by 1 hhr /
    void describe() const override;
    void load_at(std::shared_ptr<Port>& p); // set a mission to load art t port athe // set a mission to unload at the prorort (and by by how much
    void unload_at(std::shared_ptr<Port>& p, int amount);


private:
    int is_exists(const std::string& port_name) const;
    void update_cargo(); // updateteds the amount of cargo we hold // cheecks if a port exists
    const int max_capacity; // the maximunmum cargo we can hold
    int cargo;// amount of cargo we hold
    std::vector<std::pair<std::weak_ptr<Port>, int>>  missions; // missions to load\un-load at port <port, amount>

};

#endif