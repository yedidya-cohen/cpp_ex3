#include "View.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

View::View(int grid, double sc, Point org) : grid_size(grid), scale(sc), origin(org) {}

void View::set_size(int size) {
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

void View::draw() const {
    cout << "Display size: " << grid_size << ", scale: " << fixed << setprecision(2) << scale << ", origin: ";
    origin.print();
    cout << endl;

    // Initialize grid with ". "
    vector<vector<string>> grid(grid_size, vector<string>(grid_size, ". "));

    auto& model = Model::get_instance();
    
    // Helper to mark entities on grid
    auto mark_on_grid = [&](const string& name, Point p) {
        int ix = static_cast<int>(floor((p.x - origin.x) / scale));
        int iy = static_cast<int>(floor((p.y - origin.y) / scale));

        if (ix >= 0 && ix < grid_size && iy >= 0 && iy < grid_size) {
            grid[iy][ix] = name.substr(0, 2);
        }
    };

    // We need access to the vectors in Model. 
    // Assuming Model provides accessors or we use the logic from Model::status/update
    // Since Model.h shows private vectors, in a real scenario we'd need getters.
    // For this implementation, we follow the pattern of mapping entities.
    
    // Note: The actual iteration over ships/pirates/ports requires Model to expose them.
    // Based on Model.h, they are private. Assuming friend class or getters exist:
    // For the sake of completing the View logic:

    for (const auto& s : model.get_ships()) {
        if (const auto l = s.lock()){mark_on_grid(l->get_name(), l->get_position());}
    }
    for (const auto& p : model.get_pirates()) {
        if (const auto l  = p.lock() ){ mark_on_grid(l->get_name(), l->get_position());}
    }

    for (const auto& po : model.get_ports()) {
        if (const auto l = po.lock()) {mark_on_grid(l->get_name(), l->get_position());}
    }


    // Drawing the grid from top (max Y) to bottom
    for (int j = grid_size - 1; j >= 0; --j) {
        if (j % 3 == 0) {
            cout << setw(4) << left << static_cast<int>(origin.y + j * scale);
        } else {
            cout << "    ";
        }
        for (int i = 0; i < grid_size; ++i) {
            cout << grid[j][i];
        }
        cout << endl;
    }

    // Drawing X axis labels
    cout << "    ";
    for (int i = 0; i < grid_size; ++i) {
        if (i % 3 == 0) {
            cout << setw(6) << left << static_cast<int>(origin.x + i * scale);
        }
    }
    cout << endl;
}
