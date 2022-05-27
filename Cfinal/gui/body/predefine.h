#ifndef _PREDEFINE_H_
#define _PREDEFINE_H_
 
static char path_opened[300000][300] = "";//存放已打开的文件、路径 
static int path_book;//用于遍历已打开的文件、路径 

void display();
void Menu();
void ranking(FILE *op);
void drawButtons();
void numtos(int num, char *s);

//对所用值进行初始化 


#endif
