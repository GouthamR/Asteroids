#ifndef VECTOR_H
#define VECTOR_H

#include <iosfwd>

namespace Phys
{

// Note: this class uses RADIANS, not degrees.
class Vector
{
private:
    const static double THETA_MIN, THETA_MAX;

    double r; // magnitude
    double t; // theta, angle

    static double getR(const double &x, const double &y);
    static double getT(const double &x, const double &y);
public:
    const static double THETA_QUARTER, THETA_RIGHT, THETA_UP, THETA_LEFT, THETA_DOWN;

    Vector();
    Vector(const double &x, const double &y);
    static Vector* createPolar(const double &magnitude, const double &angle);
    Vector &operator += (const Vector &other);
    double getX() const;
    double getY() const;
    double getR() const;
    double getTheta() const;
    void setX(const double &x);
    void setY(const double &y);
    void setR(const double &r);
    void setTheta(const double &theta);
};

} //namespace Phys

std::ostream &operator<<(std::ostream &os, const Phys::Vector &vector);

#endif // VECTOR_H
