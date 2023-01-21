#!/bin/bash

NMEASURES=5

ARRAY_SIZE=(1000 5000 10000)
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
        ths_str=$(printf "%02d" $ths)

        OUT_FILE=$SCRIPTPATH/measure/SIZE-$size/SIZE-$size-NP-$ths_str.csv

        mkdir -p $(dirname $OUT_FILE) 2> /dev/null

        echo $(basename $OUT_FILE)
        echo "size,processes,read,tarjan,write,elapsed" >$OUT_FILE

        for ((i = 0 ; i < $NMEASURES	; i++)); do
            if [[ $ths -eq 0 ]]; then 
                $1/program_seq_O3 SIZE$size-SEQ-INPUT $size >> $OUT_FILE
                printf "\r> %d/%d %3.1d%% " $(expr $i + 1) $NMEASURES $(expr \( \( $i + 1 \) \* 100 \) / $NMEASURES)
                printf "#%.0s" $(seq -s " " 1 $(expr \( $i \* 40 \) / $NMEASURES))
            else
                mpirun -np $ths $1/program_par_O3 SIZE$size-NT$ths-INPUT $size >> $OUT_FILE
                printf "\r> %d/%d %3.1d%% " $(expr $i + 1) $NMEASURES $(expr \( \( $i + 1 \) \* 100 \) / $NMEASURES)
                printf "#%.0s" $(seq -s " " 1 $(expr \( $i \* 40 \) / $NMEASURES))
            fi
        done
        printf "\n"
    done
done