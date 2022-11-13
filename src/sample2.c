#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv){
    int rank; //ランク（自分が何プロセス目か）
    int proc; //全プロセス数
    int namelen; 
    char *name[namelen]; //プロセスを行うマシンの名前

    MPI_Init(&argc, &argv); //MPIの初期化
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); //ランクの取得
    MPI_Comm_size(MPI_COMM_WORLD, &proc); //全プロセス数の取得
    MPI_Get_processor_name(name, &namelen); //名前の取得

    printf("Hello, World! From process %d of %d, %s\n", rank, proc, name);
    MPI_Finalize(); //MPIを終了

    return 0;
}
