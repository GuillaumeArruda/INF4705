#!/bin/bash
rm v.csv
for algo in v d l
do
    rm $algo.csv
    echo "Processing $algo"
    for f in ./BTS/*.txt
    do
        
        ./tp2 -f $f -$algo >> $algo.csv
    done
done

