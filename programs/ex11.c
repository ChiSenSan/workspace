//ex11.c

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define CHA_MAX 26
#define STR_MAX 6
#define LIST_MAX 100

struct table
{
	char strings[6+1];
	int hashNum;
	struct table* next;
};

struct table func_hash(void);
void conf_hash(struct table* firstp);

int main(void)
{
	struct table *hash, *firstp;
	struct table* next;
	int i;
	
	firstp = hash;
	
	for(i=0; i<LIST_MAX; i++){
		//値の代入
		*hash = func_hash();
		printf("(%3d)%8s \t: %d\n",i+1, hash->strings, hash->hashNum);
		
		//新しい領域の確保
		next = (struct table*)malloc(sizeof(struct table));
		
		hash->next = next;
		hash = next;
	}
	
	hash->next = NULL;
	
	
	
	return 0;
}

struct table func_hash(void)
{
	int strNum;
	char rands;
	int tmp_hash = 0;
	int i;
	struct table tmp_list;
	
	//init
	tmp_list.next = NULL;
	
	//文字数の決定
	strNum = (rand() % STR_MAX) +1;
	
	//文字分の乱数を発生
	for(i=0; i < strNum; i++){
		rands = (rand()%CHA_MAX) + 65;
		tmp_hash += (int)rand;
		tmp_list.strings[i] = rands;
	}
	tmp_list.strings[i] = '\0';
	
	//ハッシュテーブルを計算1~9
	tmp_list.hashNum = (tmp_hash%9)+1;
	
	return tmp_list;
}

void conf_hash(struct table* firstp)
{
	struct table* tp = firstp;
	struct table* ctp = firstp;
	struct table* stp = NULL;
	int cnt = 0;
	int sd = 0, scnt = 0;
	
	//現在のリスト位置に移動
	while(1){
		if(tp->next == NULL) break;
		
		tp = tp->next;
	}
	
	//リストを走査
	while(1){
		cnt++;
		if(ctp->hashNum == tp->hashNum){
			scnt++;
			sd=cnt;
			stp = ctp;
		}
		if(tp->next == NULL) break;
		
		ctp = ctp->next;
	}
	
	if(sd > 0){
		printf("同じハッシュ値のデータが登録されています==>");
		printf("(ハッシュ値) %d (データ数) %d\n", stp->hashNum, scnt);
		printf(" 登録されているデータ\n");
		printf("  (リスト順)  %")
	}
}