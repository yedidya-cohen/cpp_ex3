
#ifndef EX3_VIEW_H
#define EX3_VIEW_H


#include "Geometry.h"
#include "Model.h"

class View {
public:
    View(int grid,double scale,Point org);
    void draw() const;
    void set_size(int size);
    void set_scale(int sc);
    void set_origin(double x, double y);
    void set_default();

private:
    int grid_size;
    double scale;
    Point origin;
};


#endif //EX3_VIEW_H
