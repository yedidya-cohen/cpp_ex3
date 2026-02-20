#include "Ship.h"
#include "Port.h"


void Ship::set_destination(weak_ptr<Port> p, double speed) {
      auto sp = p.lock();
      if (!sp) return;
      Point p_dest = sp->get_position();
      set_pos(p_dest,speed);
}