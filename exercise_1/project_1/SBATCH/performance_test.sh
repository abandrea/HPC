#!/bin/bash
#SBATCH --job-name=PythonTest
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=24
#SBATCH --time=01:00:00
#SBATCH --partition=THIN
#SBATCH --exclusive

# activate the virtual environment
source ../../../../venv/bin/activate

# Run the Python script
python performance_test.py

# Deactivate the environment
deactivate