#include "Ship.h"


void Ship::set_speed(double speed)
{
    if (speed < 0.0) { curr_speed = 0.0;}
    else if (speed > max_speed) {curr_speed = max_speed;}
    else {curr_speed = speed;}
}

