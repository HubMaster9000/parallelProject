#! /bin/bash

# Compile the serial version
gcc -o centroid_serial serial.c 

# Compile the OpenMP version
gcc -o centroid_openmp -fopenmp openmp.c

