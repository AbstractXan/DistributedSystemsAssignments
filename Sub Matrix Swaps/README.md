# Incrementing
8x8 Matrix is distributed to 4 Processes
The corner elements adjacent to other sub matrix are to be swapped.

Ex:
Input:
1 2 | 3 4
5 6 | 7 8
---------
9 1 | 2 3
4 5 | 6 7

Output:
1 2 | 3 4
9 1 | 7 8
---------
5 6 | 2 3
4 5 | 6 7

## Compiling
mpicc -o add add.c
## Running
mpirun -n 4 ./add
