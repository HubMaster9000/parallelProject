#! /bin/bash


g++ -o serial main.cpp

g++ -o pre_proccess_serial preProcessor_serial.cpp

g++ -o pre_proccess  -fopenmp  preProcessor.cpp
