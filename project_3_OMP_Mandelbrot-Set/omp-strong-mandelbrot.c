// omp.mandelbrot.image
// OMP_NUM_THREADS=4 ./doublompi.mandelbrot.x 256 256 -2.75 -2 1.25 2 255

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define MAX_ITERATIONS_INT 255

// Function to check if a point is in the Mandelbrot set
int mandelbrot(double real, double imag, int max_iter) {
    double z_real = 0, z_imag = 0;
    double temp_real, temp_imag;
    int iter = 0;

    while (iter < max_iter) {
        // Iteration rule: z = z^2 + c
        temp_real = z_real * z_real - z_imag * z_imag + real;
        temp_imag = 2 * z_real * z_imag + imag;
        z_real = temp_real;
        z_imag = temp_imag;

        // Check if the magnitude of z exceeds 2
        if (sqrt(z_real * z_real + z_imag * z_imag) > 2.0) {
            break; // If it does, the point is not in the Mandelbrot set
        }

        iter++;
    }

    return iter; // Return the number of iterations before escape
}

// Function to write PGM image file
void write_pgm_image(const char *filename, int *pixel_data, int width, int height, int max_value) {
    FILE *file = fopen(filename, "wb");

    if (file == NULL) {
        printf("Error: Unable to create output file '%s'.\n", filename);
        exit(1);
    }

    // Write PGM header
    fprintf(file, "P5\n%d %d\n%d\n", width, height, max_value);

    // Write pixel data in binary format
    for (int i = 0; i < width * height; i++) {
        unsigned char pixel = (unsigned char)(pixel_data[i] * 255 / max_value);
        fwrite(&pixel, sizeof(unsigned char), 1, file);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 8) {
        printf("Usage: %s n_x n_y x_L y_L x_R y_R I_max\n", argv[0]);
        return 1;
    }

    // Parse command-line arguments
    int n_x = atoi(argv[1]);
    int n_y = atoi(argv[2]);
    double x_L = atof(argv[3]);
    double y_L = atof(argv[4]);
    double x_R = atof(argv[5]);
    double y_R = atof(argv[6]);
    int I_max = atoi(argv[7]);

    // Check for invalid input arguments
    if (n_x <= 0 || n_y <= 0 || I_max <= 0) {
        printf("Error: Invalid input arguments.\n");
        return 1;
    }

    // Allocate memory for iteration counts
    int *iteration_counts = (int *)malloc(sizeof(int) * n_x * n_y);

    if (iteration_counts == NULL) {
        printf("Error: Unable to allocate memory for iteration counts.\n");
        return 1;
    }

    // Calculate delta values
    double delta_x = (x_R - x_L) / n_x;
    double delta_y = (y_R - y_L) / n_y;

    // Start measuring execution time
    double start_time = omp_get_wtime();

    // Generate Mandelbrot set
    #pragma omp parallel for schedule(static, 1) collapse(2)
    for (int j = 0; j < n_y; j++) {
        for (int i = 0; i < n_x; i++) {
            double real = x_L + i * delta_x;
            double imag = y_L + j * delta_y;
            int index = j * n_x + i;
            iteration_counts[index] = mandelbrot(real, imag, I_max);
        }
    }

    // End measuring execution time
    double end_time = omp_get_wtime();

    // Print execution time
    printf("Mandelbrot image generated successfully.\n");
    printf("Execution time: %f seconds\n", end_time - start_time);

    // Write image to file
    write_pgm_image("mandelbrotints_image.pgm", iteration_counts, n_x, n_y, MAX_ITERATIONS_INT);

    // Free allocated memory
    free(iteration_counts);

    return 0;
}