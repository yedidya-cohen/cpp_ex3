#include "Controller.h"

using namespace std;

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
        else {
            if (line.size() > 12) {
                cerr << "Invalid ship name: must be at most 12 characters" << endl;
                continue;
            }
            ship_commands(line);
        }

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

void Controller::create_s() const{
    // Expected formats:
    // create <name> Patrol (<x>,<y>) <resistance>
    // create <name> Freighter (<x>,<y>) <resistance> <capacity>
    // create <name> Cruiser (<x>,<y>) <attack_force> <range>
    string name, kind;
    char lparen = '\0', comma = '\0', rparen = '\0';
    double x = 0.0, y = 0.0, res_or_force = 0.0;
    int optional = 0;

    if (!(cin >> name >> kind >> lparen >> x >> comma >> y >> rparen >> res_or_force)) {
        cerr << "not enough arguments " << endl;
        return;
    }

    if (name.size() > 12) {
        cerr << "Invalid ship name: must be at most 12 characters" << endl;
        return;
    }

    if (lparen != '(' || comma != ',' || rparen != ')') {
        cerr << "bad coordinate format, expected (<x>,<y>)" << endl;
        return;
    }

    Data d = {name, 0.0, 0.0, FREIGHTER_MAX_SPEED, Point(x, y), ShipState::STOPPED};

    if (kind == "Patrol") {
        d.max_speed = PATROL_MAX_SPEED;
        Model::get_instance().create_patrol_ship(
            d, PATROL_MAX_FUEL, PATROL_MAX_FUEL, PATROL_CONSUMPTION, res_or_force
        );
        return;
    }

    if (!(cin >> optional)) {
        cerr << "not enough arguments " << endl;
        return;
    }

    if (kind == "Freighter" || kind == "Freigther") {
        Model::get_instance().create_freighter_ship(
            d, FREIGHTER_MAX_FUEL, FREIGHTER_MAX_FUEL, FREIGHTER_CONSUMPTION, res_or_force, optional, 0
        );
    }
    else if (kind == "Cruiser") {
        d.max_speed = CRUISER_MAX_SPEED;
        Model::get_instance().create_pirate_ship(d, optional, res_or_force);
    }
    else {
        cerr << "There is no ship like that! bye" << endl;
    }
}

void Controller::set_course(const string &ship_name) {
    double angle, speed;
    if (!(cin >> angle >> speed)) {cerr<<"not enough arguments "<<endl; return;}
    Model::get_instance().course(ship_name, angle,speed);
}

void Controller::set_position(const string& ship_name) {
    // Expected format after "<ship> position": (<x>,<y>) <speed>
    char lparen = '\0', comma = '\0', rparen = '\0';
    double x = 0.0, y = 0.0, speed = 0.0;
    if (!(cin >> lparen >> x >> comma >> y >> rparen >> speed)) {
        cerr << "not enough arguments " << endl;
        return;
    }
    if (lparen != '(' || comma != ',' || rparen != ')') {
        cerr << "bad coordinate format, expected (<x>,<y>)" << endl;
        return;
    }
    Point p(x, y);
    string ship = ship_name;
    Model::get_instance().position(ship, p, speed);
}

void Controller::set_destination(const string& ship_name) {
    string port_name;
    double speed = 0.0;
    if (!(cin >> port_name >> speed)) {cerr << "not enough arguments " << endl; return;}
    string ship = ship_name;
    Model::get_instance().destination(ship, port_name, speed);
}

void Controller::load_at(const string& ship_name) {
    string port_name;
    if (!(cin >> port_name)) {cerr << "not enough arguments " << endl; return;}
    string ship = ship_name;
    Model::get_instance().load_at(ship, port_name);
}

void Controller::unload_at(const string& ship_name) {
    string port_name;
    int amount = 0;
    if (!(cin >> port_name >> amount)) {cerr << "not enough arguments " << endl; return;}
    string ship = ship_name;
    Model::get_instance().unload_at(ship, port_name, amount);
}

void Controller::dock_at(const string& ship_name) {
    string port_name;
    if (!(cin >> port_name)) {cerr << "not enough arguments " << endl; return;}
    string ship = ship_name;
    Model::get_instance().dock_at(ship, port_name);
}

void Controller::attack(const string& ship_name) {
    string target_ship;
    if (!(cin >> target_ship)) {cerr << "not enough arguments " << endl; return;}
    string ship = ship_name;
    Model::get_instance().attack(ship, target_ship);
}

void Controller::refuel(const string& ship_name) {
    string ship = ship_name;
    Model::get_instance().refuel(ship);
}

void Controller::stop(const string& ship_name) {
    string ship = ship_name;
    Model::get_instance().stop(ship);
}
