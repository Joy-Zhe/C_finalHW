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

int S2N (char *num);
void N2S(int num, char *s);

void Main (){
    InitGraphics();
	registerCharEvent(CharEventProcess);        // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerTimerEvent(TimerEventProcess);      // 定时器
	startTimer(TIMER_TOTAL, 10);
}

// 字符串转换整型 
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
	if( button(GenUIID(0), x + w, y, w, h, "查看输出") )
	{
		run(path_book, path_opened, file);
		clone_class(pair);
		output();
		system("output.txt");
	}
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
	static char delete_num[300] = "";
	static int flag_button = 0;//判断是否按下“添加”按钮， 按下为1 
	int n = 0, delete_book = 0;
	SetPenColor("Yellow"); 
	drawRectangle(0.5, GetWindowHeight() / 4, GetWindowWidth() / 2, GetWindowHeight() / 2, 1);
	SetPenColor("Black");
	drawLabel(0.8, y + fH * 5 + 0.1, "输入路径：");
	drawLabel(0.8, y + 0.1, "输入文件名：");
	textbox(GenUIID(0), 0.8 + TextStringWidth("输入文件名："), y + fH * 4.7, GetWindowWidth() / 3, h, path1, sizeof(path1));
	textbox(GenUIID(0), 0.8 + TextStringWidth("输入文件名："), y , GetWindowWidth() / 3, h, filename1, sizeof(filename1));
	if( button(GenUIID(0), 0.5 + GetWindowWidth() / 4 - w / 2, GetWindowHeight() / 3 + fH * 2.3, w, h0, "添加") && path1[0]){
		//path(path1, filename1);//打开文件进行操作
		flag_button = 1;
		path_book++;
		f_path[path_book] = 1;
		sprintf(path_opened[path_book], "%s%s\0", path1, filename1);
		file[path_book] = fopen(path_opened[path_book], "r+");//打开文件 
		while(path1[n] || filename1[n]){
			path1[n] = 0;
			filename1[n] = 0;
			n++;
		}//清空文本框 
	}
	drawLabel(0.5 + GetWindowWidth() / 4 - w / 2, GetWindowHeight() * 4 / 15, "需删除：");
	textbox(GenUIID(0), 0.5 + GetWindowWidth() / 4, GetWindowHeight() * 4 / 15 - 0.1, TextStringWidth("3000000"), fH * 1.5, delete_num, sizeof(delete_num));
	if( button(GenUIID(0), 0.5 + GetWindowWidth() / 4 - w / 2, GetWindowHeight() * 4 / 15 + fH * 2.3, w, h0, "删除") && delete_num[0]){
		delete_book = S2N(delete_num);
		if(delete_book > path_book) delete_book = 0;//越界，通过置零（节点0无用）解决 
		/*有bug,删去两个后会出问题导致下下个被删 
		while(f_path[delete_book] == 0) 
			delete_book++;//遇到已经删除过的编号，通过顺延来删除 
		*/
		f_path[delete_book] = 0;
		fclose(file[delete_book]);//关闭已删除文件 
		n = 0;
		while(delete_num[n])
		{
			delete_num[n] = 0;
			n++;
		}//清空文本框 
	}
	
	SetPenColor("Blue");
	drawRectangle(x_List - TextStringWidth("EEEEEEEE"), GetWindowWidth() / 30, GetWindowWidth() * 7 / 12, GetWindowHeight(), 1);
	int List_i = 1, row = 1;
	SetPenColor("Green");
	drawLabel(x_List - TextStringWidth("EEEEE"), y_List - fH , "已添加文件：");
	char List_index[10] = "";
	while(List_i <= path_book){
		if(f_path[List_i]){
			row++;
			N2S(List_i, List_index);
			drawLabel(x_List - TextStringWidth("EEEEEEE"), y_List - fH * (row + 1), List_index);
			drawLabel(x_List - TextStringWidth("EEEEE"), y_List - fH * (row + 1), path_opened[List_i]);//在界面显示已添加文件
		} 
		List_i++;
	}//输出已打开文件 
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
	}//重置编号 
	*/
}
#endif

#if defined(OUTPUT) //输出
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
//		fprintf(fp_out,"本行 为调试观察请忽略%d %d\n 路径%s \n开始行：%d   结束行：%d \n%s\n", i, pair[i], Mtoken_copy[i].doc, Mtoken[i].startline, Mtoken[i].endline, Mtoken_copy[i].ch);
		for(j = 1; j <= cnt_token; j++)
		{
			if(tree[i] == pair[j])
			{
				flag[j] = 1;
				fprintf(fp_out,"本行 为调试观察请忽略%d %d\n路径:  %s \n开始行：%d   结束行：%d \n%s\n", i, pair[j], Mtoken_copy[j].doc, Mtoken[j].startline, Mtoken[j].endline, Mtoken_copy[j].ch);
			}
		}
		fprintf(fp_out,"#####################################################################\n");
		fprintf(fp_out,"#####################################################################\n");
	}
	fclose(fp_out); 
}
#endif 

#if defined(DISPLAY) //刷新 
void display(){
	DisplayClear();
	Menu();
	drawButtons();
	typeArea();
	//output();
} 
#endif 






