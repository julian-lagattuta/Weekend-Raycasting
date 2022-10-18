#include "util.hpp"

double random_double(){
    return rand()/(RAND_MAX+1.0);
}

double random_double(double min,double max){
    return min+random_double()*(max-min);
}
Point3 randomSpherePoint(){
    Vec3 p;
    while(  (p= Vec3(random_double(-1,1),random_double(-1,1),random_double(-1,1))).length_squared()>=1 ); 
    return p;
}
