#ifndef EX3_VIEW_H
#define EX3_VIEW_H

#include "Geometry.h"

//this class responsible how to view the map - can create another and pass it to the controller
class View {
public:

    View(int grid,double scale,Point org);
    //draw the map how ever you want
    void draw() const;
    //size of the map
    void set_size(int size);
    //scale - for asciis
    void set_scale(int sc);
    //what is the 0,0 point
    void set_origin(double x, double y);
    //return to default
    void set_default();

private:
    int grid_size;
    double scale;
    Point origin;
    constexpr static int grid_max = 30;
    constexpr static  int grid_min = 6;
};


#endif //EX3_VIEW_H
