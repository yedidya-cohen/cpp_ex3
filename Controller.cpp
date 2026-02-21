#include "Controller.h"



void Controller::simulate() {
    map<string, function<void()>> func = {
        {"default", [&]() {return;}},
        {"size", [&]() {return;}},
        {"zoom", [&]() {return;}},
        {"pan", [&]() {return;}},
        {"show", [&]() {return;}},
        {"status", [&]() {return;}},
        {"go", [&]() {return;}},
        {"create", [&]() {return;}}
    };
    string line; // saves a word from input
    do{
        cin >> line;
        // look for the word in the map
        auto find = func.find(line);
        // if in map -> run command else print error
        if(find != func.end()) {find->second();}
        else { ship_commands(line);}

    } while(line != "EXIT"); //exit = bye bye

}

void Controller::ship_commands(const string &ship_name) {
    map<string, function<void()>> func = {
        {"course", [&]() {set_course(ship_name);}},
        {"position", [&]() {set_position(ship_name);}},
        {"destination", [&]() {set_destination(ship_name);}},
        {"load_at", [&]() {load_at(ship_name);}},
        {"unload_at", [&]() {unload_at(ship_name);}},
        {"dock_at", [&]() {dock_at(ship_name);}},
        {"attack", [&]() {attack(ship_name);}},
        {"refuel", [&]() {refuel(ship_name);}},
        {"stop",[&](){stop(ship_name);}}
    };
    string cmd;
    cin >> cmd;
    auto find = func.find(cmd);
    if (find != func.end()) {find->second();}
    else { cerr << "Wrong command" << endl; }
}

void Controller::defaultSize() {
    view.set_default();
}

void Controller::set_size() {
    unsigned int s = 0;
    if (!cin >> s) {cerr << "Invalid size" << endl; return;}
    view.set_size(s);
}

void Controller::set_zoom() {
    unsigned int nm = 0;
    if (!cin >> nm) {cerr << "Not enough arguments " << endl; return;}
    view.set_scale(nm);
}

void Controller::set_pan() {
    double x=0, y=0;
    if (!(cin >> x) || !(cin >> y)) {cerr << "Not enough arguments " << endl; return;}
     view.set_origin(x, y);
}

void Controller::show() const {
    view.draw();
}

void Controller::status() const {
    Model::get_instance().describe();
}


void Controller::go() const {
    Model::get_instance().update();
}

//TODO - take care for () - in position and in create
void Controller::create_s() const{
    string args[7];
    int i = 0;
    while (i < 7 && cin >> args[i]) {
        i++;}
    if (i < 6) {cerr<<"not enough arguments "<<endl; return;}

    Data d = {args[0], 0.0, 0.0,  40,
        Point(stod(args[2]), stod(args[3])),ShipState::STOPPED};

    if (args[1] == "Freighter") {
        if (i!=7){cerr<<"not enough arguments "<<endl; return;}
        Model::get_instance().create_freighter_ship(d, FREIGHTER_MAX_FUEL, FREIGHTER_MAX_FUEL, FREIGHTER_CONSUMPTION, stod(args[5]), stoi(args[6]), 0);
    }
    else if (args[1] == "Cruiser") {
        if (i!=7){cerr<<"not enough arguments "<<endl; return;}
        d.max_speed = CRUISER_MAX_SPEED;
        Model::get_instance().create_pirate_ship(d,stod(args[6]),stod(args[5]));
    }
    else if (args[1] == "Patrol") {
        if (i!=6){cerr<<"not enough arguments "<<endl; return;}
        d.max_speed = PATROL_MAX_SPEED;
        Model::get_instance().create_patrol_ship(d,PATROL_MAX_FUEL,PATROL_MAX_FUEL,PATROL_CONSUMPTION,stod(args[5]));
    }
    else{cerr << "There is no ship like that! bye"<<endl; return;}
}

void Controller::set_course(const string &ship_name) {
    double angle, speed;
    if (!(cin >> angle >> speed)) {cerr<<"not enough arguments "<<endl; return;}
    Model::get_instance().course(ship_name, angle,speed);
}

void Controller::set_position(const string& ship_name) {
    // intentionally left as requested //TODO
    (void)ship_name;
}

void Controller::set_destination(const string& ship_name) {
    string port_name;
    double speed = 0.0;
    if (!(cin >> port_name >> speed)) {cerr << "not enough arguments " << endl; return;}
    Model::get_instance().destination(ship_name, port_name, speed);
}

void Controller::load_at(const string& ship_name) {
    string port_name;
    if (!(cin >> port_name)) {cerr << "not enough arguments " << endl; return;}
    Model::get_instance().load_at(ship_name, port_name);
}

void Controller::unload_at(const string& ship_name) {
    string port_name;
    int amount = 0;
    if (!(cin >> port_name >> amount)) {cerr << "not enough arguments " << endl; return;}
    Model::get_instance().unload_at(ship_name, port_name, amount);
}

void Controller::dock_at(const string& ship_name) {
    string port_name;
    if (!(cin >> port_name)) {cerr << "not enough arguments " << endl; return;}
    Model::get_instance().dock_at(ship_name, port_name);
}

void Controller::attack(const string& ship_name) {
    string target_ship;
    if (!(cin >> target_ship)) {cerr << "not enough arguments " << endl; return;}
    Model::get_instance().attack(ship_name, target_ship);
}

void Controller::refuel(const string& ship_name) {
    Model::get_instance().refuel(ship_name);
}

void Controller::stop(const string& ship_name) {
    Model::get_instance().stop(ship_name);
}

