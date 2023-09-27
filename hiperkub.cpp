#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define n 8

int main(int argc, char** argv)
{
	int rank, size, buffer[n];
	MPI_Status status;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0)
		for (int i = 0; i < n; i++)
			buffer[i] = i;

	int steps = log2(size);
	int bitmask = 0;

	for (int step_size = 1 << (steps - 1); step_size > 0; step_size >>= 1)
	{
		bitmask |= step_size;
		if ((rank & bitmask) == rank)
		{
			if ((rank ^ step_size) > rank)
				MPI_Send(&buffer[step_size], step_size, MPI_INT, rank ^ step_size, 0, MPI_COMM_WORLD);
			else
				MPI_Recv(&buffer[0], step_size, MPI_INT, rank ^ step_size, 0, MPI_COMM_WORLD, &status);

			printf("Process [%d] step %d: [", rank, (int)(steps - 1 - log2(step_size)));
			for (int j = 0; j < step_size; j++)
				printf("\t%d", buffer[j]);
			printf("\t]\n");
			fflush(stdout);
		}
	}

	MPI_Finalize();
	return 0;
}
