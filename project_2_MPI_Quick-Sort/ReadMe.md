# Parallel Quicksort with MPI

This repository contains codes, slurms and report for implementing parallel quicksort using MPI for distributed-memory parallel computing.

## Features:
- Sorts large datasets efficiently by distributing work among multiple processes.
- Utilizes quicksort algorithm for local sorting and parallel merge sort for final merging.
- Supports customization of dataset size and number of MPI processes.
- Measures execution time for performance evaluation.
- Requires MPI library for compilation and execution.

## Code:
The source codes for strong and weak scalling experiments are available [here](https://github.com/behrooz/FHPC-units/blob/main/report.pdf).

## Usage:
1. Compile the code with MPI support (`mpicc mpi-strong-qsort.c -o mpi-strong-qsort.x`).
2. Run the executable with desired number of MPI processes (`mpirun -np <num_processes> ./mpi-strong-qsort.x`).
3. View the execution time in seconds for sorting the dataset.

## Example:
To sort a dataset of size 100,000 using 4 MPI processes: `mpirun -np 4 ./mpi-strong-qsort.x`.

## Slurm:
The slurm for strong and weak scalling experiments are available [here](https://github.com/behrooz/FHPC-units/blob/main/report.pdf).

## Report:
The detailed report on the implementation and performance analysis can be found [here](https://github.com/behrooz/FHPC-units/blob/main/report.pdf).

## Contributors:
- [Nooshin Behrooz]
- [Nooshin.Behrooz@gmail.com]




