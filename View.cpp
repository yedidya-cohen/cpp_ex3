#include "View.h"
#include "CivilianShip.h"
#include "Cruiser.h"
#include "Port.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include "Model.h"

using namespace std;

View::View(int grid, double sc, Point org) : grid_size(grid), scale(sc), origin(org) {}


void View::set_size(int size) { //setting size of view between 6 to 30
    if (size>grid_max || size< grid_min){cerr<<"wrong size, should be between 6 and 30\n"; return;}
    grid_size = size;
}

void View::set_scale(int sc) {
    scale = sc;
}

void View::set_origin(double x, double y) {
    origin = Point(x, y);
}

void View::set_default() {
    grid_size = 25;
    scale = 2.0;
    origin = Point(0, 0);
}
//main function of view
void View::draw() const {
    cout << "Display size: " << grid_size << ", scale: " << fixed << setprecision(2) << scale << ", origin: ";
    origin.print();
    cout << endl;

    // Initialize grid with ". "
    vector<vector<string>> grid(grid_size, vector<string>(grid_size, ". "));
    //for convient
    auto& model = Model::get_instance();
    
    // helper to mark entities on grid - lambda very good
    auto mark_on_grid = [&](const string& name, Point p) {
        int ix = static_cast<int>(floor((p.x - origin.x) / scale));
        int iy = static_cast<int>(floor((p.y - origin.y) / scale));

        if (ix >= 0 && ix < grid_size && iy >= 0 && iy < grid_size) {
            grid[iy][ix] = name.substr(0, 2);
        }
    };

    //take all the ships,port from model who is singleTone
    //each ship mark it based on the lambda we did before
    for (const auto& s : model.get_ships()) {
        if (const auto l = s.lock()){mark_on_grid(l->get_name(), l->get_position());}
    }
    for (const auto& p : model.get_pirates()) {
        if (const auto l  = p.lock() ){ mark_on_grid(l->get_name(), l->get_position());}
    }

    for (const auto& po : model.get_ports()) {
        if (const auto l = po.lock()) {mark_on_grid(l->get_name(), l->get_position());}
    }


    // Drawing the grid from top to bottom
    for (int j = grid_size - 1; j >= 0; --j) {
        if (j % 3 == 0) {
            cout << setw(4) << left << static_cast<int>(origin.y + j * scale); //padding
        } else {
            cout << "    ";
        }
        //cout the ship/'.'
        for (int i = 0; i < grid_size; ++i) {
            cout << grid[j][i];
        }
        cout << endl;
    }

    // Drawing x labels
    cout << "    ";
    for (int i = 0; i < grid_size; ++i) {
        if (i % 3 == 0) {
            cout << setw(6) << left << static_cast<int>(origin.x + i * scale); //padding
        }
    }
    cout << endl;
}
