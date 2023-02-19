#include <stdio.h>
#include "high_low.h"

float d[N+1][N+1];
float p_sub(int n, int k);
void show_pmtrx();

int main(void){
    for(int i=0; i<=N+1; i++){
        for(int j=0; j<=N+1; j++){
            d[i][j] = -1.0;
        }
    }
    d[2][1] = 1.0;
    d[2][2] = 1.0;
    float posib=0;
    for(int i=1; i<=N; i++){
        posib += p_sub(N, i);
    }
    posib = (posib*100)/N;
    printf("possibility: %0.6f%%\n", posib);
    show_pmtrx();
    return 0;
}

float p_sub(int n, int k){
    if(d[n][k] != -1.0){
        return d[n][k];
    }
    if(n==2){
        d[n][k] = 1.0;
        return d[n][k];
    }
    float p_total=0;
    if(k<=n/2){
        for(int i=k+1; i<=n; i++){
            p_total += p_sub(n-1, i-1);
        }
        p_total = p_total/(n-1);
        d[n][k] = p_total;
    }
    else{ //代数的に省略できるけどわかりやすさ重視。計算量も変わらないし。
        for(int i=1; i<=k-1; i++){
            p_total += p_sub(n-1, i);
        }
        p_total = p_total/(n-1);
        d[n][k] = p_total;
    }
    return d[n][k];
}

void show_pmtrx(){
    printf("\tn\\k");

    for(int i=1; i<=N; i++){
        printf("\t%d ", i);
    }

    printf("\n");

    for(int i=1; i<=N; i++){
        printf("\t%d ", i);
        for(int j=1; j<=N; j++){
            printf("\t%0.3f ", d[i][j]);
        }
        printf("\n");
    }
    return;
}






