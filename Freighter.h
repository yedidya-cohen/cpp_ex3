#ifndef EX3_FREIGHTER_H
#define EX3_FREIGHTER_H

#include <memory>
#include "Port.h"
#include "Ship.h"
using namespace std;

class Freighter: public Ship{
public:
    Freighter(string name, double consumpsion, double max_speed, double fuel, double current_speed, double angle, Port position, int max_capacity, int resistance, weak_ptr<Port> destination);
    void update() override;
    void describe() const override;
    void set_destination() override;
    void set_course() override;
    bool try_docking();
    void load();

private:
    const int max_capacity, resistance;
    int cargo;
    bool is_docked;
};

#endif