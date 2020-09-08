#! /bin/bash


g++ -o serial main.cpp

gcc -o pre_proccess_serial preProcessor_serial.c

gcc -o pre_proccess  -fopenmp  preProcessor.c
