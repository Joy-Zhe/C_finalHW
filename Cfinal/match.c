#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

struct token{
    char ch[10000];//储存这个token的具体内容比如“void swap(){int a = 1;........................}”
    char doc[100];//储存这个token所在文件的文件名比如“librarysystem.c”
    int startline;//这个token的第一行的行号
    int endline;//这个token最后一行的行号
}Mtoken[100000];

typedef struct subToken{//链表表头存放当前串的信息（因为无需记录第一个出现的子串），而每次遍历都是从头开始的，故可将表头作为索引
    int index;//存放找到的
	char *head;// 仅在存放表头时有效，即subToken_index[i]->head
    struct subToken *next;
}LinkList;
LinkList *M[100001];

LinkList *map_create(int n, char *subToken);//遇到未加入映射表的subToken，建立新的键
void map_add(LinkList *list, int n/*, char *subToken*/);
void map_key(LinkList *list[], char *subToken/*, char *Token[]*/, int start_pos, int sublen);//构建映射表
int judge(char *s, char *f);//判断s是否在已有映射表中的当前键内

int /*mapping_*/main (){//之后改成映射函数
    char subToken[100001];//存放当次子串
    //char Token[100001][100001];//母串 //改为使用新的结构体数组
    int index_Token = 1, sublen = 0, pos = 0, index_subToken = 1;
    //取出键
    while(Mtoken[index_Token].ch[0]){
        for(int i = pos; i < pos + sublen; i++){
            subToken[i - pos] = Mtoken[index_Token].ch[i];
        }
        if(!Mtoken[index_Token].ch[pos + sublen]){
            pos = pos + sublen; //未到达此Token串的尾部则继续存放子串
        }else index_Token++;
		map_key(M, subToken/*, Token*/, index_Token, sublen);
    }
    //构建对应值
}

LinkList *map_create(int n, char *subToken){
	LinkList *head, *node, *end;//定义头节点，普通节点，尾部节点；
	head = (LinkList*)malloc(sizeof(LinkList));//分配地址
	end = head;         //若是空链表则头尾节点一样
	for (int i = 0; i < n; i++) {
		node = (LinkList*)malloc(sizeof(LinkList));
		node->head = subToken; //存放当前表中不存在的新键
		end->next = node;
		end = node;
	}
	end->next = NULL;//结束创建
	return head;
}

void map_add(LinkList *list, int n/*, char *subToken*/) {//
	LinkList *t = list, *in;
	while (t != NULL) 
		t = t->next;
	if (t != NULL) {
		in = (LinkList*)malloc(sizeof(LinkList));
		in->index = n;
		in->next = t->next;//填充in节点的指针域，也就是说把in的指针域指向t的下一个节点
		t->next = in;//填充t节点的指针域，把t的指针域重新指向in
	}
	else;
}

void map_key(LinkList *list[], char *subToken/*, char *Token[]*/, int start_pos, int sublen){//start_pos为当前所在Token串的编号（不计入表中）,Token为当前串
	int now = 0, pos = 0, index = 0;//通过index遍历映射表
	// while (Token[start_pos][pos] && now < sublen){
	// 	if(subToken[now] == Token[index][pos]) 
	// 		now++;
	// 	else 
	// 		now = 0;
	// 	pos++;
	// }
	while (list[index]->head[0]){
		if(now == sublen)
		if(judge(subToken, list[index]->head)){ //在内， 节点后移记录
			map_add(list[index], start_pos);
			}	//链表
		else // 不在内， 创建新键
			map_create(start_pos, subToken);
		else ;
		index++;
	}

}

int judge(char *s, char *f){
	int index = 0, pos = 0, pos_s = 0, flag = 0; //flag记录是否找到对应子串
	while (*(f + pos)){
		if(*(f + pos) == s[pos_s])
			pos_s++;
		else
			pos_s = 0;//不过既然sublen都是一样的，找不到是不是就直接下一个就行:P
		pos++;
		if(!s[pos_s]){
			flag = 1;
			break;
		}
	}
	return flag;
}