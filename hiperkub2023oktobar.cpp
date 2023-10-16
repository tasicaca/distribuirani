#define n 3
#define k 4
int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(NULL, NULL);
    // Get the rank of the process
    int myRank, size;
    int i, j;
    int val, sum = 0, tempZaSlanje = 0, tempRecv , komeSaljem;
    //MPI ono sto mora
    MPI_Status status;

    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    //main code

    val = myRank;
    sum = val;
    tempZaSlanje = val;

    for (i = 0; i < log2(size); i++) {
        komeSaljem = myRank xor (int)pow(2, i);
        MPI_Send(&tempZaSlanje, 1, MPI_INT, komeSaljem, 0, MPI_COMM_WORLD);
        MPI_Recv(&tempRecv, 1, MPI_INT, komeSaljem, 0, MPI_COMM_WORLD, &status);

        if (komeSaljem > myRank) tempZaSlanje += tempRecv;

        else {
            sum += tempRecv;
            tempZaSlanje += tempRecv;
        }
    }

    printf("My rank: %d, suma: %d\n", myRank, sum); 

    MPI_Finalize();
}
