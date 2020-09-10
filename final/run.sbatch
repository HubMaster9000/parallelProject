#! /bin/bash 

#Job settings 
#SBATCH --nodes=1
#SBATCH --time=01:00:00
#SBATCH --output=output.out
echo "---- serial proc-----" 
./pre_proccess_serial
echo "------para proc -----" 
./pre_proccess_parallel
echo "------- parallel-------"
./parallel
echo "------- serial -------" 
./serial
