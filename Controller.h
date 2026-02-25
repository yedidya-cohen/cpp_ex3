#ifndef EX3_CONTROLLER_H
#define EX3_CONTROLLER_H

#include "View.h"
#include "Model.h"



class Controller {
public:
    Controller(const View& v):view(v){}
    void simulate(); // main loop for input

    void file_read_ports(const std::string& file_name); // reading port file
private:
    //defaults for constructors of the ships
    static constexpr double FREIGHTER_MAX_SPEED = 40.0;
    static constexpr double FREIGHTER_MAX_FUEL = 500000.0;
    static constexpr double FREIGHTER_CONSUMPTION = 1000.0;

    static constexpr double CRUISER_MAX_SPEED = 75.0;

    static constexpr double PATROL_MAX_SPEED = 15.0;
    static constexpr double PATROL_MAX_FUEL = 900000.0;
    static constexpr double PATROL_CONSUMPTION = 2000.0;


    void ship_commands(const std::string& ship_name); // for commands 

    //Model
    void status() const;
    void go() const;
    void create_s() const;

    //View
    void defaultSize();
    void set_size();
    void set_zoom();
    void set_pan();
    void show() const;

   //ships
    void set_course(const std::string &ship_name);
    void set_position(const std::string& ship_name);
    void set_destination(const std::string& ship_name);
    void load_at(const std::string& ship_name);
    void unload_at(const std::string& ship_name);
    void dock_at(const std::string& ship_name);
    void attack(const std::string& ship_name);
    void refuel(const std::string& ship_name);
    void stop(const std::string& ship_name);

    View view;
};


#endif //EX3_CONTROLLER_H
