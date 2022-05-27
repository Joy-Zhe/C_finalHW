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
#include "imgui.h"
#include "predefine.h"
#define DISPLAY
#define MENU
#define BUTTONS
#define APPAREA
#define SCOREAREA
#define TYPEAREA
#define N2S
#define RANK
#define TIMER_TOTAL 1
#define PATH
#define ADDEDFILE 

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

void Main (){
    InitGraphics();
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	registerTimerEvent(TimerEventProcess);      // ��ʱ��
	startTimer(TIMER_TOTAL, 10);
}

# 

#if defined(PATH)
void path(char *s_path, char *filename){
	FILE *fp;
	char path1[]={0};//�洢���յ��ļ���ȡ·�� 
	sprintf(path1, "%s%s", s_path, filename);//ƴ��s_path+filename���γ��������ļ�·�� 
	fp = fopen(path1, "rb");//���ļ� 
    char ch = fgetc(fp);
    while(ch != EOF){
        //�ļ��Ѵ� ,��Ӳ��� 
    }
    fclose(fp);
    return;
}
#endif

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
	static int flag_button = 0;//�ж��Ƿ��¡���ӡ���ť�� ����Ϊ1 
	int n = 0;
	SetPenColor("Yellow"); 
	drawRectangle(0.5, GetWindowHeight() / 4, GetWindowWidth() / 2, GetWindowHeight() / 2, 1);
	SetPenColor("Black");
	drawLabel(0.8, y + fH * 5 + 0.1, "����·����");
	drawLabel(0.8, y + 0.1, "�����ļ�����");
	textbox(GenUIID(0), 0.8 + TextStringWidth("�����ļ�����"), y + fH * 4.7, GetWindowWidth() / 3, h, path1, sizeof(path1));
	textbox(GenUIID(0), 0.8 + TextStringWidth("�����ļ�����"), y , GetWindowWidth() / 3, h, filename1, sizeof(filename1));
	if( button(GenUIID(0), 0.5 + GetWindowWidth() / 4 - w / 2, GetWindowHeight() / 3, w, h0, "���") && path1[0]){
		//path(path1, filename1);//���ļ����в���
		flag_button = 1;
		path_book++;
		f_path[path_book] = 1;
		sprintf(path_opened[path_book], "%s%s", path1, filename1);
		fp[path_book] = fopen(path_opened[path_book], "w");//���ļ� 
		while(path1[n] || filename1[n]){
			path1[n] = 0;
			filename1[n] = 0;
			n++;
		}//����ı��� 
	}
	if( button(GenUIID(0), 0.5 + GetWindowWidth() / 4 - w / 2, GetWindowHeight() * 4 / 15, w, h0, "ɾ��") && path1[0]){
		//path(path1, filename1);//���ļ����в���
		flag_button = 1;
		path_book++;
		f_path[path_book] = 1;
		sprintf(path_opened[path_book], "%s%s", path1, filename1);
		fp[path_book] = fopen(path_opened[path_book], "w");//���ļ� 
		while(path1[n] || filename1[n]){
			path1[n] = 0;
			filename1[n] = 0;
			n++;
		}//����ı��� 
	}
	SetPenColor("Blue");
	drawRectangle(x_List - TextStringWidth("EEEEEEEE"), GetWindowWidth() / 30, GetWindowWidth() * 7 / 12, GetWindowHeight(), 1);
	int List_i = 1, row = 1;
	SetPenColor("Green");
	drawLabel(x_List - TextStringWidth("EEEEE"), y_List - fH , "������ļ���");
	while(List_i <= path_book){
		if(f_path[List_i]){
			row++;
			drawLabel(x_List - TextStringWidth("EEEEE"), y_List - fH * (row + 1), path_opened[List_i]);//�ڽ�����ʾ������ļ�
		} 
		List_i++;
	}
}
#endif

#if defined(DISPLAY) //ˢ�� 
void display(){
	DisplayClear();
	Menu();
	drawButtons();
	typeArea();
} 
#endif 

/*struct default {
	int a[10000];//a[1]���ӦԪ�ص�Token��� 
	int n;//��¼�����е�Ԫ�ظ���
} */


