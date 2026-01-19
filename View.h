//
// Created by yedid on 19/01/2026.
//

#ifndef EX3_VIEW_H
#define EX3_VIEW_H


#include "Point.h"

class View {
    View(int grid,double scale,Point org);
    void draw() const:
    void set_size();
    void set_scale();
    void set_origin();
    void set_default();
private:
    int grid_size;
    double scale;
    Point origin;

};


#endif //EX3_VIEW_H
