#!/bin/bash

# Slurm job options (job-name, job time)
#SBATCH --job-name=data_analysis
#SBATCH --time=0:20:0
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --cpus-per-task=1

# Replace [budget code] below with your budget code (e.g. t01)
#SBATCH --account=e05-react-smw
#SBATCH --partition=standard
#SBATCH --qos=short

# Define memory required for this jobs. By default, you would
# get just under 2 GB, but you can ask for up to 125 GB.
##SBATCH --mem=4G

# Set the number of threads to 1
#   This prevents any threaded system libraries from automatically
#   using threading.
export OMP_NUM_THREADS=1

source /work/e05/e05/wkjee/miniconda3/bin/activate
echo ' | shell loading py env - done'

#EXE="/work/e05/e05/wkjee/Software/gulpklmc/CPython/a.out"
EXE="/work/e05/e05/wkjee/Software/gulpklmc/CPython/PassTwoIntRetSum.x"
PyLocal="/work/e05/e05/wkjee/miniconda3/lib/"

export LD_LIBRARY_PATH=${PyLocal}:$LD_LIBRARY_PATH
echo 'ldd check'
ldd ${EXE}
echo 'ldd check end ---------'

srun --ntasks-per-node=2 --cpus-per-task=1 --distribution=block:block --hint=nomultithread ${EXE}
#srun --ntasks=4 --cpus-per-task=1 --distribution=block:block --hint=nomultithread ${EXE}
#srun --cpus-per-task=1 --distribution=block:block --hint=nomultithread ${EXE}
