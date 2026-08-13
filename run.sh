#!/bin/bash
for counter in $(seq 1 5); do 
    go run racebook.go
    sleep 1
done
