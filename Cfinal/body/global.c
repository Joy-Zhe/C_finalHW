#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


char path_opened[300000][300] = {{0}};//����Ѵ򿪵��ļ���·�� 
int path_book;//���ڱ����Ѵ򿪵��ļ���·�� 
int f_path[300000];
FILE *file[300000];
int M_book = 0;//ӳ����ڵ�������� 
int pair[10000];
int cnt_token = 1;//token������

struct token{
    char ch[100000];//储存这个token的具体内容比如“void swap(){int a = 1;........................}”
    char doc[100];//储存这个token所在文件的文件名比如“librarysystem.c”
    int startline;//这个token的第一行的行号
    int endline;//这个token最后一行的行号
}Mtoken[8000];

struct token Mtoken_copy[8000];

struct s_Token{//链表表头存放当前串的信息（因为无需记录第一个出现的子串），而每次遍历都是从头开始的，故可将表头作为索引
    int index;//存放找到的
	char contain[20];// 仅在存放表头时有效，即s_Token[i]->contain
    struct s_Token *next;
}*M[10000000];
