#!/bin/bash
#SBATCH --job-name=openmp            # Job name
#SBATCH --ntasks=1                   # Number of tasks (or processes) per node
#SBATCH --cpus-per-task=4            # Number of CPU cores per task (adjust as needed)
#SBATCH --time=10:00                 # Maximum runtime of the job (hh:mm:ss)
#SBATCH --output=ompresult.txt       # Name of stdout output file (%j expands to job ID)

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK

# Run your OpenMP program
srun ./hello.omp    `               #srun to run in parallel
