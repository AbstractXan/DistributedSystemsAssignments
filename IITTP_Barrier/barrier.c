#include <mpi.h>
#include <stdio.h>
#include <stdlib.h> 
int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    // Specify for rank 0
    if(world_rank==0){
        int n = rand()%100;
	    MPI_Send(&n,1,MPI_INT,world_rank+1,0,MPI_COMM_WORLD);
        int temp;
        MPI_Recv(&temp,1,MPI_INT,world_size-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf(" Rank %d recieved %d \n", world_rank , temp);
	    fflush(stdout);
    } else {
        int n;
        MPI_Recv(&n,1,MPI_INT,world_rank-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf(" Rank %d recieved %d \n", world_rank , n);
	    fflush(stdout);
        n++;
        if(world_rank!=world_size-1){
        MPI_Send(&n,1,MPI_INT,world_rank+1,0,MPI_COMM_WORLD);
        } else {
        MPI_Send(&n,1,MPI_INT,0,0,MPI_COMM_WORLD);
        }
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}
