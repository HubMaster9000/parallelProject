#! /bin/bash 

#Job settings 
#SBATCH --nodes=1
#SBATCH --time=0:30:00
#SBATCH --output=output.out
echo "------- serial -------" 
./serial
echo "---- serial proc-----" 
./pre_proccess_serial
echo "------para proc -----" 
./pre_proccess
#echo "------- parallel-------"
#./para
