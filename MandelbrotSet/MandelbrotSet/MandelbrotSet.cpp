#include <iostream>
#include <fstream>
#include <complex>
#include <omp.h>
#include <time.h>

using namespace std;

const int NUM_THREADS = 1;
const int width = 1000; //width of the image
const int height = 1000; //height of the image
const int max_iter = 35; //iterations threshold. if we reach this, we count z as a part of the set (not converging to infinity with the formula)
const double threshold = 5.0; //if abs(z) exceeds this, then we count it as converging to infinity
const double x_min = -2.0, x_max = 2.0; //x axis boundaries for numbers (smallest and biggest number on the line that is going to be drawn)
const double y_min = -2.0, y_max = 2.0; //y axis boundaries for numbers

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

void generateMandelbrotSet(int window_width, int window_height, int max_iter, double threshold, double x_min, double x_max, double y_min, double y_max) {
    ofstream file("mandelbrot_set.ppm"); //initialize the file
    file << "P3\n" << window_width << " " << window_height << "\n255\n";
    int colors[width];

    for (int y = 0; y < window_height; y++) { //for each pixel on y axis
#pragma omp parallel num_threads(NUM_THREADS)
        {
            for (int x = 0; x < window_width; x++) { //for each pixel on x axis

                //cout << "Number of threads used: " << omp_get_num_threads() << endl;

                double real = x_min + (x_max - x_min) * x / (window_width - 1); //x axis is the real part and y axis is the imaginary part
                double imag = y_min + (y_max - y_min) * y / (window_height - 1); //calculated as a pixel with current width and height rather than numbers on the number line
                complex<double> c(real, imag);

                int iter = isInSet(c, max_iter, threshold); //seeing if we count the number as in the set
                int color = 255 - (255 * iter / max_iter); //calculating the color based on how quickly it converges to infinity

                colors[x] = color;
            }
        }

        for (int i = 0; i < window_width; i++)
        {
            file << colors[i] << " " << colors[i] << " " << colors[i] << " "; //add the colored pixels to the image
        }
        file << "\n"; //go to the next line when done with one (on the x axis)
    }
    file.close();
}

int main() {
    double time = omp_get_wtime();

    generateMandelbrotSet(width, height, max_iter, threshold, x_min, x_max, y_min, y_max);
    
    time = omp_get_wtime() - time;
    int timeS = (int) time;
    time = (time - timeS) * 1000;
    int timeMS = (int) time;

    cout << "Mandelbrot set image generated in 'mandelbrot_set.ppm'" << endl;
    cout << "Time = " << timeS << " s " << timeMS << " ms" << endl;
    return 0;
}