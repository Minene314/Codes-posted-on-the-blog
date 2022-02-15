#include<stdio.h>
#include<string.h>
#include<time.h>

#define MAX_N 110   //商品の最大個数
#define MAX_C 1000  //出せる最大金額

typedef struct MENU{
    char name[256]; //商品名
    int cal;    //カロリー
    int cost;   //値段
}M;

int ans[MAX_N]={};  //解
int cand[MAX_N]={}; //解候補
M m[MAX_N]; //商品のデータ
int N;  //読み込んだ商品の種類数
int max_cal=0;  //最大カロリー
int costy=0;    //最大カロリーを実現するためのコスト


void knap(int i,int sum_cal,int sum_cos){
    //出せる金額を上回った
    if(sum_cos>MAX_C) return;

    //すべての品物について考えた
    if(i==N){
        if(sum_cos<=MAX_C && max_cal<sum_cal){
            memcpy(ans,cand,sizeof(cand));
            max_cal = sum_cal;
            costy = sum_cos;
        }
        return;
    }

    //商品iを入れる
    cand[i] = 1;
    knap(i+1,sum_cal+m[i].cal,sum_cos+m[i].cost);
    
    //商品iを入れない
    cand[i] = 0;
    knap(i+1,sum_cal,sum_cos);

    return;

}

int main(void){
    FILE *fp;
    char fname[] = "menu.txt";
    int cnt=0;
    clock_t start,end;

    if((fp = fopen(fname,"r"))==NULL){
        printf("errer\n");
        return -1;
    }else{
        printf("%s file opened\n",fname);
    }
    while(fscanf(fp,"%s %d %d",m[cnt].name,&m[cnt].cal,&m[cnt].cost)!=EOF) cnt++;
    fclose(fp);
    N = cnt;

    //メニュー一覧
    printf("%d\n",N);
    for(int i=0;i<N;i++) printf("name:%s\ncal:%d\ncost:%d\n\n",m[i].name,m[i].cal,m[i].cost);
    printf("\n");

    start = clock();    //開始時刻を取得
    knap(0,0,0);    //再帰ナップ
    end = clock();  //終了時刻を取得

    //最終解
    printf("you should order these! (cost<=%d)\n\n",MAX_C);
    for(int i=0;i<N;i++){
        if(ans[i]==1){
            printf("name:%s\ncal:%d\ncost:%d\n\n",m[i].name,m[i].cal,m[i].cost);
        }
    }
    printf("SUM_COST:%dyen\n",costy);   //かかるコスト
    printf("MAXI_CAL: %dcal\n\n",max_cal);  //摂取カロリー

    printf("calc_time:%fs\n\n",(double)(end-start)/CLOCKS_PER_SEC); //計算時間

    return 0;
}