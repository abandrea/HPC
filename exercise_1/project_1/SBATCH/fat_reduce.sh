#!/bin/bash
#SBATCH --job-name=Reduce_fat_benchmark
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=36 # Adjust according to your node configuration
#SBATCH --time=02:00:00
#SBATCH --partition=THIN
#SBATCH --constraint=FAT
#SBATCH --exclusive
module load openMPI/4.1.5/gnu/12.2.1

# Define output directory and file
output_dir="../../../../../HPC_project/HPC/exercise_1/project_1/results/"
mkdir -p $output_dir
output_file="${output_dir}fat_reduce_results.csv"

# Header for CSV file
echo "Algorithm,Processes,Size,Latency" > $output_file

# Algorithms to be tested
declare -A algorithms
algorithms[1]="basic_linear"
algorithms[2]="chain"
algorithms[3]="pipeline"

# Number of repetitions for average calculation
repetitions=1000

for alg in "${!algorithms[@]}"
do
    for j in {1..8}
    do
        processes=$((2**j))
        for i in {1..20}
        do
            size=$((2**i))
            # Execute osu_reduce with fixed size and varying processes
            result=$(mpirun --map-by core -np $processes --mca coll_tuned_use_dynamic_rules true --mca coll_tuned_reduce_algorithm $alg osu_reduce -m $size -x $repetitions -i $repetitions | tail -n 1 | awk '{print $2}')
            # Write results to CSV
            echo "${algorithms[$alg]},$processes,$size,$result" >> $output_file
        done
    done
done
