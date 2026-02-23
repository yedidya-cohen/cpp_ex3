#include "Geometry.h"
#include <cmath>
#include <ctgmath>

using namespace std;

const double pi = 2. * atan2(1., 0.);
double to_radians(double theta_d) {
    theta_d = 90-theta_d;
    return theta_d * pi / 180.0;
}

double to_degrees(double theta_r)
{
    double d = 90 - (theta_r * 180.0 / pi);
    return d < 0 ? d + 360 : d;

}
// construct a Cartesian_vector from a Polar_vector
Cartesian_vector::Cartesian_vector(const Polar_vector& pv) {
    delta_x = pv.r * cos(pv.theta);
    delta_y = pv.r * sin(pv.theta);
}

Cartesian_vector::Cartesian_vector()
{
    delta_x = 0.0;
    delta_y = 0.0;
}
void Cartesian_vector::operator=(const Polar_vector& pv)
{
    delta_x = pv.r * cos(pv.theta);
    delta_y = pv.r * sin(pv.theta);
}
// construct a Polar_vector from a Cartesian_vector
Polar_vector::Polar_vector(const Cartesian_vector& cv) {
    r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
    /* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
    theta = atan2(cv.delta_y, cv.delta_x);
    if (theta < 0.)
        theta = 2. * pi + theta; // normalize theta positive
}
Polar_vector::Polar_vector()
{
    r = 0.0;
    theta = 0.0;
}
void Polar_vector::operator=(const Cartesian_vector& cv)
{
    r = sqrt((cv.delta_x * cv.delta_x) + (cv.delta_y * cv.delta_y));
    /* atan2 will return a negative angle for Quadrant III, IV, must translate to I, II */
    theta = atan2(cv.delta_y, cv.delta_x);
    if (theta < 0.)
        theta = 2. * pi + theta; // normalize theta positive
}

Point::Point(double x, double y) : x(x), y(y)
{
}

Point::Point()
{
    x = 0.0;
    y = 0.0;
}

void Point::print() const
{
    cout << setprecision(2) << "(" << x << ", " << y << ")";
}

bool Point::operator==(const Point & rhs) const {//nm
    return abs(x - rhs.x) < 0.1 && abs(y - rhs.y) < 0.1;
}

double dist(const Point& p1,const Point& p2) {
    const double dx = p2.x - p1.x;
    const double dy = p2.y - p1.y;
    return sqrt(dx*dx + dy*dy);
}

ostream& operator<<(ostream& o, const Point& p) {
    o << "(" << p.x << "," << p.y << ")";
    return o;
}

Point calculate_next_pos(Point start, double angle_rad, double speed) {


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