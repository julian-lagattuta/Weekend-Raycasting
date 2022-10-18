#include "raycast.hpp"
#include <fstream>
#include <cmath>
#include <limits>
#include <cstdlib>
#include "util.hpp"
HittableList objectsInScene;


Color ray_color(Ray r,HittableList& table,int n){
    if(n<=0)
        return Color(0,0,0);
    
    using std::make_shared;
    
    HitRecord rec;
    
    if(table.hit(r,0.001,infinity,rec)){
        Color att;
        Ray outray;
        if(rec.mat->scatter(r,rec,att,outray))
            return  att*ray_color(outray,table,n-1);
        printf("returned false");
        return Color(0,0,0);

    }
    // cout<<r.direction<<endl;
    // double by = 
    double t= (r.direction.normalized().y()/2+.5);
    return (1.0-t)*Color(1,1,1)+t*Color(0.5,0.7,1.0);
}
using std::make_shared;
using std::ofstream;
void render(){    

    auto glass = make_shared<Refractor>(1.5);
    auto mat = make_shared<Lambertian>(Color(.8,.8,0));
    auto met = make_shared<Metal>(Color(.8,.6,.2),1);
    // auto s = make_shared<Sphere>(Point3(0,0,-1),.5,met);
    // objectsInScene.add(s);
// 
    // auto s2 =make_shared<Sphere>(Point3(0,-100.5,-1), 100,mat);
    // objectsInScene.add(s2);
    // objectsInScene.add(make_shared<Sphere>(Point3(1.2,.1,-1.3),.4,glass));
    // objectsInScene.add(mak)

    objectsInScene.add(make_shared<Sphere>(Point3( 0.0, -100.5, -1.0), 100.0,mat));
    objectsInScene.add(make_shared<Sphere>(Point3( 0.0,    0.0, -1.0),   0.5,mat));
    objectsInScene.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),   0.5, glass));
    objectsInScene.add(make_shared<Sphere>(Point3(-1.0,    0.0, -1.0),  -0.4, glass));
    objectsInScene.add(make_shared<Sphere>(Point3( 1.0,    0.0, -1.0),   0.5, met));
    int width = 400;
    const auto ratio = 16.0 / 9.0;
    int height = static_cast<int>(width / ratio);
    Camera cam = Camera(90,ratio,Vec3(),Vec3(.5,.2,-1));

    auto antialiasing_level =10;

    ofstream f;
    f.open("out.ppm");

    f<<"P3\n"<<width<<" "<<height<<"\n255\n";
    for(int i =height-1;i>=0;i--){
        for(int j=0;j<width;j++){
            Color avg=Color();
            for(int k=0;k<antialiasing_level;k++){
                double y=double(i+random_double())/(height-1);  
                double x=double(j+random_double())/(width-1);
                Ray r= cam.getRay(x,y);
                avg+=ray_color(r,objectsInScene,50);
            }
            avg/=antialiasing_level;
            write_color(f,avg);
        }
        f<<'\n';

    }

}