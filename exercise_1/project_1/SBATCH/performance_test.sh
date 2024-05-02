#!/bin/bash
#SBATCH --job-name=PerformanceModel
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --time=01:00:00
#SBATCH --partition=THIN
#SBATCH --exclusive

module load openMPI/4.1.5/gnu/12.2.1

# Define output directory and file
output_dir="../performance_test"
mkdir -p $output_dir
output_file="${output_dir}/performance.csv"

# Header for csv file
echo "Size, Avg Latency" > $output_file

# Assuming you want to vary the number of processes in a loop
result=$(mpirun -np 2 --map-by core ../../../../osu-micro-benchmarks-7.3/c/mpi/pt2pt/standard/osu_latency)
# write result to csv
echo $result >> $output_file

echo "Performance test completed"
