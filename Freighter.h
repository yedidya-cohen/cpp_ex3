#ifndef EX3_FREIGHTER_H
#define EX3_FREIGHTER_H

#include "CivilianShip.h"
using namespace std;

class Freighter: public CivilianShip{
public:
    Freighter(Data d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo, Port& destination);
    Freighter(const Freighter& other) = default;
    Freighter& operator=(const Freighter& other) = default;

    void update() override;
    void describe() const override;
    void load_at(shared_ptr<Port>& p,int x=1);
    void unload_at(shared_ptr<Port>& p, int amount);


private:
    int is_exists(shared_ptr<Port>& p) const;
    void update_cargo();
    const int max_capacity;
    int cargo;
    shared_ptr<Port> dest;
    vector<pair<shared_ptr<Port>, int>>  missions;

    // enum mission {
    //     None = 0,
    //     Load = 1,
    //     Unload = 2,
    //     dock = 3
    // };
    // queue<pair<Port,mission>> next_mission;
};

#endif