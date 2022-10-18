#pragma once
#include <ostream>
#include <cmath>
class Vec3{
public:
    double e[3];
    inline double x(){return e[0];};
    inline double y(){return e[1];};
    inline double z(){return e[2];};
    Vec3():e{0,0,0}{};
    Vec3(double X, double Y, double Z) : e{X,Y,Z} {};

    double length() const { 
        using std::sqrt;
        return sqrt(e[0]*e[0]+e[1]*e[1]+e[2]*e[2]);
    }
    double length_squared() const {
        return e[0]*e[0]+e[1]*e[1]+e[2]*e[2];
    }
    Vec3& operator+=(const Vec3& o){
        e[0]+=o.e[0];
        e[1]+=o.e[1];
        e[2]+=o.e[2];
        return *this;
    }

    Vec3& operator-=(const Vec3& o){
        e[0]-=o.e[0];
        e[1]-=o.e[1];
        e[2]-=o.e[2];
        return *this;
    }
    Vec3& operator*=(const double m){
        e[0]*=m;
        e[1]*=m;
        e[2]*=m;
        return *this;
    }
    Vec3& operator/=(const double m){
        e[0]/=m;
        e[1]/=m;
        e[2]/=m;
        return *this;
    }
    Vec3 operator-()const {
        Vec3 c = *this;
        c.e[0]*=-1;
        c.e[1]*=-1;
        c.e[2]*=-1;
        return c;
    }
    Vec3 normalized();
    Vec3 reflect(Vec3 o);
    bool closeToZero();
    Vec3 refract(Vec3 n, double o_over_e);
};
using Point3 = Vec3;
inline std::ostream& operator<<(std::ostream& o, const Vec3 &v) {
    return o<<"("<<v.e[0]<<", "<<v.e[1]<<", "<<v.e[2]<<")";
}
inline Vec3 operator+(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

inline Vec3 operator-(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline Vec3 operator*(const Vec3 &u, const Vec3 &v) {
    return Vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline Vec3 operator*(double t, const Vec3 &v) {
    return Vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline Vec3 operator*(const Vec3 &v, double t) {
    return t * v;
}

inline Vec3 operator/(Vec3 v, double t) {
    return (1/t) * v;
}
inline double dot(const Vec3& a,const Vec3& b){

    return a.e[0]*b.e[0]+a.e[1]*b.e[1]+a.e[2]*b.e[2];
}
inline Vec3 cross(const Vec3& a,const Vec3& b){

    return Vec3(a.e[1]*b.e[2]-a.e[2]*b.e[1],
               a.e[2]*b.e[0]-a.e[0]*b.e[2],
               a.e[0]*b.e[1]-a.e[1]*b.e[0]);
}

Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat);