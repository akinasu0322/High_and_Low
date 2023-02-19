#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NMAX 13

double mat[NMAX][NMAX];

double high_low_dp(int n, int k){
    if(mat[n][k]!=0){
        return mat[n][k];
    }
    if(n==1 || n==2){
        mat[n][k] = 1;
        return mat[n][k];
    }
    double tmp, ret;
    if(k>(n-1)/2 && k<n) { //kが右寄りなら下から選択
        tmp = 0;
        for(int i=0; i<k; i++){
            tmp += high_low_dp(n-1, i);
        }
        ret = tmp / (n-1);
    } else if(k<=(n-1)/2 && k>=0) { //kが左寄りなら上から選択
        tmp = 0;
        for(int i=k; i<n-1; i++){
            tmp += high_low_dp(n-1, i);
        }
        ret = tmp/ (n-1);
    } else {
        assert(0);
    }
    mat[n][k] = ret;
    return mat[n][k];
}

void print_mat(int n){
    printf("[\n");
    for(int i=0; i<=n; i++){
        printf("[");
        for(int j=0; j<n; j++){
            printf("%lf, ", mat[i][j]);
        }
        printf("]\n");
    }
    printf("]\n");
    return;
}

int main(int argc, char **argv){
    int n = atoi(argv[1]);
    double sum = 0;
    double tmp = 0;
    for(int i=0; i<n; i++){
        tmp = high_low_dp(n, i);
        printf("n=%d, i=%d, tmp=%lf\n", n, i, tmp);
        sum += tmp;
    }
    double ret = sum/n;
    print_mat(n);
    printf("%d枚のトランプでhigh and lowをやると成功率は%lf%%です。\n", n, ret*100);
    return 0;
}
// katou,nogeseisyounennkouryuusennta-,daisuki,warera,nogeseino,gebokunari