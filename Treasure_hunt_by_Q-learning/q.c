#define ALPHA 0.1		// 学習率
#define GAMMA 0.9		// 割引率
#define EPSILON 0.1		// イプシロングリーディの変数EPSILON
#define REWARD_T 10		// 最東端の報酬
#define REWARD_B -10	// 最西端の報酬
#define MAX_LOOP 200000	// 行動回数

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// 大きいほうの数字を返す関数maxi
double maxi(double a, double b) {
	if (a < b) return b;
	return a;
}

// 状態sから行動aをイプシロングリーディで選択する関数selectAction
int selectAction(double qValue[][2], int size, int state) {
	double tmp = (double)rand()/RAND_MAX;
	
	// q値の大きい行動を選択
	if (EPSILON < tmp) {
		if (qValue[state][0] < qValue[state][1]) return 1;
		return 0;
	}
	
	// EPSILONの確率でランダム選択
	int action = 0;
	if (0.5 <= (double)rand()/RAND_MAX) action = 1;
	else action = 0;
	
	return action;
	
}

// q値の更新式の2項目を計算する関数calcQValue
double calcQValue(double qValue[][2], int reward[], int state, int next, int action) {
	return (ALPHA * (reward[next] + GAMMA * maxi(qValue[next][0], qValue[next][1]) - qValue[state][action]));
}

int main(void) {
	// q値を格納する変数
	double qValue[5][2];
	// 各状態の報酬を格納する変数
	int reward[5] = {REWARD_B, 0, 0, 0, REWARD_T};
	// 状態s(初期値2)
	int s = 2;
	
	// rand関数を初期化
	srand(time(NULL));
	
	// qValueInit
	for(int i = 0; i < 5; i++) {
		for(int j = 0; j < 2; j++) {
			qValue[i][j] = 0.0;
		}
	}
	
	
	// 規定回数まで学習を続ける
	for(int i = 0; i < MAX_LOOP; i++) {
		if ((i % 5000) == 0) {
			printf("%d's qValue\n", i);
			for(int j = 0; j < 5; j++) {
				printf("%d", j);
				for(int k = 0; k < 2; k++) {
					printf(" %.2f", qValue[j][k]);
				}
				printf("\n");
			}
			printf("\n");
		}
		
		
		if (s == 0) {  // 最西端
			qValue[s][1] = qValue[s][1] + calcQValue(qValue, reward, s, 2, 1);
			s = 2;
		}
		else if (s == 4){  // 最東端
			qValue[s][0] = qValue[s][0] + calcQValue(qValue, reward, s, 2, 0);
			s = 2;
		}
		else {  // その他
			// 次の行動
			int action = 0;
			int next = 0;
			
			if (qValue[s][0] == qValue[s][1]) {
				// ランダムで次の遷移を決める
				if (0.5 <= (double)rand()/RAND_MAX) action = 0;
				else action = 1;
			}
			else {
				action = selectAction(qValue, 5, s);
			}
			
			if (action == 0) next = s - 1;
			else next = s + 1;
			
			// q値を更新
			qValue[s][action] = qValue[s][action] + calcQValue(qValue, reward, s, next, action);
			
			// 状態遷移
			s = next;
		}
	}
	
	printf("finel qValue\n");
	for(int j = 0; j < 5; j++) {
		printf("%d", j);
		for(int k = 0; k < 2; k++) {
			printf(" %.2f", qValue[j][k]);
		}
		printf("\n");
	}
	printf("\n");
	
	return 0;
}