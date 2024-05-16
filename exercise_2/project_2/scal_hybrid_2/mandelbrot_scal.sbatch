#!/bin/bash
#SBATCH --job-name=mandelbrot_scal_hybrid
#SBATCH --output=hybrid_scaling_%j.out
#SBATCH --error=hybrid_scaling_%j.err
#SBATCH --partition=THIN
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=12 ## Using half of the cores on a node
#SBATCH --cpus-per-task=2 ## Distributing 2 threads openMP for each MPI task
#SBATCH --time=01:30:00
#SBATCH --exclusive

## Load the required modules
module load openMPI/4.1.5/gnu/12.2.1

## Compile the program
mpicc -o mandelbrot_hybrid -fopenmp mandelbrot_mpi_omp.c


## Executing the program with different number of MPI processes and OpenMP threads
for procs in 2 4 8 16 24
do
   for threads in 1 2 4 8 12
   do
      export OMP_NUM_THREADS=$threads
      echo "Running with $procs MPI processes and $threads OpenMP threads:"
      /usr/bin/time -v mpirun -np $procs ./mandelbrot_hybrid
   done
done

echo "Hybrid MPI+OpenMP scalability test completed."



