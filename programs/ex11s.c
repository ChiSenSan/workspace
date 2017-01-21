//ex11s.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CHA_MAX 26
#define STR_MAX 6
#define HASH_MAX 4
#define LIST_MAX 10

struct list
{
	char name[STR_MAX+1];
	int num;
	struct list* next;
}table[HASH_MAX];

int func_hash(struct list* data);
void conf_hash(int* hcnt);
void search_hash(char* str);

int main(void)
{
	struct list* tmpd;
	int hcnt[HASH_MAX];
	int i;
	
	//printf("check\n");
	tmpd = (struct list*)malloc(sizeof(struct list));
	//init
	for(i=0; i<HASH_MAX; i++){
		table[i].next = NULL;
		hcnt[i] = 0;
	}
	
	//データの挿入
	for(i=0; i<LIST_MAX; i++){
		int h_num;
		//init
		tmpd->next = NULL;
		tmpd->num = i+1;
		
		h_num = func_hash(tmpd);
		if(tmpd->name == NULL){
			printf("error!\n");
			exit(-1);
		}
		
		printf("○%3d-->%-8s \t(ハッシュ値) %d\n", tmpd->num, tmpd->name, h_num);
		
		if(hcnt[h_num]){
			//ハッシュテーブルの挿入処理
			struct list* tmp_list;
			tmp_list = &table[h_num];
			while(1){
				//printf(":::::%p\n",tmp_list);
				if(tmp_list->next == NULL) break;
				tmp_list = tmp_list->next;
			}
			
			tmp_list->next = tmpd;
			
			//同値ハッシュの警告
			printf("\t同じハッシュ値のデータが登録されています==>(ハッシュ値)%d(データ数)%d\n",h_num ,hcnt[h_num]);
			printf("\t 登録されているデータ\n");
			printf("\t  (リスト順) %d==>%s \t\t(登録順番)%3d\n",hcnt[h_num] ,tmp_list->name, tmp_list->num);
			printf("\t 注意：データを登録します\n");
			printf("\t  (登録データ) ==>%s\n",tmpd->name);
			
		}
		else{
			//各ハッシュテーブル一回目の処理
			table[h_num] = *tmpd;
		}
		(hcnt[h_num])++;
		tmpd = (struct list*)malloc(sizeof(struct list));
	}
	//確認
	conf_hash(hcnt);
	//検索
	while(1){
		char s_str[STR_MAX+1];
		
		printf("△△＝＝＝検索機能\n");
		printf("検索文字列を入力してください(6文字以内)「終了は //END」?");
		scanf(" %s",s_str);
		if(!strcmp("//END",s_str)) break;
		
		search_hash(s_str);
	}
	
	printf("\t---プログラム終了---");
	return 0;
}

int func_hash(struct list* data)
{
	int strNum;
	char rands;
	int tmp_hash = 0;
	int i;
	
	//文字数の決定
	strNum = (rand() % STR_MAX) +1;
	
	//文字分の乱数を発生
	for(i=0; i < strNum; i++){
		rands = (rand()%CHA_MAX) + 65;
		tmp_hash += (int)rands;
		data->name[i] = rands;
	}
	data->name[i] = '\0';
	
	//ハッシュテーブルを計算1~9
	//printf("%d\n",tmp_hash);
	tmp_hash = tmp_hash%HASH_MAX;
	
	return tmp_hash;
}

void conf_hash(int* hcnt)
{
	int i,j;
	struct list* tmp_table;
	printf("------------------------------\n");
	printf("     ハッシュテーブルの確認   \n");
	printf("------------------------------\n\n");
	
	for(i=0; i<HASH_MAX; i++){
		printf("ハッシュ値=%d(登録データ数)%d\n",i,hcnt[i]);
		tmp_table = &table[i];
		for(j=0;;j++){
			printf("[%d]%-7s(登録順番)%d\n",j+1, tmp_table->name, tmp_table->num);
			if(tmp_table->next == NULL) break;
			tmp_table = tmp_table->next;
		}
		printf("\n");
	}
}

void search_hash(char* str)
{
	int i;
	int s_num;
	int tmp_hash = 0;
	struct list* data;
	
	//ハッシュ値の計算
	s_num = strlen(str);
	for(i=0; i < s_num; i++)
		tmp_hash += (int)str[i];
	
	tmp_hash = tmp_hash%HASH_MAX;
	
	printf("確認(ハッシュ値)=%d",tmp_hash);
	
	data=&table[tmp_hash];
	
	printf("\n\t検索したい文字列 ?%s\n",str);
	
	for(i=0;;i++){
		
		printf("\t [%d]%-8s(登録順番)%2d  ---->", i, data->name, data->num);
		
		if(strcmp(str, data->name) != 0){
			printf("NG NG\n");
		}
		else{
			printf("見つかりました\n");
		}
		if(data->next == NULL) break;
		data = data->next;
	}
	printf("\n\n");
}
