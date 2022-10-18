
#include <vector>
#include <memory>
#include <iostream>
#include "ray.hpp"
#include "vec3.hpp"
#include "util.hpp"
#include "color.hpp"
using std::shared_ptr;
using std::vector;
struct HitRecord;
class Material{
    public:
    virtual bool scatter(Ray& inr,HitRecord& inrec,Color& color_out,Ray& ray_out) const=0;

};
struct HitRecord{
    Point3 point;
    Vec3 normal;
    double t;
    bool front;
    shared_ptr<Material> mat;
    void setNormalFace(const Ray& r,const Vec3 n){
        if(dot(r.direction,n)<0){
            front = true;
            normal =n;
            return;
        }
        
        front = false;
        normal = -n;
    }
};

class Hittable{
    public:

    virtual bool hit(const Ray& r,double tmin,double tmax,HitRecord& rec) const = 0;

};

class Sphere: public Hittable{
 public:
    Point3 center;
    double radius;
    Sphere(Point3 c, double r,shared_ptr<Material> m):mat(m), center(c), radius(r){}
    bool hit(const Ray& r,double tmin,double tmax,HitRecord& rec) const;
    shared_ptr<Material> mat;
};
class HittableList{
    public:
        HittableList(){}
        void add(shared_ptr<Hittable> o);
        void clear();
        bool hit(const Ray& r,double tmin,double tmax,HitRecord& rec) const;
        vector<shared_ptr<Hittable>> objects;
};



class Lambertian: public Material{
    public:
    virtual bool scatter(Ray& inr,HitRecord& inrec,Color& color_out,Ray& ray_out) const override;
    Lambertian(Color c): color(c){};
    Color color;
};

class Metal : public Material{
    public:
    virtual bool scatter(Ray& inr,HitRecord& inrec,Color& color_out,Ray& ray_out) const override;
    Metal(Color c,double fuzz):fuzziness(fuzz), color(c){};
    Color color;
    double fuzziness;
};

class Refractor : public Material{
public:
    virtual bool scatter(Ray& inr,HitRecord& inrec,Color& color_out,Ray& ray_out) const override;
    Refractor(double ratio): refraction_ratio(ratio){}
    double refraction_ratio;
};