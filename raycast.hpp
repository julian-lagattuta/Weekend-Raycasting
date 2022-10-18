#pragma once
#include "camera.hpp"
#include "raycast.hpp"
#include "hittable.hpp"
#include "vec3.hpp"
#include "color.hpp"
#include "ray.hpp"
Color ray_color(Ray r,HittableList& world,int n);
void render();