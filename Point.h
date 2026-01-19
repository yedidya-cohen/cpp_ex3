#ifndef EX3_POINT_H
#define EX3_POINT_H

class Point
{
public:

    Point(double x, double y): x(x), y(y) {}
    double get_x() const {return x;}
    double get_y() const {return y;}


private:
    double x, y;
};

#endif