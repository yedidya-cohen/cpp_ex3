#ifndef EX3_PATROL_H
#define EX3_PATROL_H

#include <vector>
#include "CivilianShip.h"


//this class represent an actual ship - patrol, patrol is the police of the sea - she go to all ports and travel between them
class Patrol : public CivilianShip{

public:
    Patrol(Data& d,double fuel, double max_fuel, double consumption, double resistance);
    //main function
    void update() override;
    void describe() const override;


private:
    //what is my next step
    void next_step();
    //wait 3 steps - refuel,dock,dest
    void my_3_steps();
    //which port i visit
    std::vector<std::string> visited;
    //to take care in the 3 steps
    enum PatrolState {REFUEL=0,DOCK=1,DEST=2,NONE=3};
    PatrolState patrolState;
    //what is the first port we been to
    std::string first_port;
};

#endif //EX3_PATROL_H
