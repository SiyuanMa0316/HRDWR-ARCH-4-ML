#!/bin/bash

source /home/siyuan/HRDWR-ARCH-4-ML/Lab1A_virtualenv/bin/activate
sudo sh -c 'echo 1 >/proc/sys/kernel/perf_event_paranoid'
curr_path=/home/siyuan/HRDWR-ARCH-4-ML/Lab1
mkdir -p ${curr_path}/output_perf
#echo ${curr_path}
for code in 1 10 1101
do
    perf stat -o ${curr_path}/output_perf/out_mlp_${code} --append -e instructions,cycles,L1-dcache-loads,L1-dcache-load-misses,LLC-loads,LLC-load-misses,branches,branch-misses python3 ${curr_path}/mlp_keras.py ${code}
    perf stat -o ${curr_path}/output_perf/out_mlp_${code} --append -e instructions:u,cycles:u,L1-dcache-loads:u,L1-dcache-load-misses:u,LLC-loads:u,LLC-load-misses:u,branches:u,branch-misses:u python3 ${curr_path}mlp_keras.py ${code}
    perf stat -o ${curr_path}/output_perf/out_mlp_${code} --append -e mem_inst_retired.all_loads,mem_inst_retired.all_stores,br_inst_retired.all_branches python3 ${curr_path}/mlp_keras.py ${code}
    perf stat -o ${curr_path}/output_perf/out_mlp_${code} --append -e fp_arith_inst_retired.128b_packed_double,fp_arith_inst_retired.128b_packed_single,fp_arith_inst_retired.256b_packed_double,fp_arith_inst_retired.256b_packed_single,fp_arith_inst_retired.scalar_double,fp_arith_inst_retired.scalar_single python3 ${curr_path}/mlp_keras.py ${code}
done







