#ifndef EX3_FREIGHTER_H
#define EX3_FREIGHTER_H

#include "CivilianShip.h"
using namespace std;

class Freighter: public CivilianShip{
public:
    Freighter(Data d, int max_capacity,int cargo, int resistance, weak_ptr<Port> destination);
    void update() override;
    void describe() const override;
    void set_destination(weak_ptr<Port> dest, double speed) override;
    void set_course(double speed, double angle) override;
    bool try_docking();
    void load();
    void attacked(bool win_lose);

private:
    //static constexpr double max_fuel = 500.0, max_velocity=40.0, waste_fuel = 1000.0
    const int max_capacity;
    int cargo;
};

#endif