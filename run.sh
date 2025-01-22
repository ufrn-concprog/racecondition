#!/bin/bash
for counter in $(seq 1 20); do 
    ./bin/racecondition
    sleep 1
done
