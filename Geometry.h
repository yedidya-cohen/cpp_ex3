
#ifndef EX3_GEOMETRY_H
#define EX3_GEOMETRY_H

#include <iostream>
#include <iomanip>


// angle units conversion functions
double to_radians(double theta_d);
double to_degrees(double theta_r);

// class declarations
//was given in the class
typedef struct Point {
    double x;
    double y;
    Point(double x, double y);
    Point();
    void print() const;
    bool operator==(const Point& rhs) const;
    friend std::ostream& operator<<(std::ostream& o, const Point& p);
} Point;

double dist(const Point& p1,const Point& p2);

struct Polar_vector;
typedef struct Cartesian_vector {
    Cartesian_vector(const struct Polar_vector & pv);
    Cartesian_vector();
    void operator=(const struct Polar_vector & pv);
    double delta_x;
    double delta_y;
} Cartesian_vector;

typedef struct Polar_vector {
    Polar_vector(const Cartesian_vector & cv);
    Polar_vector();
    void operator=(const Cartesian_vector & cv);
    double r;
    double theta;
} Polar_vector;

Point calculate_next_pos(Point start, double angle_rad, double speed);
#endif //EX3_GEOMETRY_H
