#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <omp.h>

double magnitude_squared(double real, double imag) {
    return real * real + imag * imag;
}

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

int main(int argc, char **argv) {
    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int width = 800, height = 800;
    double center_x = -0.75, center_y = 0.0;
    double radius = 2.0;
    double scale_x = radius / width * 4;
    double scale_y = radius / height * 4;
    int max_iterations = 1000;

    int rows_per_proc = height / size;
    int rem_rows = height % size;
    int local_start = rows_per_proc * rank;
    int local_end = local_start + rows_per_proc + (rank < rem_rows ? 1 : 0);

    unsigned char *local_image = malloc(width * (local_end - local_start));
    if (local_image == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    #pragma omp parallel for schedule(dynamic)
    for (int py = local_start; py < local_end; py++) {
        for (int px = 0; px < width; px++) {
            double x = center_x + (px - width / 2) * scale_x;
            double y = center_y + (py - height / 2) * scale_y;
            int iters = mandelbrot(x, y, max_iterations);
            local_image[(py - local_start) * width + px] = (unsigned char)(255 * iters / max_iterations);
        }
    }

    unsigned char *full_image = NULL;
    if (rank == 0) {
        full_image = malloc(width * height);
        if (full_image == NULL) {
            fprintf(stderr, "Root process memory allocation failed\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }
    MPI_Gather(local_image, width * (local_end - local_start), MPI_UNSIGNED_CHAR, full_image, width * (local_end - local_start), MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        FILE *file = fopen("mandelbrot.pgm", "wb");
        if (file == NULL) {
            perror("Failed to open file");
            free(full_image);
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        fprintf(file, "P5\n%d %d\n255\n", width, height);
        fwrite(full_image, 1, width * height, file);
        fclose(file);
        free(full_image);
    }

    free(local_image);
    MPI_Finalize();
    return 0;
}
