#! /bin/bash


g++ -g -o serial  serial_main.cpp
g++ -g -o parallel -fopenmp parallel_main.cpp
g++ -o pre_proccess_serial preProcessor_serial.cpp
g++ -o pre_proccess_parallel  -fopenmp  preProcessor_parallel.cpp
