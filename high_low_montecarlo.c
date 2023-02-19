#include <stdio.h>
#include "high_low.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

int high_low(int n);
int high_low_core(int n, int k, int rslt);
void makecsv_monte_rslt(int n_range, int rslt_len, int *rslt);

int main(int argc, char **argv){
    int rslt[NMONTE];
    srand((unsigned int)time(NULL));
    for(int i=0; i<NMONTE; i++){
        rslt[i] = high_low(N);
    }
    makecsv_monte_rslt(N, NMONTE, rslt);
    return 0;
}

//n枚でhigh_lowやって何枚成功するか。
int high_low(int n){
    int k = rand()%n + 1;
    // n枚のデッキからk番目が見えた状態でスタート
    int rslt = high_low_core(n, k, 0); 
    return rslt;
}

int high_low_core(int n, int k, int rslt){
    assert(1<=k && k<=n);
    if(n==2){ //必ず成功する。
        return ++rslt;
    }
    int tmp=rand()%(n-1) + 1; //1~nのうちk番目を除いて次のカードをめくる。
    if(tmp>=k){
        tmp = tmp + 1;
    }
    if(k<=n/2){ //下が見えてたら上を選択する
        if(k<tmp){
            // 成功したら次は「n-1枚の中からtmp-1番目が捲れている場合に何回正解するか。」という検証に移る。
            // tmp-1な理由はkが消えるから。
            return high_low_core(n-1, tmp-1, rslt+1);
        }else{
            // 失敗。これまでの記録を返す。
            return rslt;
        }
    }else{ //上の方が見えてたら下を選択する。
        if(k<tmp){ //失敗
            return rslt;
        }else{// 成功
            return high_low_core(n-1, tmp, rslt+1);
        }
    }
    printf("error.\n");
    exit(1);
}



void makecsv_monte_rslt(int n, int rslt_len, int *rslt){
    /*
    n:rsltが持つ整数値が0からn-1までであることを表す。度数分布の作成に必要。
    rslt_len:rsltの長さ。
    rslt:結果のリスト。
    */
    // 各成功回数の数え上げ
    int *total;
    if((total = (int *)malloc(sizeof(int)*n))==NULL){
        printf("malloc error.\n");
        exit(1);
    }
    memset(total, 0, sizeof(int)*n);
    for(int i=0; i<rslt_len; i++){
        total[rslt[i]]++; //rslt[i]は成功回数なので0回からn_range回までの整数。
    }
    // csvに結果書き込み
    FILE *fp;
    if((fp = fopen("montecarlo_result.csv", "w"))==NULL){
        printf("file open error.\n");
        exit(1);
    }
    for(int i=0; i<rslt_len; i++){
        fprintf(fp, "%d,", rslt[i]);
    }
    fseek(fp, -1, SEEK_END); //最後の「,」を消す。
    fprintf(fp, "\n");
    for(int i=0; i<n; i++){
        fprintf(fp, "%d,", total[i]);
    }
    fseek(fp, -1, SEEK_END);
    fprintf(fp, "\n");
    fclose(fp);
    free(total);
}

