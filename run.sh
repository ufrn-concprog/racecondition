#!/bin/bash
for counter in $(seq 1 5); do 
    go run $1.go
    sleep 1
done
