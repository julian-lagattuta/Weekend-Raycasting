#include "camera.hpp"

Camera::Camera(double fov_degrees, double rratio, Point3 orig,Vec3 direction){
    using namespace std;
    fov = fov_degrees/57.29578;
    origin =orig;
    auto viewport_height = 2.0*tan(fov/2);
    auto viewport_width = viewport_height*rratio;

    horizontal = cross(direction,Vec3(0,1,0)).normalized()*viewport_width;

    vertical = cross(horizontal,direction).normalized()*viewport_height;
    double focal_length = 1.0;
    bottom_left = origin-horizontal/2-vertical/2-Vec3(0,0,focal_length);
    ratio = rratio;
}
Ray Camera::getRay(double x,double y){
    return Ray(origin,bottom_left+horizontal*x+vertical*y-origin);
}