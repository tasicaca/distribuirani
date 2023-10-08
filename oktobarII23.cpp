///oktobar 2 2023. hiperkub///

#include <stdio.h>
#include <mpi.h>
#include <math.h>

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);

	int rank, size;
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int datalocalno = rank;
	int data = rank; // Example data to be exchanged
	int partner_data;
	int partner_rank;

	for (int i = 0; i < log2(size); i++) {
			partner_rank = rank ^ (1 << i);//xor operator se obeležava sa ^ , mora se koristiti 1<<i jer se radi sa bitovima
		//proces razmenjuje podatke sa onim procesom koji se razlikuje za 1 bit, u prvoj iteraciji (001) na poziciji najnižeg bita, u drugoj iteraciji na poziciji srednjeg bita i u 
		//trecoj iteraciji na poziciji bita najveće težine (100)
			MPI_Send(&data, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD);
			MPI_Recv(&partner_data, 1, MPI_INT, partner_rank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	

			printf("Process %d exchanges data with process %d: My data: %d, Partner's data: %d\n", rank, partner_rank, data, partner_data);
			data += partner_data;
		
			if (partner_rank <= rank) //ako prima od procesa sa manjim rankom, uvecava svoje datalocalno
			{
				datalocalno += partner_data;
				 
				printf("rank %d  data: %d    \n", rank, datalocalno);
			}
			
		//}
	}

	MPI_Finalize();
	return 0;
}


