# Running MPI
Add 100 elements over 4 processes

## Compiling
mpicc -o add add.c
## Running
mpirun -n 4 ./add
