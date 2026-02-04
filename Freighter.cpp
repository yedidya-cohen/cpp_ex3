#include "Freighter.h"


Freighter::Freighter(Data d,double fuel, double max_fuel, double consumption, double resistance ,int max_capacity,int cargo, Port& destination)
:CivilianShip(d,fuel,max_fuel,consumption,resistance),
max_capacity(max_capacity),cargo(cargo),dest(destination){}

//
// void Freighter::update(){
//     move_by_point();
// }
//
// void Freighter::describe() const{
//     std::cout << "i am a freighter! i have your ali-express luxury items";
// }
//
// void Freighter::set_destination(weak_ptr<Port> dest, double speed){
//     if (auto port = dest.lock()){
//         angle_to(port->get_pos());
//         current_speed = speed;
//     }
// }
//
// void Freighter::set_course(double speed, double angle){
//     Ship::angle = angle;
//     current_speed = speed;
// }
//
// void Freighter::set_destination(const Port &dest, double speed) {
//     curr_speed = speed < max_speed ? speed : max_speed;
//
// }
