
#ifndef EX3_GEOMETRY_H
#define EX3_GEOMETRY_H

#include <iostream>
#include <iomanip>
using namespace std;
//TODO - need to check conversions from 0 to 90
// angle units conversion functions
double to_radians(double theta_d);
double to_degrees(double theta_r);

// class declarations
typedef struct Point {
    double x;
    double y;
    Point(double x, double y);
    Point();
    void print() const;
    bool operator==(const Point& rhs) const;
    friend ostream& operator<<(ostream& o, const Point& p);
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

/*
*Point calculate_next_pos(Point start, double angle_rad, double speed) {
    // 1. Convert the input angle to the system's radian format
    // WARN: Current to_radians logic implies 0 deg = South (-y axis)


    // 2. Create a polar vector for the movement
    // Since time is exactly 1 hour, distance = speed * 1
    Polar_vector move_vector;
    move_vector.r = speed;
    move_vector.theta = angle_rad;

    // 3. Convert to Cartesian to get x/y offsets
    Cartesian_vector delta(move_vector);

    // 4. Apply the offset to the starting point
    Point next_p;
    next_p.x = start.x + delta.delta_x;
    next_p.y = start.y + delta.delta_y;

    return next_p;
}
 */