
#include "Patrol.h"

void Patrol::describe() const {
    CivilianShip::describe();
    cout<<"somthing somthing";
}

void Patrol::stop() {
    state = ShipState::STOPPED;
}

void Patrol::update_after_dock() {
    w_g.curr = w_g.r_l ? (w_g.curr++)% w_g.len : (w_g.curr--)%w_g.len;
    if(w_g.curr==w_g.start){
        //need to finish route;
    }
}