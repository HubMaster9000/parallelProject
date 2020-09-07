#! /bin/bash 

#Job settings 
#SBATCH --nodes=1
#SBATCH --time=0:30:00
#SBATCH --output=output.out
echo "------- serial -------" 
./serial
#echo "------- parallel-------"
#./para
