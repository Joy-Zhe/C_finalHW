#ifndef _PREDEFINE_H_
#define _PREDEFINE_H_
 
static char path_opened[300000][300] = {{0}};//����Ѵ򿪵��ļ���·�� 
static int path_book;//���ڱ����Ѵ򿪵��ļ���·�� 
static int f_path[300000];
FILE *fp[300000];

void display();
void Menu();
void ranking(FILE *op);
void drawButtons();
void numtos(int num, char *s);

//������ֵ���г�ʼ�� 


#endif
