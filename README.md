# parallelProject
Adding parallelism to an artificial neural network

serial_main.cpp - A serial implementation of a ANN using the MNIST dataset. Preprocesses data, trains model, and tests for accuracy. To run: include # of iterations as a parameter, ex. "serial_main.cpp 100"

parallel_main.cpp - An openMP parallel implementation of a ANN using the MNIST dataset. Preprocesses data, trains model, and tests for accuracy. To run: include # of iterations as a parameter, ex. "parallel_main.cpp 100"

preProcessor_serial.cpp - A serial preproceeseor for data (used for testing).

preProcessor_parallel.cpp - An attempt at a parallel preproceeseor for data (used for testing).


Modules to load: module load slurm gcc-7.2.0 

