#!/bin/bash
#SBATCH --job-name=mandelbrot_mpi
#SBATCH --output=mandelbrot_%j.out
#SBATCH --error=mandelbrot_%j.err
#SBATCH --partition=EPYC
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=128
#SBATCH --time=02:00:00
#SBATCH --exclusive
##SBATCH --mem=4G

module load openMPI/4.1.5/gnu/12.2.1


mpicc -o mandelbrot_mpi mandelbrot_mpi.c


mpirun -n 48 ./mandelbrot_mpi

echo "Job finished at: `date`"
