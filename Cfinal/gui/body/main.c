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
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}
// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event){
	uiGetKeyboard(key,event); // GUI获取键盘
	display(); // 刷新显示
}
// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event){
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	display(); // 刷新显示
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
	registerCharEvent(CharEventProcess);        // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerTimerEvent(TimerEventProcess);      // 定时器
	startTimer(TIMER_TOTAL, 10);
}

# 

#if defined(PATH)
void path(char *s_path, char *filename){
	FILE *fp;
	char path1[]={0};//存储最终的文件读取路径 
	sprintf(path1, "%s%s", s_path, filename);//拼接s_path+filename，形成完整的文件路径 
	fp = fopen(path1, "rb");//打开文件 
    char ch = fgetc(fp);
    while(ch != EOF){
        //文件已打开 ,添加操作 
    }
    fclose(fp);
    return;
}
#endif

#if defined(MENU) //菜单 
void Menu(){
	
	static char *menuListAbout[] = {"关于", "帮助", "退出"};
	double w = TextStringWidth(menuListAbout[0]) * 2, h = 0.4, x = 0, wsub = TextStringWidth("。菜单") * 1.2, y = GetWindowHeight() - h;
	static char *selectedLabel = NULL;
	//以下与按钮关联 
	double fH1 = GetFontHeight();
	double h1 = fH1*2; // 控件高度
	double x1 = GetWindowWidth() / 2.5; 
	double y1 = 0;
	double w1 = GetWindowWidth() / 5; // 控件宽度
	int selection;
 
	selection = menuList(GenUIID(0), x, y, w, wsub, h, menuListAbout, sizeof(menuListAbout)/sizeof(menuListAbout[0]));
	if(selection > 0) selectedLabel = menuListAbout[selection];
	switch(selection){
		case 1: //帮助 
			system("start readme.txt");
			break;
		case 2: 
			exit(-1); //退出 
			break;

	}
}
#endif

#if defined(BUTTONS) //按钮 
void drawButtons(){
	double fH = GetFontHeight();
	double h = fH*2;  // 控件高度
	double x = GetWindowWidth() / 2.5;  
	double y = 0; 
	double w = GetWindowWidth() / 5; // 控件宽度
	if( button(GenUIID(0), x + 2 * w, y, w, h, "退出") ) 
		exit(-1);
}
#endif


#if defined(TYPEAREA) //操作区
void typeArea(){ 
	double x_List = GetWindowHeight() - TextStringWidth("EEEEE");
	double y_List = GetWindowHeight() - GetFontHeight();
	double h = GetWindowHeight() / 20;  // 操作区高度 
	double fH = GetFontHeight();
	double h0 = fH*2;  // 控件高度 
	double w = GetWindowWidth() / 6; // 操作区宽度
	double x = GetWindowWidth() / 2 - w / 2;
	double y = GetWindowHeight() / 2 - h0 / 2; 
	static char path1[300] = ""; 
	static char filename1[300] = "";
	static int flag_button = 0;//判断是否按下“添加”按钮， 按下为1 
	int n = 0;
	SetPenColor("Yellow"); 
	drawRectangle(0.5, GetWindowHeight() / 4, GetWindowWidth() / 2, GetWindowHeight() / 2, 1);
	SetPenColor("Black");
	drawLabel(0.8, y + fH * 5 + 0.1, "输入路径：");
	drawLabel(0.8, y + 0.1, "输入文件名：");
	textbox(GenUIID(0), 0.8 + TextStringWidth("输入文件名："), y + fH * 4.7, GetWindowWidth() / 3, h, path1, sizeof(path1));
	textbox(GenUIID(0), 0.8 + TextStringWidth("输入文件名："), y , GetWindowWidth() / 3, h, filename1, sizeof(filename1));
	if( button(GenUIID(0), 0.5 + GetWindowWidth() / 4 - w / 2, GetWindowHeight() / 3, w, h0, "添加") && path1[0]){
		//path(path1, filename1);//打开文件进行操作
		flag_button = 1;
		path_book++;
		f_path[path_book] = 1;
		sprintf(path_opened[path_book], "%s%s", path1, filename1);
		fp[path_book] = fopen(path_opened[path_book], "w");//打开文件 
		while(path1[n] || filename1[n]){
			path1[n] = 0;
			filename1[n] = 0;
			n++;
		}//清空文本框 
	}
	if( button(GenUIID(0), 0.5 + GetWindowWidth() / 4 - w / 2, GetWindowHeight() * 4 / 15, w, h0, "删除") && path1[0]){
		//path(path1, filename1);//打开文件进行操作
		flag_button = 1;
		path_book++;
		f_path[path_book] = 1;
		sprintf(path_opened[path_book], "%s%s", path1, filename1);
		fp[path_book] = fopen(path_opened[path_book], "w");//打开文件 
		while(path1[n] || filename1[n]){
			path1[n] = 0;
			filename1[n] = 0;
			n++;
		}//清空文本框 
	}
	SetPenColor("Blue");
	drawRectangle(x_List - TextStringWidth("EEEEEEEE"), GetWindowWidth() / 30, GetWindowWidth() * 7 / 12, GetWindowHeight(), 1);
	int List_i = 1, row = 1;
	SetPenColor("Green");
	drawLabel(x_List - TextStringWidth("EEEEE"), y_List - fH , "已添加文件：");
	while(List_i <= path_book){
		if(f_path[List_i]){
			row++;
			drawLabel(x_List - TextStringWidth("EEEEE"), y_List - fH * (row + 1), path_opened[List_i]);//在界面显示已添加文件
		} 
		List_i++;
	}
}
#endif

#if defined(DISPLAY) //刷新 
void display(){
	DisplayClear();
	Menu();
	drawButtons();
	typeArea();
} 
#endif 

/*struct default {
	int a[10000];//a[1]存对应元素的Token编号 
	int n;//记录该类中的元素个数
} */


