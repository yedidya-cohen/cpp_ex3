

#include "Cruiser.h"


Cruiser::Cruiser(const Data& d, double range, double force): Ship(d), range(range), force(force){

}
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
// void Cruiser::attack(CivilianShip& s) {
//     if (calc_dist(*this,s) <= range){
//         if (force > s.get_resistance()){
//             s.attacked(false);
//             force++;
//         }else{
//             s.attacked(true);
//             force--;
//         }
//     }
// }
//
//
//
// void Cruiser::stop(){
//     Ship::state = STOPPED;
//     curr_speed = 0;
//     angle = 0;
// }
//
// double Cruiser::get_force() const{ return force;}




