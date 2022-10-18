#include "Vec3.hpp"
#include "util.hpp"


Vec3 Vec3::normalized(){
    return *this/length();
}
Vec3 Vec3::reflect(Vec3 o){

    return (*this)-2*(dot(*this,o))*o;
}

bool Vec3::closeToZero(){
    double eps = 1e-8;
    return fabs(e[0])<eps && fabs(e[1])<eps && fabs(e[2])<eps;
}
Vec3 refract(const Vec3& uv, const Vec3& n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vec3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}

Vec3 Vec3::refract(Vec3 n, double o_over_e){
    Vec3 norm_dir = normalized();
    double costheta = fmin(dot(-norm_dir,n.normalized()),1.0);
    double sintheta = sqrt(1-costheta*costheta);
    auto r0 = (1-o_over_e)/(1+o_over_e);
    r0*=r0;
    if((r0+(1-r0)*pow(1-costheta,5))>random_double()){
        return reflect(n);
    }
    if(o_over_e*sintheta>1.0){
        return reflect(n);
    }
    Vec3 perp = o_over_e*(norm_dir+costheta*n.normalized());
    Vec3 parall = n.normalized()*(-sqrt(fabs(1.0-perp.length_squared())));
    return perp+parall;
}