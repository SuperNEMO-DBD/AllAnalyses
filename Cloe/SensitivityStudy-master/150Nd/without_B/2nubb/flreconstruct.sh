#!/bin/bash

for ((i=0;i<10;i++))
 do

sed "s|@JobNb|$i|g" script_flreconstruct > job_flreconstruct

# qsub -l sps=1 job_flsimulate
qsub -V -P P_nemo -l h_cpu=48:00:00,fsize=20G,sps=1 -e $WORKDIR/Simulations/stderr -o $WORKDIR/Simulations/stdo job_flreconstruct

done

