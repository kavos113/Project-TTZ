#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

int main(int argc, char *argv[]){
    int all;       //全試行数
    int inner = 0; //円の内部の数
    int i;
    double x, y;
    double pi, respi;

    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //乱数の初期化
    srand((unsigned int)(time(NULL) + rank));

    if(rank == 0){
        printf("試行回数：");
        scanf("%d", &all);
    }

    MPI_Bcast(&all, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //1プロセスの処理
    for (i = 0; i < all / size; i++){
        //適当な点の生成
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        //円の内部かどうか判定
        if (x * x + y * y <= 1.0){
            inner++;
        }
    }

    pi = (double)inner / (double)(all / size) * 4.0;
    //ここまで

    printf("%f\n", pi);

    MPI_Reduce(&pi, &respi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0){
        respi /= size;
        printf("pi = %.16f\n", respi);
    }

    MPI_Finalize();

    return 0;
}