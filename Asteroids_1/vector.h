#ifndef VECTOR_H
#define VECTOR_H

#include <iosfwd>

namespace Phys
{

// NOTE THAT CLASS USES RADIANS AtTheMoment. write inline method for conversion?
// CHECK implementation for set r.
// add empty line below declaration of method within access specifier public/etc.?
// Add operators!

class Vector
{
private:
    const static double THETA_MIN, THETA_MAX;
    double x,y,r,theta;
    static double getR(const int &x, const int &y);
    static double getTheta(const int &x, const int &y);
    static double getRandom(const double &min, const double &max);
public:
    Vector();
    Vector(const double &x, const double &y);
    static Vector* createPolar(const double &r, const double &theta);
    static Vector* createRandomAngle(const double &r);
    Vector* getReversed();
    double getX() const {return x;}
    double getY() const {return y;}
    double getR() const {return r;}
    double getTheta() const {return theta;}
    void setX(const double &x);
    void setY(const double &y);
    void setR(const double &r);
    void setTheta(const double &theta);
};

} //namespace Phys

std::ostream &operator<<(std::ostream &os, const Phys::Vector &vector);

#endif // VECTOR_H
