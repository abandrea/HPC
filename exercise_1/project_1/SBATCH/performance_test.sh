#!/bin/bash
#SBATCH --job-name=PythonTest
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=24
#SBATCH --time=01:00:00
#SBATCH --partition=THIN
#SBATCH --exclusive

# Load Python module
module load Python/3.8.2

# Activate the virtual environment
source myenv/bin/activate

# Run the Python script
python my_performance_test.py

# Deactivate the environment
deactivate