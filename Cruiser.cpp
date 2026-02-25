#include "Cruiser.h"
#include "CivilianShip.h"
#include "Model.h"

using namespace std;

Cruiser::Cruiser(Data& d, double range, int force): Ship(d), range(range), force(force)
,need_to_attack(){}



void Cruiser::update() { //attacking or moving by 1hr
    if (!need_to_attack.empty() ){
        Model::get_instance().attacking(need_to_attack, force) ? force ++ : force --;
        need_to_attack = "";
        return;
    }
    Ship::update();
}


void Cruiser::describe() const {
    std::cout << "Cruiser " << name << " at "  << position  << " force: "<< force <<" Moving on course "<< to_degrees(rad_angle)
    <<"deg , speed "<<curr_speed<< " nm/hr"<<endl;
}



void Cruiser::attack(weak_ptr<CivilianShip> s) { // trying to attack ship if it within range
    auto sp = s.lock();
    if (!sp) {return;}
    if (dist(this->get_position(),sp->get_position()) <= range) {need_to_attack = sp->get_name();}
}

double Cruiser::get_force() const{ return force;}




