#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv){
    int rank, proc;
    int name_length = 10;
    char *name[name_length];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &proc);
    MPI_Get_processor_name(name, &name_length);

    printf("%s : %d of %d\n", name, rank, proc);

    MPI_Finalize();
    
    return 0;
}
