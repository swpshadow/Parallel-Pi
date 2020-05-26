#!/usr/bin/env bash

#SBATCH --job-name=helloMPI
#SBATCH --error=job.%J.err
#SBATCH --output=job.%J.out
#SBATCH --ntasks=8
#SBATCH --time=10:00
#SBATCH --mem-per-cpu=100

# module load gcc
# module load openmpi

#cd ~/shadow_pi/
mpirun ./parallel_pi
