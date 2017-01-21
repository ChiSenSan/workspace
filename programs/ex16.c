//-------------------------------------------------------------------------------
//    プログラミング上級Ⅱ　　練習問題６
//             ランダムファイルを活用した都市情報の検索
//         FileName=LECBRenMon08-6.c  （参考）LECARenMon02-6.c
//         入力ファイルは     MIYAGIdata10.txt
//         書き込みファイルは MIYAGIdata19.txt （ランダム形式）
//
//-------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define  REC        150
#define  ERR        printf
//---------------------------------------------------------------------------
//   main
//---------------------------------------------------------------------------
int main(void)
{
	char   name1[ 20+1 ] , name2[ 20+1 ] , name3[ 80+1 ] ;
	int    code1 , code2 , code3 ;
	int    sw0 , sw1  ;
	int    i , readCnt ;
	int hash;
	long   n;

	char setToshiName[ 30 ][ 20+1 ];
	int  setToshiAddress[ 30 ];
	char FIELD[]="\n%-6d%-10s%-20s%-60s%-10d%-10d";
	FILE   *fileFp1 , *fileFp2;
	
	fileFp1 = fopen( "MIYAGIdata10.txt" , "r" );
	if ( fileFp1 == NULL ){
		printf( " ファイル名（MIYAGIdata10.txt が見つかりません！\n");
		exit( 0 );
	}
	  
	  fileFp2 = fopen( "MIYAGIdata19.txt" , "w" );
      if ( fileFp2 == NULL )
      {
         printf( " ファイル名（MIYAGIdata19.txt が見つかりません！\n");
         exit( 0 );
      }
      
//-------------------------------------------------------------------------
//       ファイルの読み込み、書き込み　処理
//-------------------------------------------------------------------------
      puts("\t～～　ファイルの読み書き処理開始　～～");
//ファイルにセットされているデータ数の値を読込む
//	  
	  fscanf( fileFp1 , "%d" , &readCnt);
// 注意
      for( i=0 ; i<readCnt ; i++ )
      {
	  
			fscanf( fileFp1 , "%s" , &name1[0]);    //漢字都市名
			if ( feof( fileFp1) )  break;
            fscanf( fileFp1 , "%s" , &name2[0]);
			
			fscanf( fileFp1 , "%d" , &code1);      //ランダムファイルのレコード番号に採用
			fscanf( fileFp1 , "%s" , &name3[0]);
			fscanf( fileFp1 , "%d" , &code2);
			fscanf( fileFp1 , "%d" , &code3);
			
			strcpy( &setToshiName[i][0] , &name1[0]);
			setToshiAddress[i] = code1%100;        //下2桁を書込むレコード番号とする
			
		//ERR( "MSG01: ********* %10d %5d\n" , code1 , setToshiAddress[i]   );
			
//--------------------------------------------------------------------------
//  入力データの確認
//--------------------------------------------------------------------------
        	printf("<%2d>\n" , i+1);
			printf("・市町村名：%s\n" , &name1[0]);
			printf("・しちょうそんめい：%s\n" , &name2[0]);
			printf("・コード：%d\n" , code1);  //printf("----%d\n",code1%100);
			printf("・所在地住所：%s\n" , &name3[0]);
			printf("・人口数：%d\n" , code2);
	    	printf("・世帯数：%d\n" , code3);
			printf("\n");

//-------------------------------------------------------------
//  ランダムファイルへの書き込み処理
//------------------------------------------------------------- 
		hash = setToshiAddress[i];
		fseek(fileFp2, REC*hash, 0);
		fprintf(fileFp2, FIELD, code1, name1, name2, name3, code2, code3);
	   }
	 puts("\t　～～　ファイルの読み書き処理終了　～～");
//
//
//------------------------------------------------------------
//	検索　処理
//------------------------------------------------------------

      puts("\n");
	  puts("\t---------------------------------------------------");
	  puts("\t　　　　～～検索処理～～");
	  puts("\t---------------------------------------------------");
	
	  while(1){
	  	char word[20+1];
	  	int flag=0;
	  	
	  	printf("検索したい文字列を入力してください (終了は//end) ?");
	  	scanf(" %s",word);
	  	
	  	if(strcmp(word,"//end")==0)
	  		break;
	  	
	  	for(i=0 ; i<readCnt ; i++){
	  		if(strstr(&setToshiName[i][0],word) != NULL){
	  			flag = 1;
	  			break;
	  		}
	  	}
	  	
	  	if(flag){
	  		hash = setToshiAddress[i];
	  		fseek(fileFp2, REC*hash, 0);
	  		fscanf(fileFp2, FIELD, &code1, name1, name2, name3, &code2, &code3);
	  		
	  		printf("\t[コード] %d\n" , code1);
	  		printf("\t[都市名] %s\n" , &name1[0]);
			printf("\t[ひらがな] %s\n" , &name2[0]);
			printf("\t[住所] %s\n" , &name3[0]);
			printf("\t[人口数] %d\n" , code2);
	    	printf("\t[世帯数]%d\n" , code3);
	  	}
	  	else{
	  		printf("\t指定された市町村は見つかりませんでした!\n");
	  	}
	  	
	  	printf("\n\n");
	  }
	
	 fclose( fileFp2 );
	 puts("\n\t＊＊＊　プログラム終了　＊＊＊＊\n\n\n\n");
	 
    return 0;
}
