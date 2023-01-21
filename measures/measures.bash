#!/bin/bash

echo "ciao"


NMEASURES=5

ARRAY_SIZE=(10 100 1000)
ARRAY_THS=(0 1 2 4 8)

trap "exit" INT

SCRIPTPATH=$( cd -- "$(dirname "$0")" >/dev/null 2>&1 ; pwd -P )

for size in "${ARRAY_SIZE[@]}"; do
    for ths in "${ARRAY_THS[@]}"; do
        $1/graph_generator_O3 $size $ths
    done
done