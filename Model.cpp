#include "Model.h"

#include <string>
#include "Geometry.h"

void Model::update() {
    for (auto& s: ships){s.update();}
    for (auto& p: pirates){p.update();}
    for (auto& p: ports){p.update();}

}

void Model::sort_by_print() {
    auto print_order = [](const auto& a, const auto& b) {
        Point pa = a.get_position();
        Point pb = b.get_position();
        if (pa.y != pb.y) return pa.y > pb.y;  // Higher y first
        return pa.x < pb.x;  // Lower x first
    };

    // Use the same lambda for all sorts
    std::sort(pirates.begin(), pirates.end(), print_order);
    std::sort(ships.begin(), ships.end(), print_order);
    std::sort(ports.begin(), ports.end(), print_order);
}

void Model::status() {
    for (auto& s: ships){s.status();}
    for (auto& p: pirates){p.status();}
    for (auto& p: ports){p.status();}
}


bool Model::create_freighter_ship(const string& name, Point position, int resistance, int container_capacity) {
    if (is_civil_exists(name)) {
        cout << "Ship with name:" << name << "already exists \n";
        return false;
    }
    // TODO: create class of freighter - depens on lass
    ships.emplace_back(name, position, resistance, container_capacity);
    return true;
}

bool Model::create_patrol_ship(const string& name, Point position, int resistance) {
    if (is_civil_exists(name)) {
        cout << "Ship with name:" << name << "already exists \n";
        return false;
    }
    //TODO - depens on patrol c'tors
    ships.emplace_back(name, position, resistance);
    return true;
}

bool Model::create_pirate_ship(const string& name, Point position, int attack_force, int attack_range){
    if (is_pirate_exists(name)) {
        cout << "Ship with name:" << name << "already exists \n";
        return false;
    }
    //TODO - depens on C'tor of pirets!
    pirates.emplace_back(name, position, attack_force), attack_force;

}

bool Model::create_port(const string& name, Point position, int resistance, int container_capacity) {
    if (is_port_exists(name)) {
        cout<< "Port with name:" << name << "already exists \n";
        return false;
    }
    //TODO -depens on C'tor of ports!
    ports.emplace_back(name, position, resistance, container_capacity);
}

bool Model::is_civil_exists(const string &o){
    for (auto& s:ships) {
        if (s.get_name() == o) {return true;}
    }
    return false;
}

bool Model::is_pirate_exists(const string &o) {
    for (auto& s: pirates)
    {
        if (s.get_name() == o) {return true;}
    }
    return false;
}

bool Model::is_port_exists(const string &o) {
    for (auto& s: ports)
    {
        if (s.get_name()==o){return true;}
    }
    return false;
}