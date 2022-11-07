#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void){
    int all;       //全試行数
    int inner = 0; //円の内部の数
    int i;
    double x, y;
    double pi;

    //乱数の初期化
    srand((unsigned int)time(NULL));

    printf("試行回数：");
    scanf("%d", &all);

    for (i = 0; i < all; i++){
        //適当な点の生成
        x = (double)rand() / 32767;
        y = (double)rand() / 32767;

        //円の内部かどうか判定
        if (x * x + y * y <= 1.0){
            inner++;
        }
    }

    pi = (double)inner / (double)all * 4;

    printf("pi = %.16f\n", pi);

    return 0;
}