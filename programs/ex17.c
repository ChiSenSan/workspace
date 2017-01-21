//ex17.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CITY_NUM 50        //市の名前　登録上限
#define FAC_NUM 20         //学部名　登録上限
#define INVERT_ROW 25+1    //インバーテッドテーブル　列数 最前列は要素数

#define READ_FILE   "H28LECBdata1.txt" //入力ファイル
#define WRITE_FILE  "H28LECBdataR.txt" //出力ランダムファイル

#define FIELD "\n%-10s%-4s%-10s%-10s%-20s%-16s"
#define REC 70

#define ERR        printf //エラー表示用
#define DEBAG      printf //デバッグ表示用
#define MES        printf //メッセージ表示用
#define EXIT      exit(0) //強制終了
//プロトタイプ宣言系
void Init(int t_cityRec[CITY_NUM][INVERT_ROW], int t_facRec[FAC_NUM][INVERT_ROW]);
void EditTable(char *s_newTitle, char *s_title, int *ar_list, int recNum, int flag);
void DisplayTable(char *s_title, int *ar_list, int c_max);

/***************
 *    main
 ***************/
int main(void){
    //インバーテッドテーブル系
    //出身市
    char t_cityName[CITY_NUM][16]; //市名格納
    int t_cityRec[CITY_NUM][INVERT_ROW]; //インバーテッドテーブル
    int c_city = 0; //市数カウンタ
    int c_cityRecMax = 0; //レコードの最大数
    
    //学部
    char t_facName[FAC_NUM][16]; //学部名格納
    int t_facRec[FAC_NUM][INVERT_ROW]; //インバーテッドテーブル
    int c_fac = 0; //学部数カウンタ
    int c_facRecMax = 0; //レコードの最大数
    
    //ファイルポインタ
    FILE *p_fileR; //読み込みファイル"H28LECBdata1.txt"ポインタ
    FILE *p_fileW; //書き込みファイル"H28LECBdataR.txt"ポインタ
    
    //リスト系
    char s_name[10];  //名前
    char s_sex[3];      //性別
    char s_pref[10];  //出身県
    char s_city[16];  //出身市
    char s_school[20];//出身校
    char s_fac[16];   //学部
    
    //検索系
    //検索入力用
    char s_inpCity[20];
    char s_inpFac[20]; 
    //予約語
    char s_seachEnd[] = "終了";
    char s_seachTable[] = "?";
    char c_seach = 0; //検索トライカウンタ
    
    //カウンタ
    int c_rec = 0; //レコードカウンタ
    int i;
    
    
    //インバーテッドテーブルの初期化
    Init( t_cityRec, t_facRec );
    
    //ファイル準備、読み込み
    //DEBAG(READ_FILE);
    //入力ファイル
    p_fileR = fopen(READ_FILE, "r" );
    if( p_fileR == NULL ){
        ERR("入力ファイルが見つかりません\n");
        EXIT;
    }
    //出力ファイル
    p_fileW = fopen( WRITE_FILE, "w" );
    if( p_fileW == NULL ){
        ERR("出力ファイルが見つかりません\n");
        EXIT;
    }
    
    //------------------------------------------------
    //    インバーテッドテーブル、ランダムファイルの作成
    //------------------------------------------------
    MES("--ランダムファイル作成開始--\n");
    
    while(1){
        //読み込み
        fscanf(p_fileR, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", s_name, s_sex, s_pref, s_city, s_school, s_fac);
        if ( feof( p_fileR) )  break;//ファイル終端であればブレイク
        //DEBAG("%s\n",s_name);
        
        //ランダムファイルへ書き込み
        fseek(p_fileW, REC*c_rec, 0);
        fprintf(p_fileW, FIELD, s_name, s_sex, s_pref, s_city, s_school, s_fac);
        
        //インバーテッドテーブルの作成
        if(!c_rec){ 
            //最初のレコードでの処理
            c_rec++;
            //出身市
            EditTable(s_city, t_cityName[c_city], t_cityRec[c_city], c_rec, 0);
            c_city++;

            //学部
            EditTable(s_fac, t_facName[c_fac], t_facRec[c_fac], c_rec, 0);
            c_fac++;
        }
        else{
            c_rec++;
            //市名が既存か探索
            for(i=0; i < c_city; i++){
                if(!strcmp(&t_cityName[i][0],s_city)){
                    //既存の場合
                    EditTable(NULL, NULL, t_cityRec[i], c_rec, 1);
                    break;
                }
            }
            if(i == c_city){
                //初出の場合
                EditTable(s_city, t_cityName[c_city], t_cityRec[c_city], c_rec, 0);
                c_city++;
                
            }
            else{
            	//レコード最大数を更新
            	if(c_cityRecMax < t_cityRec[i][0]) c_cityRecMax = t_cityRec[i][0];
            }
            //学部が既存か探索
            for(i=0; i < c_fac; i++){
                if(!strcmp(&t_facName[i][0],s_fac)){
                    //既存の場合
                    EditTable(NULL, NULL, t_facRec[i], c_rec, 1);
                    break;
                }
            }
            if(i == c_fac){
                //初出の場合
                EditTable(s_fac, t_facName[c_fac], t_facRec[c_fac], c_rec, 0);
                c_fac++;
            }
            else{
            	//レコード最大数を更新
            	if(c_facRecMax < t_facRec[i][0]) c_facRecMax = t_facRec[i][0];
            }
        }
	}
    MES("--ランダムファイル作成終了--\n");
    
    //インバーテッドテーブルの内容表示
    MES("出身市テーブルの内容\n");
    MES("		件数＝%d\n",c_city);
    for(i=0; i<c_city; i++){
    	DisplayTable(t_cityName[i], t_cityRec[i], c_cityRecMax);
	}
    MES("\n\n");
    MES("学部テーブルの内容\n");
    MES("		件数＝%d\n",c_fac);
    for(i=0; i<c_fac; i++){
    	DisplayTable(t_facName[i], t_facRec[i], c_facRecMax);
	}	
    MES("\n\n");
    
    //検索機能
    MES("～～　検索処理　開始　～～\n");
    while(1){
    	MES("【%3d】出身市名を入力してください\n",c_seach+1);
    	MES("　　   「%s」-->終了, 「%s」-->一覧表示     ?", s_seachEnd, s_seachTable);
    	scanf(" %s",s_inpCity);
    	//終了処理
    	if(!strcmp(s_inpCity, s_seachEnd)){
    		break;
    	}
    	//一覧表示
    	else if(!strcmp(s_inpCity, s_seachTable)){
    		MES("\n　　    ～　出身市名　一覧～\n");
    		for(i=0; i<c_city; i++){
    			MES("%-10s:",t_cityName[i]);
    			if(!(i%5)) MES("\n");
    		}
    	}
    	//学部
    	else{
    		MES("　　   学部名を入力してください\n");
    		MES("　　   「%s」-->一覧表示    ?",s_seachTable);
    		scanf(" %s",s_inpFac);
    		//一覧表示
    		if(!strcmp(s_inpFac, s_seachTable)){
    			MES("\n　　    ～　学部名　一覧～\n");
    			for(i=0; i<c_fac; i++){
    				MES("%10s:",t_facName[i]);
    				if(!(i%5)) MES("\n");
    			}
    		}
    		else{
    		}
    	}
    	c_seach++;
	}
    MES("～～　検索処理　終了　～～\n");
    
    //ファイルのクローズ
    fclose(p_fileR);
    fclose(p_fileW);
    
    MES("--プログラム終了\n");
    return 0;
}

/*****************************************
 *    インバーテッドテーブルの初期化
 *****************************************/
void Init(int t_cityRec[CITY_NUM][INVERT_ROW], int t_facRec[FAC_NUM][INVERT_ROW])
{
    int i,j;
    //出身市
    for(i=0; i < CITY_NUM; i++){
        t_cityRec[i][0] = 0;
        for(j=1; j < INVERT_ROW; j++){
            t_cityRec[i][j] = -9;
        }
    }
    
    //学部
    for(i=0; i < FAC_NUM; i++){
        t_facRec[i][0] = 0;
        for(j=1; j < INVERT_ROW; j++){
            t_facRec[i][j] = -9;
        }
    }
}

/*****************************************
 *    インバーテッドテーブルへの書き込み
 *****************************************/
void EditTable(char *s_newTitle, char *s_title, int *ar_list, int recNum, int flag)
{
    //フラッグ処理　0-new 1-add
    if(!flag){
        //新規処理
        strcpy(s_title, s_newTitle);//名前を記録
    }
    //追加処理
        ar_list[0]++; //カウンタをインクリメント
        ar_list[ar_list[0]] = recNum; //レコード番号を記録
}

/*****************************************
 *    インバーテッドテーブルの内容表示
 *****************************************/
 void DisplayTable(char *s_title, int *ar_list, int c_max)
 {
 	 int i;
 	 
 	 //一行を記述
 	 MES("%s  \t:",s_title);
 	 for(i=0; i<= c_max; i++){
 	 	 MES("%3d:",ar_list[i]);
 	 }
 	 MES("\n");
 }