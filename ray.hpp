#pragma once
#include "vec3.hpp"

class Ray{
    public:
    Point3 origin;
    Vec3 direction;
    Ray(Point3 o,Vec3 dir) : origin(o), direction(dir){}
    Ray():origin(Point3()),direction(Vec3()){}
    Point3 at(double t) const{
        return origin+direction*t;
    }
};