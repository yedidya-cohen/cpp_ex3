#ifndef EX3_FREIGHTER_H
#define EX3_FREIGHTER_H

#include <memory>
#include "Port.h"
#include "Ship.h"
using namespace std;

class Freighter: public Ship{
public:
    Freighter(Data d, int max_capacity, int resistance, weak_ptr<Port> destination);
    void update() override;
    void describe() const override;
    void set_destination();
    void set_course(double speed, double angle) override;
    bool try_docking();
    void load();
    void attcked(bool win_lose);
    double get_resistance() const;
    double get_force() const;

private:
    //static constexpr double max_fuel = 500.0, max_velocity=40.0, waste_fuel = 1000.0
    const int max_capacity;
    double resistance;
    int cargo;
};

#endif