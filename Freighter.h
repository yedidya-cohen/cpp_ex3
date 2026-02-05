#ifndef EX3_FREIGHTER_H
#define EX3_FREIGHTER_H

#include "CivilianShip.h"
using namespace std;

class Freighter: public CivilianShip{
public:
    Freighter(Data d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo, Port& destination);
    Freighter(const Freighter& other) = default;
    Freighter& operator=(const Freighter& other) = default;

    // void update() override;
    // void describe() const override;

    // void load_at(Port& dest);
    // void unload_at(Port& dest);

private:
    const int max_capacity;
    int cargo;
    Port& dest;
   // vector<pair<string, int> (for loading and unloa

    enum mission {
        None = 0,
        Load = 1,
        Unload = 2,
        dock = 3
    };
    queue<pair<Port,mission>> next_mission;
};

#endif