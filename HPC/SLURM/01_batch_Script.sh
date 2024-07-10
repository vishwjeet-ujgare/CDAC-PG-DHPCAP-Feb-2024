#!/bin/bash
#SBATCH --nodes=1                 # Number of nodes requested
#SBATCH --ntasks-per-node=1       # Number of tasks (or processes) per node
#SBATCH --time=00:05:00            # Maximum runtime of the job (hh:mm:ss)
#SBATCH --partition=cpu  # Specify the partition/queue name
#SBATCH --o %j.out    # Name of stdout output file (%j expands to job ID)
#SBATCH --e %j.err     # Name of stderr error file (%j expands to job ID)

# Commands to execute on the allocated node(s)
srun hostname
srun echo ${SLURM_JOBID}

# Additional commands can be added here
