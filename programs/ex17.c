//ex17.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define CITY_NUM 50        //�s�̖��O�@�o�^���
#define FAC_NUM 20         //�w�����@�o�^���
#define INVERT_ROW 25+1    //�C���o�[�e�b�h�e�[�u���@�� �őO��͗v�f��

#define READ_FILE   "H28LECBdata1.txt" //���̓t�@�C��
#define WRITE_FILE  "H28LECBdataR.txt" //�o�̓����_���t�@�C��

#define FIELD "\n%-10s%-4s%-10s%-10s%-20s%-16s"
#define R_FIELD "\n%10s%4s%10s%10s%20s%16s"
#define REC 70

#define ERR        printf //�G���[�\���p
#define DEBAG      printf //�f�o�b�O�\���p
#define MES        printf //���b�Z�[�W�\���p
#define EXIT      exit(0) //�����I��
//�v���g�^�C�v�錾�n
void Init(int t_cityRec[CITY_NUM][INVERT_ROW], int t_facRec[FAC_NUM][INVERT_ROW]);
void EditTable(char *s_newTitle, char *s_title, int *ar_list, int recNum, int flag);
void DisplayTable(char *s_title, int *ar_list, int c_max);
void SeachTable(int *ar_city, int *ar_fac, int *ar_seach, int i_mood);

/***************
 *    main
 ***************/
int main(void){
    //�C���o�[�e�b�h�e�[�u���n
    //�o�g�s
    char t_cityName[CITY_NUM][16]; //�s���i�[
    int t_cityRec[CITY_NUM][INVERT_ROW]; //�C���o�[�e�b�h�e�[�u��
    int c_city = 0; //�s���J�E���^
    int c_cityRecMax = 0; //���R�[�h�̍ő吔
    
    //�w��
    char t_facName[FAC_NUM][16]; //�w�����i�[
    int t_facRec[FAC_NUM][INVERT_ROW]; //�C���o�[�e�b�h�e�[�u��
    int c_fac = 0; //�w�����J�E���^
    int c_facRecMax = 0; //���R�[�h�̍ő吔
    
    //�t�@�C���|�C���^
    FILE *p_fileR; //�ǂݍ��݃t�@�C��"H28LECBdata1.txt"�|�C���^
    FILE *p_fileW; //�������݃t�@�C��"H28LECBdataR.txt"�|�C���^
    
    //���X�g�n
    char s_name[10];  //���O
    char s_sex[3];      //����
    char s_pref[10];  //�o�g��
    char s_city[16];  //�o�g�s
    char s_school[20];//�o�g�Z
    char s_fac[16];   //�w��
    
    //�����n
    //�������͗p
    char s_inpCity[20];
    char s_inpFac[20]; 
    //�\���
    char s_seachEnd[] = "�I��";
    char s_seachTable[] = "?";
    char c_seach = 0; //�����g���C�J�E���^
    int i_inp; //�������[�h�w��p
    
    int ar_seach[INVERT_ROW*2];
    //�J�E���^
    int c_rec = 0; //���R�[�h�J�E���^
    int i,j;
    
    
    //�C���o�[�e�b�h�e�[�u���̏�����
    Init( t_cityRec, t_facRec );
    
    //�t�@�C�������A�ǂݍ���
    //DEBAG(READ_FILE);
    //���̓t�@�C��
    p_fileR = fopen(READ_FILE, "r" );
    if( p_fileR == NULL ){
        ERR("���̓t�@�C����������܂���\n");
        EXIT;
    }
    //�o�̓t�@�C��
    p_fileW = fopen( WRITE_FILE, "w" );
    if( p_fileW == NULL ){
        ERR("�o�̓t�@�C����������܂���\n");
        EXIT;
    }
    
    //------------------------------------------------
    //    �C���o�[�e�b�h�e�[�u���A�����_���t�@�C���̍쐬
    //------------------------------------------------
    MES("--�����_���t�@�C���쐬�J�n--\n");
    
    while(1){
        //�ǂݍ���
        fscanf(p_fileR, "%[^,],%[^,],%[^,],%[^,],%[^,],%s", s_name, s_sex, s_pref, s_city, s_school, s_fac);
        if ( feof( p_fileR) )  break;//�t�@�C���I�[�ł���΃u���C�N
        //DEBAG("%s\n",s_name);
        
        //�����_���t�@�C���֏�������
        fseek(p_fileW, REC*c_rec, 0);
        fprintf(p_fileW, FIELD, s_name, s_sex, s_pref, s_city, s_school, s_fac);
        
        //�C���o�[�e�b�h�e�[�u���̍쐬
        if(!c_rec){ 
            //�ŏ��̃��R�[�h�ł̏���
            c_rec++;
            //�o�g�s
            EditTable(s_city, t_cityName[c_city], t_cityRec[c_city], c_rec, 0);
            c_city++;

            //�w��
            EditTable(s_fac, t_facName[c_fac], t_facRec[c_fac], c_rec, 0);
            c_fac++;
        }
        else{
            c_rec++;
            //�s�����������T��
            for(i=0; i < c_city; i++){
                if(!strcmp(&t_cityName[i][0],s_city)){
                    //�����̏ꍇ
                    EditTable(NULL, NULL, t_cityRec[i], c_rec, 1);
                    break;
                }
            }
            if(i == c_city){
                //���o�̏ꍇ
                EditTable(s_city, t_cityName[c_city], t_cityRec[c_city], c_rec, 0);
                c_city++;
                
            }
            else{
            	//���R�[�h�ő吔���X�V
            	if(c_cityRecMax < t_cityRec[i][0]) c_cityRecMax = t_cityRec[i][0];
            }
            //�w�����������T��
            for(i=0; i < c_fac; i++){
                if(!strcmp(&t_facName[i][0],s_fac)){
                    //�����̏ꍇ
                    EditTable(NULL, NULL, t_facRec[i], c_rec, 1);
                    break;
                }
            }
            if(i == c_fac){
                //���o�̏ꍇ
                EditTable(s_fac, t_facName[c_fac], t_facRec[c_fac], c_rec, 0);
                c_fac++;
            }
            else{
            	//���R�[�h�ő吔���X�V
            	if(c_facRecMax < t_facRec[i][0]) c_facRecMax = t_facRec[i][0];
            }
        }
	}
    MES("--�����_���t�@�C���쐬�I��--\n");
    
    //�t�@�C���̃N���[�Y
    fclose(p_fileR);
    fclose(p_fileW);
    
    //�C���o�[�e�b�h�e�[�u���̓��e�\��
    MES("�o�g�s�e�[�u���̓��e\n");
    MES("		������%d\n",c_city);
    for(i=0; i<c_city; i++){
    	DisplayTable(t_cityName[i], t_cityRec[i], c_cityRecMax);
	}
    MES("\n\n");
    MES("�w���e�[�u���̓��e\n");
    MES("		������%d\n",c_fac);
    for(i=0; i<c_fac; i++){
    	DisplayTable(t_facName[i], t_facRec[i], c_facRecMax);
	}	
    MES("\n\n");
    
    //�����_���t�@�C��
    p_fileR = fopen(WRITE_FILE, "r" );
    if( p_fileR == NULL ){
        ERR("���̓t�@�C����������܂���\n");
        EXIT;
    }
    
    //�����@�\
    MES("�`�`�@���������@�J�n�@�`�`\n");
    while(1){
    	MES("�y%3d�z�o�g�s������͂��Ă�������\n",c_seach+1);
    	MES("�@�@   �u%s�v-->�I��, �u%s�v-->�ꗗ�\��     ?", s_seachEnd, s_seachTable);
    	scanf(" %s",s_inpCity);
    	//�I������
    	if(!strcmp(s_inpCity, s_seachEnd)){
    		break;
    	}
    	//�ꗗ�\��
    	else if(!strcmp(s_inpCity, s_seachTable)){
    		MES("\n�@�@    �`�@�o�g�s���@�ꗗ�`\n");
    		for(i=0; i<c_city; i++){
    			MES("%-10s:",t_cityName[i]);
    			if(!(i%5)) MES("\n");
    		}
    	}
    	//�w��
    	else{
    		MES("�@�@   �w��������͂��Ă�������\n");
    		MES("�@�@   �u%s�v-->�ꗗ�\��    ?",s_seachTable);
    		scanf(" %s",s_inpFac);
    		//�ꗗ�\��
    		if(!strcmp(s_inpFac, s_seachTable)){
    			MES("\n�@�@    �`�@�w�����@�ꗗ�`\n");
    			for(i=0; i<c_fac; i++){
    				MES("%10s:",t_facName[i]);
    				if(!(i%5)) MES("\n");
    			}
    		}
    		else{
    			//����
    			MES("�@�@   �_�����Z�i��->1, �a->2       ?");
    			scanf(" %d", &i_inp);
    			
    			//�s��
    			for(i=0; i<c_city; i++){
    				if(strcmp(s_inpCity, t_cityName[i]))
    					break;
    			}
    			//�w��
    			for(j=0; j<c_fac; j++){
    				if(strcmp(s_inpFac, t_facName[i]))
    					break;
    			}
    			
    			SeachTable(t_cityRec[i], t_facRec[j], ar_seach, i_inp);
    			
    			//DEBAG("%d:::\n",ar_seach[0]-1);
    			
    			//�������ʂ̕\��
    			
    			if(ar_seach[0] > 1){
    				for(i=1; i<ar_seach[0]; i++){
    					//DEBAG("%d  \n", ar_seach[i]);
    					MES("(%3d) ���ԁ�%d\n", i+1,ar_seach[i]);
    					fseek(p_fileR, REC*(ar_seach[i]-1), 0);
    					fscanf(p_fileR, R_FIELD, s_name, s_sex, s_pref, s_city, s_school, s_fac);
    					
    					MES("�@�@   ���O�� \t%s\n", s_name);
    					MES("�@�@   �o�g�s���� \t%s\n", s_city);
    					MES("�@�@   �o�g���Z���� \t%s\n", s_school);
    					MES("�@�@   �w������ \t%s\n",s_fac);
    					MES("\n");
    				}
    			}
    			else{
    				MES("�������ʂ͂���܂���B\n");
    			}
    		}
    	}
    	c_seach++;
	}
    MES("�`�`�@���������@�I���@�`�`\n");
    
	//�t�@�C���̃N���[�Y
	fclose(p_fileR);
    
    MES("--�v���O�����I��\n");
    return 0;
}

/*****************************************
 *    �C���o�[�e�b�h�e�[�u���̏�����
 *****************************************/
void Init(int t_cityRec[CITY_NUM][INVERT_ROW], int t_facRec[FAC_NUM][INVERT_ROW])
{
    int i,j;
    //�o�g�s
    for(i=0; i < CITY_NUM; i++){
        t_cityRec[i][0] = 0;
        for(j=1; j < INVERT_ROW; j++){
            t_cityRec[i][j] = -9;
        }
    }
    
    //�w��
    for(i=0; i < FAC_NUM; i++){
        t_facRec[i][0] = 0;
        for(j=1; j < INVERT_ROW; j++){
            t_facRec[i][j] = -9;
        }
    }
}

/*****************************************
 *    �C���o�[�e�b�h�e�[�u���ւ̏�������
 *****************************************/
void EditTable(char *s_newTitle, char *s_title, int *ar_list, int recNum, int flag)
{
    //�t���b�O�����@0-new 1-add
    if(!flag){
        //�V�K����
        strcpy(s_title, s_newTitle);//���O���L�^
    }
    //�ǉ�����
        ar_list[0]++; //�J�E���^���C���N�������g
        ar_list[ar_list[0]] = recNum; //���R�[�h�ԍ����L�^
}

/*****************************************
 *    �C���o�[�e�b�h�e�[�u���̓��e�\��
 *****************************************/
 void DisplayTable(char *s_title, int *ar_list, int c_max)
 {
 	 int i;
 	 
 	 //��s���L�q
 	 MES("%s  \t:",s_title);
 	 for(i=0; i<= c_max; i++){
 	 	 MES("%3d:",ar_list[i]);
 	 }
 	 MES("\n");
 }
 
 /*****************************************
 *    �C���o�[�e�b�h�e�[�u���̌���
 *****************************************/
 void SeachTable(int *ar_city, int *ar_fac, int *ar_seach, int i_mood)
 {
 	 int i,j;
 	 for(i=0; i<INVERT_ROW*2; i++){
 	 	 ar_seach[i] = -9;
 	 }
 	 ar_seach[0] = 0;
 	 DEBAG("initialize Done\n");
 	 if(!(i_mood-1)){
 	 	 DEBAG("seki\n");
 	 	 //��
 	 	 for(i=1; i<ar_city[0]; i++){
 	 	 	 for(j=1; j<ar_fac[0]; j++){
 	 	 	 	 if(ar_city[i] == ar_fac[j]){
 	 	 	 	 	 ar_seach[++ar_seach[0]] = ar_city[i];
 	 	 	 	 	 break;
 	 	 	 	 }
 	 	 	 }
 	 	 }
 	 	 MES("�@�@   �_���σf�[�^�@%d��\n",ar_seach[0]-1);
 	 }
 	 else{
 	 	 DEBAG("wa\n");
 	 	 //�a
 	 	 //�w���e�[�u���𗬂�����
 	 	 for(i=1; i<ar_fac[0]; i++)
			ar_seach[++ar_seach[0]] = ar_fac[i];
			
		//�w���e�[�u���ɂȂ��������̂��s���e�[�u������ǉ�����
		for(i=1; i<ar_city[0]; i++){
 	 	 	 for(j=1; j<ar_fac[0]; j++){
 				//�������Ȃ�
 	 	 	 }
 	 	 	 if(j < ar_fac[0]){
 	 	 	 	 ar_seach[++ar_seach[0]] = ar_city[i];
 	 	 	 }
 	 	 }
 	 	 MES("�@�@   �_���a�f�[�^�@%d��\n",ar_seach[0]-1);
 	 }
 }