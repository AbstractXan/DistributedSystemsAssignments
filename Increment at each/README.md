# Incrementing
0 send number n to 1.
1 increments and send to 2.
...
3 increments and sends to 0 

## Compiling
mpicc -o inc inc.c
## Running
mpirun -n 4 ./inc
