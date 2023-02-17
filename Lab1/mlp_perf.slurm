#!/bin/bash
#----------------------------------------------------
# Sample Slurm job script
#   for TACC Stampede2 SKX nodes
#
#   *** Serial Job on SKX Normal Queue ***
#
# Notes:
#
#   -- Copy/edit this script as desired.  Launch by executing
#      "sbatch sample.slurm" on a Stampede2 login node.
#
#   -- Serial codes run on a single node (upper case N = 1).
#        A serial code ignores the value of lower case n,
#        but slurm needs a plausible value to schedule the job.
#
#   -- For a good way to run multiple serial executables at the
#        same time, execute "module load launcher" followed
#        by "module help launcher".

#----------------------------------------------------

#SBATCH -J myjob                        # Job name
#SBATCH -o myjob.o%j                    # Name of stdout output file (%j corresponds to the job id)
#SBATCH -e myjob.e%j                    # Name of stderr error file (%j corresponds to the job id)
#SBATCH -p skx-normal                   # Queue (partition) name
#SBATCH -N 1                            # Total # of nodes (must be 1 for serial)
#SBATCH -n 1                            # Total # of mpi tasks (should be 1 for serial)
#SBATCH -t 00:60:00                     # Run time (hh:mm:ss)
#SBATCH --mail-user=siyuan.ma@utexas.edu
#SBATCH --mail-type=all                 # Send email at begin and end of job (can assign begin or end as well)
#SBATCH -A Hardware-Acceleratio         # Allocation name (req'd if you have more than 1)

# Other commands must follow all #SBATCH directives...

module load python3
source $WORK/Lab1A_virtualenv/bin/activate
mkdir -p $WORK/HRDWR-ARCH-4-ML/Lab1/output_perf
#sudo sh -c 'echo 1 >/proc/sys/kernel/perf_event_paranoid'
curr_path=$WORK/HRDWR-ARCH-4-ML/Lab1
echo ${curr_path}
for code in 1 10 1101
do
    perf stat -e instructions,cycles,L1-dcache-loads,L1-dcache-load-misses,LLC-loads,LLC-load-misses,branches,branch-misses python3 ${curr_path}/mlp_keras.py ${code} >> ${curr_path}/output_perf/out_mlp_${code}
    perf stat -e instructions:u,cycles:u,L1-dcache-loads:u,L1-dcache-load-misses:u,LLC-loads:u,LLC-load-misses:u,branches:u,branch-misses:u python3 ${curr_path}mlp_keras.py ${code} >> ${curr_path}/output_perf/out_mlp_${code}
    perf stat -e mem_inst_retired.all_loads,mem_inst_retired.all_stores,br_inst_retired.all_branches python3 ${curr_path}/mlp_keras.py ${code} >> ${curr_path}/output_perf/out_mlp_${code}
    perf stat -e fp_arith_inst_retired.128b_packed_double,fp_arith_inst_retired.128b_packed_single,fp_arith_inst_retired.256b_packed_double,fp_arith_inst_retired.256b_packed_single,fp_arith_inst_retired.scalar_double,fp_arith_inst_retired.scalar_single python3 ${curr_path}/mlp_keras.py ${code} >> ${curr_path}/output_perf/out_mlp_${code}
done







