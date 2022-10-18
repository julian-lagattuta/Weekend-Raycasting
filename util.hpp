#pragma once
#include "vec3.hpp"
#include <cmath>
#include <limits>
#include <cstdlib>
double random_double();
double random_double(double min,double max);

Point3 randomSpherePoint();
const double infinity = std::numeric_limits<double>::infinity();