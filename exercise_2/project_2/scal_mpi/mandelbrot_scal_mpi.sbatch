#!/bin/bash
#SBATCH --job-name=mandelbrot_scal_mpi
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

## Compile the program
mpicc -o mandelbrot_scal_mpi -fopenmp mandelbrot_mpi_omp.c

## Number of processes MPI to test for scalability
num_procs=(1 2 4 8 16 24 36 48)

## Run the program in loop for each number of processes
for procs in "${num_procs[@]}"
do
    echo "Running with ${procs} processes:"
    /usr/bin/time -v mpirun -np ${procs} ./mandelbrot_scal_mpi
done

echo "Scalability test is complete."



