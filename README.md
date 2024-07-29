# MandelbrotSetGen

**Mandelbrot set** is a set of complex numbers, for which the function [ z(n+1) = z(n)^2 + c; z(0) = 0 ] does not converge to infinity, where c is the said complex number

This program generates a ppm file of the Mandelbrot set based on given parameters (width, height, number plane range, etc) and displays the points on the plain whiter the faster they converge to infinity

Tests (1000x1000, max_iter = 50, threshold = 10, x[-2; 2], y[-2; 2]):

    1 thread: approx. 5 s 500 ms

    2 threads: approx. 5 s 200 ms

    4 threads: approx. 5 s 0 ms

    8 threads: approx. 4 s 800 ms

    12 threads: approx. 4 s 700 ms

_Due to supposed false sharing, with more than one threads, the image is generated with some pixels having incorrect colors_
