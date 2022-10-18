#include "hittable.hpp"
#include "vec3.hpp"
bool Sphere::hit(const Ray& r,double tmin,double tmax,HitRecord& rec) const{
    double a = dot(r.direction,r.direction);
    double b=  2*dot(r.direction,r.origin-center);
    double c=  (r.origin-center).length_squared()-radius*radius;
    double d = b*b-4.0*a*c;
    if(d<0)
        return false;

    double sqrt_d = sqrt(d);
    double t= (-b-sqrt_d)/(2.0*a);
    if(t<tmin || t>tmax){
        t= (-b+sqrt_d)/(2.0*a);
        if(t<tmin||t>tmax)
            return false;
    }
    rec.t =t;
    rec.point=r.at(t);
    rec.setNormalFace(r,(rec.point-center)/radius);
    rec.mat = mat;
    return true;
}
bool HittableList::hit(const Ray& r,double tmin,double tmax,HitRecord& rec) const{
    HitRecord br;
    double closest=tmax;
    bool found = false;
    for(int i =0;i<objects.size();i++){
        HitRecord t;
        if(!objects[i]->hit(r,tmin,tmax,t))
            continue;
        found=true;
        if(closest>t.t){
            closest = t.t;
            br=t;
        }
    }
    if(found){
        rec=br;
        return true;
    }
    return false;
}

void HittableList::clear(){
    objects.clear();
}
void HittableList::add(shared_ptr<Hittable> o){
    objects.push_back(o);
}

bool Lambertian::scatter(Ray& inr,HitRecord& inrec,Color& color_out,Ray& ray_out) const {
    Vec3 dir = inrec.normal+randomSpherePoint().normalized();
    if(dir.closeToZero())
        dir = inrec.normal;
    
    ray_out= Ray(inrec.point,dir);
    color_out = color;
    return true;
}
bool Metal::scatter(Ray& inr,HitRecord& inrec,Color& color_out,Ray& ray_out) const {
    Vec3 dir = (inr.direction.reflect(inrec.normal)+(fuzziness==0 ? Vec3(0,0,0) : fuzziness*randomSpherePoint()));
    
    ray_out= Ray(inrec.point,dir);
    color_out =color;
    return true;
}

bool Refractor::scatter(Ray& inr,HitRecord& inrec,Color& color_out,Ray& ray_out) const {
    color_out = Color(1.0, 1.0, 1.0);
    
    double ratio = inrec.front? 1.0/refraction_ratio : refraction_ratio;
    ray_out= Ray(inrec.point, inr.direction.refract(inrec.normal,ratio));
    return true;
}