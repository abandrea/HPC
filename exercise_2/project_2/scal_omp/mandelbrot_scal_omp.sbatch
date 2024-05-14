#!/bin/bash
#SBATCH --job-name=mandelbrot_scal_omp
#SBATCH --output=omp_scaling_%j.out
#SBATCH --error=omp_scaling_%j.err
#SBATCH --partition=THIN
#SBATCH --nodes=1
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=24 ## Assuming to use all cores on a node
#SBATCH --time=01:00:00
#SBATCH --exclusive

## Load the required modules
module load openMPI/4.1.5/gnu/12.2.1

## Compile the program
mpicc -o mandelbrot_scal_omp -fopenmp mandelbrot_mpi_omp.c

## Test for different number of OpenMP threads

for threads in 1 2 4 8 12 16 20 24
do
   export OMP_NUM_THREADS=$threads
   echo "Running with $threads OpenMP threads:"
   /usr/bin/time -v ./mandelbrot_scal_omp
done

echo "OpenMP scalability test completed."



