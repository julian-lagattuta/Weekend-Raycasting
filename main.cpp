#include <iostream>
#include <fstream>
#include "vec3.hpp"
#include "raycast.hpp"

int main() {

    render();
    return 0;
using namespace std;

    // Image
    ofstream f;
    f.open("out.ppm");
    const int image_width = 256;
    const int image_height = 259;

    // Render

    f << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
            auto r = double(i) / (image_width-1);
            auto g = double(j) / (image_width-1);
            auto b = 0.25;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            f << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }
    f.close();
}