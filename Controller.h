//
// Created by yedid on 04/02/2026.
//

#ifndef EX3_CONTROLLER_H
#define EX3_CONTROLLER_H
#include <iostream>

#include "View.h"
#include "Model.h"


class Controller {
public:
    void simulate();

    //Model
    void status();
    void go();
    void create_s();

    //View
    void defaultSize();
    void set_size();
    void set_zoom();
    void set_pan();
    void show();

   //ships
    void set_course();
    void set_position();
    void set_destination();
    void load_at();
    void unload_at();
    void dock_at();
    void attack();
    void refuel();
    void stop();

private:
    View view;
};


#endif //EX3_CONTROLLER_H