

#include "Cruiser.h"


Cruiser::Cruiser(const Data& d, double range, double force): Ship(d), range(range), force(force){}
//pirates!
//
// void Cruiser::update() {
//   move_by_point();
// }
//
// void Cruiser::set_course(double speed, double angle) {
//     curr_speed = speed;
//     this->angle = angle; //TODO understand
// }
//
// void Cruiser::describe() const {
//     std::cout << "i am a pirate! AAARRRRRRR";
// }
//
void Cruiser::attack(CivilianShip& s) {
    if (dist(this->get_position(),s.get_position()) <= range){
        if (force > s.get_resistance()){
            s.been_attacked(false);
            force++;
        }else{
            s.been_attacked(true);
            force--;
        }
    }
}

double Cruiser::get_force() const{ return force;}




