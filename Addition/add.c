#include <mpi.h>
#include <stdio.h>

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

    // Print off a hello world message
    printf("Hello world from processor %s, rank %d out of %d processors\n",
           processor_name, world_rank, world_size);



    // Specify for rank 0
    if(world_rank==0){
	    // Initialize data
	int data[100];	
		
	for(int i=0; i<100 ; i++){
	    data[i]=1;
	}
	printf(" Initializd data \n");
	fflush(stdout);

	// Sending data to rank 1-3
	for(int i=1; i<4; i++){
		int a[25];
		for(int j=0;j<25; j++){
			a[j]=data[25*i+j]; // Assign 25 elements to each process		
		}
		MPI_Send(a,25,MPI_INT,i,0,MPI_COMM_WORLD);
		printf(" Data Sent to %d \n", i);
		fflush(stdout);
	}

	// Calculate sum over 25 of data
	int sum=0;
	for(int i=0; i<25; i++){
		sum+=data[i];
	}
	
	// Sum all sums incoming from processes
	int temp;
	for(int i=1; i<4;i++){
		MPI_Recv(&temp,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		sum+=temp;
	}
	
	printf(" Total sum is %d \n", sum);
	fflush(stdout);
    } else {
	int num[25];
	MPI_Recv(&num,25,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	
	printf("%d Recieved elements. First = %d \n", world_rank, num[0]);
	fflush(stdout);

	int sum=0;
	for(int i=0;i<25;i++){
		sum+=num[i];	
	}	

	printf("%d Calculated sum %d \n", world_rank, sum);
	fflush(stdout);
	MPI_Send(&sum,1,MPI_INT,0,0,MPI_COMM_WORLD);

	printf("%d Sent %d \n", world_rank, sum);
	fflush(stdout);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
}
