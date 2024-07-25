#include <iostream>
#include <fstream>
#include <complex>

using namespace std;

// Function to compute the number of iterations for a given point
int isInSet(complex<double> c, int max_iter, double threshold) {
    complex<double> z = (0, 0); //complex number z, used in the formula
    int iter; //iterations of the formula
    for (iter = 0; iter < max_iter; iter++) {
        if (abs(z) > threshold)
            break; 
        //if z is exceeding threshold, c is not in mandelbrot set
        //either way, we memorize iterations, which tell how quickly z converges to infinity
        //else, when iterations are done enough times (max_iter), the cycle will end naturally

        z = z * z + c; //the formula
    }
    return iter;
}

void generateMandelbrotSerial(int width, int height, int max_iter, double threshold, double x_min, double x_max, double y_min, double y_max) {
    ofstream file("mandelbrot_serial.ppm"); //initialize the file
    file << "P3\n" << width << " " << height << "\n255\n";

    for (int y = 0; y < height; y++) { //for each pixel on y axis
        for (int x = 0; x < width; x++) { //for each pixel on x axis
            double real = x_min + (x_max - x_min) * x / (width - 1); //x axis is the real part and y axis is the imaginary part
            double imag = y_min + (y_max - y_min) * y / (height - 1); //calculated as a pixel with current width and height rather than numbers on the number line
            complex<double> c(real, imag);

            int iter = isInSet(c, max_iter, threshold); //seeing if we count the number as in the set
            int color = 255 - (255 * iter / max_iter); //calculating the color based on how quickly it converges to infinity

            file << color << " " << color << " " << color << " "; //add the colored pixels to the image
        }
        file << "\n"; //go to the next line when done with one (on the x axis)
    }
    file.close();
}

int main() {
    int width = 800; //width of the image
    int height = 600; //height of the image
    int max_iter = 35; //iterations threshold. if we reach this, we count z as a part of the set (not converging to infinity with the formula)
    double threshold = 2.0; //if abs(z) exceeds this, then we count it as converging to infinity
    double x_min = -2.0, x_max = 2.0; //x axis boundaries for numbers (smallest and biggest number on the line that is going to be drawn)
    double y_min = -2.0, y_max = 2.0; //y axis boundaries for numbers

    generateMandelbrotSerial(width, height, max_iter, threshold, x_min, x_max, y_min, y_max);

    cout << "Mandelbrot set image generated in 'mandelbrot_serial.ppm'" << endl;
    return 0;
}