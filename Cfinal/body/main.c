#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h> 
#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
#include <math.h>
#include <ctype.h>
#include "global.h"
#include "imgui.h"
#include "predefine.h"
#include "clone_class.h"
#define DISPLAY
#define MENU
#define BUTTONS
#define TYPEAREA
#define TIMER_TOTAL 1
#define PATH
#define ADDEDFILE 
#define OUTPUT 

void CharEventProcess(char ch){
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}
// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event){
	uiGetKeyboard(key,event); // GUI��ȡ����
	display(); // ˢ����ʾ
}
// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event){
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	display(); // ˢ����ʾ
}

void TimerEventProcess(int timerID){
	switch (timerID){
		case TIMER_TOTAL:
			display();
			break;
	}
}

int S2N (char *num);
void N2S(int num, char *s);

void Main (){
    InitGraphics();
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	registerTimerEvent(TimerEventProcess);      // ��ʱ��
	startTimer(TIMER_TOTAL, 10);
}

// �ַ���ת������ 
int S2N (char *num){
	int ans = 0, i = 0;
	while(*(num + i)){
		ans = ans * 10 + *(num + i) - '0';
		i++;
	}
	return ans;
}

void N2S(int num, char *s){
	int tmp = num, cnt = 0, cnt_s = 0;
	while (tmp){
		cnt++;
		tmp /= 10;
	}
	while (cnt){
		s[cnt_s] = num / (pow(10, cnt-1)) + '0';
		num = num - (num / (int)(pow(10, cnt-1))) * (int)(pow(10, cnt-1));
		cnt_s++;
		cnt--;
	}
}

#if defined(MENU) //�˵� 
void Menu(){
	static char *menuListAbout[] = {"����", "����", "�˳�"};
	double w = TextStringWidth(menuListAbout[0]) * 2, h = 0.4, x = 0, wsub = TextStringWidth("���˵�") * 1.2, y = GetWindowHeight() - h;
	static char *selectedLabel = NULL;
	//�����밴ť���� 
	double fH1 = GetFontHeight();
	double h1 = fH1*2; // �ؼ��߶�
	double x1 = GetWindowWidth() / 2.5; 
	double y1 = 0;
	double w1 = GetWindowWidth() / 5; // �ؼ����
	int selection;
 
	selection = menuList(GenUIID(0), x, y, w, wsub, h, menuListAbout, sizeof(menuListAbout)/sizeof(menuListAbout[0]));
	if(selection > 0) selectedLabel = menuListAbout[selection];
	switch(selection){
		case 1: //���� 
			system("start readme.txt");
			break;
		case 2: 
			exit(-1); //�˳� 
			break;

	}
}
#endif

#if defined(BUTTONS) //��ť 
void drawButtons(){
	double fH = GetFontHeight();
	double h = fH*2;  // �ؼ��߶�
	double x = GetWindowWidth() / 2.5;  
	double y = 0; 
	double w = GetWindowWidth() / 5; // �ؼ����
	if( button(GenUIID(0), x + w, y, w, h, "�鿴���") )
	{
		run(path_book, path_opened, file);
		clone_class(pair);
		output();
		system("output.txt");
	}
	if( button(GenUIID(0), x + 2 * w, y, w, h, "�˳�") ) 
		exit(-1);
}
#endif


#if defined(TYPEAREA) //������
void typeArea(){ 
	double x_List = GetWindowHeight() - TextStringWidth("EEEEE");
	double y_List = GetWindowHeight() - GetFontHeight();
	double h = GetWindowHeight() / 20;  // �������߶� 
	double fH = GetFontHeight();
	double h0 = fH*2;  // �ؼ��߶� 
	double w = GetWindowWidth() / 6; // ���������
	double x = GetWindowWidth() / 2 - w / 2;
	double y = GetWindowHeight() / 2 - h0 / 2; 
	static char path1[300] = ""; 
	static char filename1[300] = "";
	static char delete_num[300] = "";
	static int flag_button = 0;//�ж��Ƿ��¡���ӡ���ť�� ����Ϊ1 
	int n = 0, delete_book = 0;
	SetPenColor("Yellow"); 
	drawRectangle(0.5, GetWindowHeight() / 4, GetWindowWidth() / 2, GetWindowHeight() / 2, 1);
	SetPenColor("Black");
	drawLabel(0.8, y + fH * 5 + 0.1, "����·����");
	drawLabel(0.8, y + 0.1, "�����ļ�����");
	textbox(GenUIID(0), 0.8 + TextStringWidth("�����ļ�����"), y + fH * 4.7, GetWindowWidth() / 3, h, path1, sizeof(path1));
	textbox(GenUIID(0), 0.8 + TextStringWidth("�����ļ�����"), y , GetWindowWidth() / 3, h, filename1, sizeof(filename1));
	if( button(GenUIID(0), 0.5 + GetWindowWidth() / 4 - w / 2, GetWindowHeight() / 3 + fH * 2.3, w, h0, "���") && path1[0]){
		//path(path1, filename1);//���ļ����в���
		flag_button = 1;
		path_book++;
		f_path[path_book] = 1;
		sprintf(path_opened[path_book], "%s%s\0", path1, filename1);
		file[path_book] = fopen(path_opened[path_book], "r+");//���ļ� 
		while(path1[n] || filename1[n]){
			path1[n] = 0;
			filename1[n] = 0;
			n++;
		}//����ı��� 
	}
	drawLabel(0.5 + GetWindowWidth() / 4 - w / 2, GetWindowHeight() * 4 / 15, "��ɾ����");
	textbox(GenUIID(0), 0.5 + GetWindowWidth() / 4, GetWindowHeight() * 4 / 15 - 0.1, TextStringWidth("3000000"), fH * 1.5, delete_num, sizeof(delete_num));
	if( button(GenUIID(0), 0.5 + GetWindowWidth() / 4 - w / 2, GetWindowHeight() * 4 / 15 + fH * 2.3, w, h0, "ɾ��") && delete_num[0]){
		delete_book = S2N(delete_num);
		if(delete_book > path_book) delete_book = 0;//Խ�磬ͨ�����㣨�ڵ�0���ã���� 
		/*��bug,ɾȥ�����������⵼�����¸���ɾ 
		while(f_path[delete_book] == 0) 
			delete_book++;//�����Ѿ�ɾ�����ı�ţ�ͨ��˳����ɾ�� 
		*/
		f_path[delete_book] = 0;
		fclose(file[delete_book]);//�ر���ɾ���ļ� 
		n = 0;
		while(delete_num[n])
		{
			delete_num[n] = 0;
			n++;
		}//����ı��� 
	}
	
	SetPenColor("Blue");
	drawRectangle(x_List - TextStringWidth("EEEEEEEE"), GetWindowWidth() / 30, GetWindowWidth() * 7 / 12, GetWindowHeight(), 1);
	int List_i = 1, row = 1;
	SetPenColor("Green");
	drawLabel(x_List - TextStringWidth("EEEEE"), y_List - fH , "������ļ���");
	char List_index[10] = "";
	while(List_i <= path_book){
		if(f_path[List_i]){
			row++;
			N2S(List_i, List_index);
			drawLabel(x_List - TextStringWidth("EEEEEEE"), y_List - fH * (row + 1), List_index);
			drawLabel(x_List - TextStringWidth("EEEEE"), y_List - fH * (row + 1), path_opened[List_i]);//�ڽ�����ʾ������ļ�
		} 
		List_i++;
	}//����Ѵ��ļ� 
	/*
	while(List_i <= path_book){
		int i_temp = 0;
		if(f_path[List_i] == 0){
			for(i_temp = List_i; i_temp < path_book; i_temp++){
				f_path[i_temp] = f_path[i_temp + 1];
				strcpy(path_opened[i_temp], path_opened[i_temp + 1]);
			} 
			path_book--;
		} 
		if(f_path[List_i]) List_i++;
	}//���ñ�� 
	*/
}
#endif

#if defined(OUTPUT) //���
void output(){
	int i = 1, j = 1, sum = 0;;
	FILE *fp_out;
	int flag[10000]={0};
	int tree[10000]={0};
	fp_out = fopen("output.txt", "w+");
	for(i=1; i<= cnt_token; i++)
	{
		if(pair[i]==i)
		{
			int cnt_tree = 0; 
			for(j = 1; j <= cnt_token; j++)
			{
				if(pair[j] == i) cnt_tree++;
			}
			if(cnt_tree > 1)
			{
				sum++;
				tree[sum] = i;
			}
		}
	}
	fprintf(fp_out,"%d\n",sum);
	fprintf(fp_out,"#####################################################################\n");
	fprintf(fp_out,"#####################################################################\n");

	for(i = 1; i <= sum; i++)
	{
//		flag[i] = 1;
//		fprintf(fp_out,"���� Ϊ���Թ۲������%d %d\n ·��%s \n��ʼ�У�%d   �����У�%d \n%s\n", i, pair[i], Mtoken_copy[i].doc, Mtoken[i].startline, Mtoken[i].endline, Mtoken_copy[i].ch);
		for(j = 1; j <= cnt_token; j++)
		{
			if(tree[i] == pair[j])
			{
				flag[j] = 1;
				fprintf(fp_out,"���� Ϊ���Թ۲������%d %d\n·��:  %s \n��ʼ�У�%d   �����У�%d \n%s\n", i, pair[j], Mtoken_copy[j].doc, Mtoken[j].startline, Mtoken[j].endline, Mtoken_copy[j].ch);
			}
		}
		fprintf(fp_out,"#####################################################################\n");
		fprintf(fp_out,"#####################################################################\n");
	}
	fclose(fp_out); 
}
#endif 

#if defined(DISPLAY) //ˢ�� 
void display(){
	DisplayClear();
	Menu();
	drawButtons();
	typeArea();
	//output();
} 
#endif 






