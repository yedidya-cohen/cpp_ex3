

#include "Cruiser.h"


Cruiser::Cruiser(Data d, double range, double force): Ship(std::move(d)), range(range), force(force){

}
//pirates!

void Cruiser::update() {
  move_by_point();
}

void Cruiser::set_course(double speed, double angle) {
    current_speed = speed;
    this->angle = angle;
}

void Cruiser::describe() const {
    std::cout << "i am a pirate! AAARRRRRRR";
}

void Cruiser::attack(const weak_ptr<CivilianShip>& s) {
    if (auto target = s.lock()){
        if (force > target->get_resistance()){
            target->attacked(false);
        }else{
            target->attacked(true);
            stop();
            Ship::state = DEAD;
        }
    }
}


void Cruiser::stop(){
    Ship::state = STOPPED;
    current_speed = 0;
    angle = 0;
}

double Cruiser::get_force() const{ return force;}




