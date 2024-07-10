#!/bin/bash
#SBATCH --nodes=2                    #specify number of nodes
#SBATCH --ntasks-per-node=2          #specify number of cores per node
#SBATCH --time=1:00:00               # Maximum runtime of the job (hh:mm:ss)

#SBATCH --job-name=mpi_job           # Job name
#SBATCH --output=output_%j.txt       # Name of stdout output file (%j expands to job ID)
#SBATCH --error=error_%j.txt         # Name of stderr error file (%j expands to job ID)
#SBATCH --partition=standard   # Specify the partition/queue name

# Change to your program's directory
cd /path/to/your/mpi/program/directory

###load the default MPI module
module load intel/oneapi/mpi/2021.4.0

# Run your MPI program
mpirun -np $SLURM_NTASKS ./hello.mpi
