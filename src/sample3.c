#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int rank; 
    int all_proc; //全プロセス数
    int numinput;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &all_proc);

    //proc_num = 0 はマスターノード

    if(rank == 0){
        printf("input num:");
        scanf("%d", &numinput);
    }

    MPI_Bcast(&numinput, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("I am process %d, recieved = %d\n", rank, numinput);

    MPI_Finalize();

    return 0;
}
/*expected result
input num: 22 ←input

I am process 1, recieved = 22
I am process 3, recieved = 22
I am process 2, recieved = 22
I am process 0, recieved = 22
*/