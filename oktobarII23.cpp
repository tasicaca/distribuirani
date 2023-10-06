///oktobar 2 2023.///
#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	int rank, size;
	int datalocalno = 0;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	int data = rank; // Example data to be exchanged
	int partner_data;
	double partner_rank;

	for (int i = 0; i < log2(size); i++) {
			partner_rank = rank ^ (1 << i);

		//if (partner_rank < size) {
			MPI_Send(&data, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
			MPI_Recv(&partner_data, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			printf("Process %d exchanges data with process %d: My data: %d, Partner's data: %d\n", rank, partner_rank, data, partner_data);
			data += partner_data;
			// You can update the value of "data" here based on the partner's data if necessary
			if (partner_rank < rank)
			{
				datalocalno += partner_data;
				printf("rank %d  data: %d    \n", rank, datalocalno);
			}
			
		//}
	}

	MPI_Finalize();
	return 0;
}
