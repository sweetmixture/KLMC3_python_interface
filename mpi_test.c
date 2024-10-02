#include <stdio.h>
#include <mpi.h>

int main() {
    // Initialize the Python interpreter

    MPI_Init(NULL,NULL);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&size);
	printf("rank %d\n",rank);

    MPI_Finalize();
    return 0; // Exit successfully
}

