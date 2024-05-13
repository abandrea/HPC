#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to compute the magnitude squared of a complex number
double magnitude_squared(double real, double imag) {
    return real * real + imag * imag;
}

// Function to determine if a point is in the Mandelbrot set
int mandelbrot(double c_real, double c_imag, int max_iter) {
    double z_real = 0.0, z_imag = 0.0;
    double z_real_new, z_imag_new;
    int iter = 0;

    while (magnitude_squared(z_real, z_imag) < 4.0 && iter < max_iter) {
        z_real_new = z_real * z_real - z_imag * z_imag + c_real;
        z_imag_new = 2 * z_real * z_imag + c_imag;
        
        z_real = z_real_new;
        z_imag = z_imag_new;

        iter++;
    }

    return iter;
}

// Main function to setup and compute Mandelbrot set over a grid and write to a PGM file
int main() {
    int width = 4096, height = 4096;
    double center_x = -0.75, center_y = 0.0;
    double radius = 2.0;
    int max_iterations = 1000;
    double scale_x = radius / width * 4;
    double scale_y = radius / height * 4;

    unsigned char *image = malloc(width * height);
    if (image == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Compute the Mandelbrot image
    for (int py = 0; py < height; py++) {
        for (int px = 0; px < width; px++) {
            double x = center_x + (px - width / 2) * scale_x;
            double y = center_y + (py - height / 2) * scale_y;
            int iters = mandelbrot(x, y, max_iterations);
            image[py * width + px] = (unsigned char)(255 * iters / max_iterations);
        }
    }

    // Write to PGM
    FILE *file = fopen("mandelbrot_4096.pgm", "wb");
    if (file == NULL) {
        perror("Failed to open file");
        free(image);
        return 1;
    }

    fprintf(file, "P5\n%d %d\n255\n", width, height); // Header
    fwrite(image, 1, width * height, file); // Pixel data
    fclose(file);
    free(image);

    return 0;
}