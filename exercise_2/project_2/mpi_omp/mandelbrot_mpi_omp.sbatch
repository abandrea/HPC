#!/bin/bash
#SBATCH --job-name=mandelbrot_mpi
#SBATCH --output=mandelbrot_%j.out
#SBATCH --error=mandelbrot_%j.err
#SBATCH --partition=THIN
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=24
#SBATCH --cpus-per-task=1
#SBATCH --time=01:00:00
#SBATCH --exclusive
##SBATCH --mem=4G

## Load the required modules
module load openMPI/4.1.5/gnu/12.2.1

## Number of thread OpenMP for each task MPI
export OMP_NUM_THREADS=4

mpicc -o mandelbrot_mpi_omp -fopenmp mandelbrot_mpi_omp.c

## Run the program
mpirun -np 48 ./mandelbrot_mpi_omp

