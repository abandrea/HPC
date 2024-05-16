#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

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

// Main function to setup and compute the Mandelbrot set over 
// a grid and write it to a PGM image file 

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int width = 800, height = 800;
    double center_x = -0.75, center_y = 0.0;
    double radius = 2.0;
    int max_iterations = 1000;
    double scale_x = radius / width * 4;
    double scale_y = radius / height * 4;

    // parse command-line arguments
    // if (argc == 8) {
    //     width = atoi(argv[1]); // n_x
    //     height = atoi(argv[2]); // n_y
    //     center_x = atof(argv[3]); // x_L
    //     center_y = atof(argv[4]); // y_L
    //     radius = atof(argv[5]); 
    //     scale_x = radius / width * 4; // x_R
    //     scale_y = radius / height * 4; // y_R
    //     max_iterations = atoi(argv[6]); // I_max
    // } else if (argc != 1) {
    //     fprintf(stderr, "Usage: %s <width> <height> <center_x> <center_y> <radius> <max_iterations>\n", argv[0]);
    //     MPI_Abort(MPI_COMM_WORLD, 1);
    // }

    // each process will compute its own portion of the image
    int rows_per_process = height / size;
    int extra_rows = height % size;
    int start_row = rank * rows_per_process + (rank < extra_rows ? rank : extra_rows);
    int end_row = start_row + rows_per_process + (rank < extra_rows ? 1 : 0);

    unsigned char *local_image = malloc(width * (end_row - start_row));
    if (local_image == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    for (int py = start_row; py < end_row; py++) {
        for (int px = 0; px < width; px++) {
            double x = center_x + (px - width / 2) * scale_x;
            double y = center_y + (py - height / 2) * scale_y;
            int iters = mandelbrot(x, y, max_iterations);
            local_image[(py - start_row) * width + px] = (unsigned char)(255 * iters / max_iterations);
        }
    }

    // Gather all partial images to the root process
    unsigned char *image = NULL;
    if (rank == 0) {
        image = malloc(width * height);
        if (image == NULL) {
            fprintf(stderr, "Memory allocation failed at root\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    MPI_Gather(local_image, width * (end_row - start_row), MPI_UNSIGNED_CHAR,
               image, width * (end_row - start_row), MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    // Write to PGM only on the root process
    if (rank == 0) {
        FILE *file = fopen("mandelbrot.pgm", "wb");
        if (file == NULL) {
            perror("Failed to open file");
            free(image);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        fprintf(file, "P5\n%d %d\n255\n", width, height); // Header
        fwrite(image, 1, width * height, file); // Pixel data
        fclose(file);
        free(image);
    }

    free(local_image);
    MPI_Finalize();
    return 0;
}
