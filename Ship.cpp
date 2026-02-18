#include "Ship.h"
#include "Port.h"


void Ship::set_destination(const Port &p, double speed) {
      Point p_dest = p.get_position();
      set_pos(p_dest,speed);

}