#include <iostream>
#include <fstream>
#include <complex>

using namespace std;

// Function to compute the number of iterations for a given point
int mandelbrot(complex<double> c, int max_iter) {
    complex<double> z = 0;
    int iter;
    for (iter = 0; iter < max_iter; ++iter) {
        if (abs(z) > 2.0) break;
        z = z * z + c;
    }
    return iter;
}

void generateMandelbrotSerial(int width, int height, int max_iter, double x_min, double x_max, double y_min, double y_max) {
    ofstream file("mandelbrot_serial.ppm");
    file << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double real = x_min + (x_max - x_min) * x / (width - 1);
            double imag = y_min + (y_max - y_min) * y / (height - 1);
            complex<double> c(real, imag);
            int iter = mandelbrot(c, max_iter);

            int color = 255 - (255 * iter / max_iter);

            //int color = (iter == max_iter) ? 0 : 255 * iter / max_iter;
            file << color << " " << color << " " << color << " ";
        }
        file << "\n";
    }
    file.close();
}

int main() {
    int width = 800;
    int height = 600;
    int max_iter = 1000;
    double x_min = -2.0, x_max = 2.0;
    double y_min = -2.0, y_max = 2.0;

    generateMandelbrotSerial(width, height, max_iter, x_min, x_max, y_min, y_max);

    cout << "Mandelbrot set image generated in 'mandelbrot_serial.ppm'" << endl;
    return 0;
}