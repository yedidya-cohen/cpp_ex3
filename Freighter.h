#ifndef EX3_FREIGHTER_H
#define EX3_FREIGHTER_H

#include "CivilianShip.h"
using namespace std;

class Freighter: public CivilianShip{
public:
    Freighter(Data d, int max_capacity,int cargo, Port& destination, int resistance,double max_fuel,double curr_fuel,double consumption);
    // void update() override;
    //void describe() const override;
    // void set_destination(const Port& dest, double speed) override;
    // void set_course(double speed, double angle);

private:
    const int max_capacity;
    int cargo;
    Port& dest;


    enum mission {
        None = 0,
        Load = 1,
        Unload = 2,
        dock = 3
    };
    queue<pair<Port,mission>> next_mission;
};

#endif