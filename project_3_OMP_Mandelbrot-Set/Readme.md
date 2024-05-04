# OMPMandelbrot Image Generator

## Overview
This program generates a Mandelbrot set image using parallelized computation, allowing exploration of complex regions of the set within a reasonable time frame. It employs OpenMP directives for parallelization and outputs the Mandelbrot image in PGM (Portable Gray Map) format.

## Requirements
- C compiler (e.g., gcc)
- OpenMP library

## Usage
Compile the program using a C compiler:
gcc -fopenmp omp.mandelbrot.c -o omp.mandelbrot.x -lm

Run the program with the following command-line arguments:
OMP_NUM_THREADS=n ./executable-file.x n_x n_y x_L y_L x_R y_R I_max
Where:
- `n_x` and `n_y` are the dimensions of the image (width and height).
- `x_L`, `y_L`, `x_R`, `y_R` specify the rectangular region of the complex plane to explore.
- `I_max` is the maximum number of iterations for each point.

Example:
OMP_NUM_THREADS=8 ./omp-strong-mandelbrot.x 256 256 -2.75 -2 1.25 2 255

## Output
The program generates a PGM image file named `mandelbrot_image.pgm` in the current directory, representing the Mandelbrot set.


## Code:
The source codes are available 
[here](https://github.com/SNB-Cs-Ds/hpc_projects/blob/main/project_3_OMP_Mandelbrot-Set/omp-strong-mandelbrot.c) and
[here](https://github.com/SNB-Cs-Ds/hpc_projects/blob/main/project_3_OMP_Mandelbrot-Set/omp-weak-mandelbrot.c).

## Slurm:
The slurm for strong and weak scalling experiments are available 
[here](https://github.com/SNB-Cs-Ds/hpc_projects/blob/main/project_3_OMP_Mandelbrot-Set/slurm-omp-strong-mandelbort.job) and
[here](https://github.com/SNB-Cs-Ds/hpc_projects/blob/main/project_3_OMP_Mandelbrot-Set/slurm-omp-weak-mandelbort.job).

## Report:
The detailed report on the implementation and performance analysis can be found 
[here](https://github.com/SNB-Cs-Ds/hpc_projects/blob/main/project_3_OMP_Mandelbrot-Set/report_proj3.pdf).

## Contributors:
- [Nooshin Behrooz]
- [Nooshin.Behrooz@gmail.com]





