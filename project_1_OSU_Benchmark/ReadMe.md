# OSU Benchmark: Broadcasting and Scattering

## Overview
This repository contains the OSU Micro-Benchmarks for broadcasting and scattering operations using four different algorithms. These benchmarks are useful for evaluating the performance of MPI implementations and communication libraries for high-performance computing (HPC) applications.

## Supported Algorithms
The benchmark suite includes four different algorithms with general form;
for broadcasting bcast_algorithm n:

1. default       (n=0)
2. basicl_linear (n=1)
3. binary_tree   (n=5)
4. knomial       (n=7)

and for scattering scatter_algorithm n:

1. default        (n=0)
2. basic_linear   (n=1)
2. Binomial_tree  (n=2)
3. Linear_nb      (n=3)

Each algorithm offers different trade-offs in terms of communication pattern, message size, and scalability, allowing users to compare their performance under various conditions.

## Prerequisites
OSU benchmark files and
OpenMPI Libraries

## Building the Benchmarks
Before running the benchmarks, ensure that you have downloaded and compiled the OSU benchmark available ON this page: 

https://mvapich.cse.ohio-state.edu/benchmarks/ 

More detailed instruction about compilation can be found

[here] https://mvapich.cse.ohio-state.edu/static/media/mvapich/README-OMB.txt

for example, after downloading OSU benchmark
./configure --prefix=/u/dssc/nbehrooz/proj1/osu-micro-benchmarks-7.3

CC=/opt/programs/openMPI/4.1.5/bin/mpicc CXX=/opt/programs/openMPI/4.1.5/bin/mpicxx

make

make install

module load openMPI/4.1.5/gnu/12.2.1

## Running the Benchmarks
To run the benchmarks the general command lines are 

for example to run default algorithm of bcast communication with total num of tasks = 8 and 2 Nodes, 1 hour time and 1GB memory

compile:

salloc -n8 -N2 --cpus-per-task=1 -p EPYC --time= 1:00:00 --mem=1GB   

run:    

mpirun --mca coll_tuned_use_dynamic_rules true --mca coll_tuned_bcast_algorithm 0 osu_bcast

## Slurm:
The slurm for OSU benchmark Bcast and Scatter operations are available, respectively:

[here](https://github.com/SNB-Cs-Ds/hpc_projects/blob/main/project_1_OSU_Benchmark/slurm_osu_bcast.job) and

[here](https://github.com/SNB-Cs-Ds/hpc_projects/blob/main/project_1_OSU_Benchmark/slurm_osu_scatter.job).

## Report:
The detailed report on the implementation and performance analysis can be found 

[here](https://github.com/SNB-Cs-Ds/hpc_projects/blob/main/project_1_OSU_Benchmark/report_proj1.pdf).

## Contributors:
- [Nooshin Behrooz]
  
- [Nooshin.Behrooz@gmail.com]




