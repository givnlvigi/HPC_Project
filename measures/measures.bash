#!/bin/bash

NMEASURES=5

ARRAY_SIZE=(10 100 1000)
ARRAY_THS=(0 1 2 4 8)

trap "exit" INT

SCRIPTPATH=$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )

echo "#------------------------------------ CREATING FILES PHASE STARTED ------------------------------------"

for size in "${ARRAY_SIZE[@]}"; do
    for ths in "${ARRAY_THS[@]}"; do
        $1/graph_generator_O3 $size $ths
    done
done

echo "#------------------------------------ CREATING FILES PHASE ENDED ------------------------------------"
echo "#-------------------------------- MEASURING PERFORMANCE PHASE STARTED -------------------------------"

for size in "${ARRAY_SIZE[@]}"; do
    for ths in "${ARRAY_THS[@]}"; do
        # for ((i = 0 ; i < $NMEASURES	; i++)); do
        if [[ $ths -eq 0 ]]; then 
            $1/program_seq_O3 SIZE$size-SEQ-INPUT $size
        else
            mpirun -np $ths $1/program_par_O3 SIZE$size-NT$ths-INPUT $size
        fi
        # done
    done
done