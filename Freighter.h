#ifndef EX3_FREIGHTER_H
#define EX3_FREIGHTER_H

#include "CivilianShip.h"
#include <vector>


class Freighter: public CivilianShip{
public:
    Freighter(Ship::Data& d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo);
    Freighter(const Freighter& other) = default;
    Freighter& operator=(const Freighter& other) = default;

    void update() override;
    void describe() const override;
    void load_at(std::shared_ptr<Port>& p);
    void unload_at(std::shared_ptr<Port>& p, int amount);


private:
    int is_exists(const std::string& port_name) const;
    void update_cargo();
    const int max_capacity;
    int cargo;
    std::vector<std::pair<std::weak_ptr<Port>, int>>  missions;

    // enum mission {
    //     None = 0,
    //     Load = 1,
    //     Unload = 2,
    //     dock = 3
    // };
    // queue<pair<Port,mission>> next_mission;
};

#endif