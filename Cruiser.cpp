

#include "Cruiser.h"


Cruiser::Cruiser(const Data& d, double range, double force): Ship(d), range(range), force(force)
,need_to_attack(""){}
//pirates!


void Cruiser::update() {
    if (need_to_attack != "" ){
        Model::get_instance().attacking(need_to_attack, force) ? force ++ : force --;

        need_to_attack = "";
        return;
    }
    Ship::update();
}


void Cruiser::describe() const {
    std::cout << "Cruiser " << name << "at"  << position  << "force: "<< force <<" Moving on course "<< to_degrees(rad_angle)
    <<"deg , speed "<<curr_speed<< " nm/hr"<<endl;
}
//Cruiser Xerxes at (5.00, 25.00), force: 6, Moving on course 270.00 deg, speed 20.00
//nm/hr
//

//TODO: 2 cmd of attack, what to do?
void Cruiser::attack(const CivilianShip& s) {
    if (dist(this->get_position(),s.get_position()) <= range) {need_to_attack = s.get_name();}
}

double Cruiser::get_force() const{ return force;}




