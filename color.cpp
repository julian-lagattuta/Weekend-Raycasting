#include "color.hpp"
void write_color(std::ostream& out,Color v){
    double r = v.e[0];
    double g = v.e[1];
    double b = v.e[2];    
    r=sqrt(r);
    g=sqrt(g);
    b=sqrt(b);
    out<<static_cast<int>(255.999*r)<<' '<<static_cast<int>(255.999*g)<<' '<<static_cast<int>(255.999*b)<<'\n' ;
}