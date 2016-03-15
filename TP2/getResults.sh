#!/bin/bash
for algo in v d l
do
    echo "Processing $algo"
    for f in ./BTS/*.txt
    do
        
        ./tp2 -f $f -$algo >> $algo.csv
    done
done

