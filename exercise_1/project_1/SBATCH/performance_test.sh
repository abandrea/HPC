#!/bin/bash
#SBATCH --job-name=PerformanceModel
#SBATCH --nodes=2
#SBATCH --ntasks-per-core=1
#SBATCH --time=01:00:00
#SBATCH --partition=THIN
#SBATCH --exclusive

module load openMPI/4.1.5/gnu/12.2.1

# Define output directory and file
output_dir="../performance_test3"
mkdir -p $output_dir
output_file="${output_dir}/performance_3.csv"

# Header for csv file
echo "Size, Latency" > $output_file

# Run osu_latency and capture its output
result=$(mpirun -np 2 --map-by core ../../../../osu-micro-benchmarks-7.3/c/mpi/pt2pt/standard/osu_latency)

# Process and write results to csv
echo "$result" | grep -v '#' | grep -v 'MPI' | awk '{print $1 "," $2}' >> $output_file

echo "Performance test completed"