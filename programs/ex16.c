//-------------------------------------------------------------------------------
//    �v���O���~���O�㋉�U�@�@���K���U
//             �����_���t�@�C�������p�����s�s���̌���
//         FileName=LECBRenMon08-6.c  �i�Q�l�jLECARenMon02-6.c
//         ���̓t�@�C����     MIYAGIdata10.txt
//         �������݃t�@�C���� MIYAGIdata19.txt �i�����_���`���j
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
		printf( " �t�@�C�����iMIYAGIdata10.txt ��������܂���I\n");
		exit( 0 );
	}
	  
	  fileFp2 = fopen( "MIYAGIdata19.txt" , "w" );
      if ( fileFp2 == NULL )
      {
         printf( " �t�@�C�����iMIYAGIdata19.txt ��������܂���I\n");
         exit( 0 );
      }
      
//-------------------------------------------------------------------------
//       �t�@�C���̓ǂݍ��݁A�������݁@����
//-------------------------------------------------------------------------
      puts("\t�`�`�@�t�@�C���̓ǂݏ��������J�n�@�`�`");
//�t�@�C���ɃZ�b�g����Ă���f�[�^���̒l��Ǎ���
//	  
	  fscanf( fileFp1 , "%d" , &readCnt);
// ����
      for( i=0 ; i<readCnt ; i++ )
      {
	  
			fscanf( fileFp1 , "%s" , &name1[0]);    //�����s�s��
			if ( feof( fileFp1) )  break;
            fscanf( fileFp1 , "%s" , &name2[0]);
			
			fscanf( fileFp1 , "%d" , &code1);      //�����_���t�@�C���̃��R�[�h�ԍ��ɍ̗p
			fscanf( fileFp1 , "%s" , &name3[0]);
			fscanf( fileFp1 , "%d" , &code2);
			fscanf( fileFp1 , "%d" , &code3);
			
			strcpy( &setToshiName[i][0] , &name1[0]);
			setToshiAddress[i] = code1%100;        //��2���������ރ��R�[�h�ԍ��Ƃ���
			
		//ERR( "MSG01: ********* %10d %5d\n" , code1 , setToshiAddress[i]   );
			
//--------------------------------------------------------------------------
//  ���̓f�[�^�̊m�F
//--------------------------------------------------------------------------
        	printf("<%2d>\n" , i+1);
			printf("�E�s�������F%s\n" , &name1[0]);
			printf("�E�����傤����߂��F%s\n" , &name2[0]);
			printf("�E�R�[�h�F%d\n" , code1);  //printf("----%d\n",code1%100);
			printf("�E���ݒn�Z���F%s\n" , &name3[0]);
			printf("�E�l�����F%d\n" , code2);
	    	printf("�E���ѐ��F%d\n" , code3);
			printf("\n");

//-------------------------------------------------------------
//  �����_���t�@�C���ւ̏������ݏ���
//------------------------------------------------------------- 
		hash = setToshiAddress[i];
		fseek(fileFp2, REC*hash, 0);
		fprintf(fileFp2, FIELD, code1, name1, name2, name3, code2, code3);
	   }
	 puts("\t�@�`�`�@�t�@�C���̓ǂݏ��������I���@�`�`");
//
//
//------------------------------------------------------------
//	�����@����
//------------------------------------------------------------

      puts("\n");
	  puts("\t---------------------------------------------------");
	  puts("\t�@�@�@�@�`�`���������`�`");
	  puts("\t---------------------------------------------------");
	
	  while(1){
	  	char word[20+1];
	  	int flag=0;
	  	
	  	printf("�������������������͂��Ă������� (�I����//end) ?");
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
	  		
	  		printf("\t[�R�[�h] %d\n" , code1);
	  		printf("\t[�s�s��] %s\n" , &name1[0]);
			printf("\t[�Ђ炪��] %s\n" , &name2[0]);
			printf("\t[�Z��] %s\n" , &name3[0]);
			printf("\t[�l����] %d\n" , code2);
	    	printf("\t[���ѐ�]%d\n" , code3);
	  	}
	  	else{
	  		printf("\t�w�肳�ꂽ�s�����͌�����܂���ł���!\n");
	  	}
	  	
	  	printf("\n\n");
	  }
	
	 fclose( fileFp2 );
	 puts("\n\t�������@�v���O�����I���@��������\n\n\n\n");
	 
    return 0;
}
