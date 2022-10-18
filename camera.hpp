#pragma once
#include "vec3.hpp"
#include "ray.hpp"
#include <cmath>
#include <iostream>
class Camera{
public:
    Camera(double fov_arg, double ratio, Point3 origin,Vec3 direction);
    Ray getRay(double x,double y);
    Point3 origin;
    Vec3 horizontal;
    Vec3 vertical;
    Point3 bottom_left;
    double ratio;
    double fov;
};