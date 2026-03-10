#!/bin/bash

N=1000000000
MAX_THREADS=10

> times.dat

for nthreads in $(seq 1 $MAX_THREADS)
do
    echo "Running with $nthreads threads"
    { /usr/bin/time -p ./main -threads $nthreads -terms $N ; } 2>&1 | \
    awk -v t=$nthreads '/real/ {print t, $2}' >> times.dat
done