#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

struct token{
    char *ch/*[10000]*/;//储存这个token的具体内容比如“void swap(){int a = 1;........................}”
    char doc[100];//储存这个token所在文件的文件名比如“librarysystem.c”
    int startline;//这个token的第一行的行号
    int endline;//这个token最后一行的行号
}Mtoken[100000];



typedef struct s_Token{//链表表头存放当前串的信息（因为无需记录第一个出现的子串），而每次遍历都是从头开始的，故可将表头作为索引
    int index;//存放找到的
	char *contain;// 仅在存放表头时有效，即s_Token[i]->contain
    struct s_Token *next;
}LinkList;
LinkList *M[100001];
int M_book = 0;

LinkList *map_create(/*int n, */char *subToken);//遇到未加入映射表的subToken，建立新的键
void map_add(LinkList *list, int n/*, char *subToken*/);
void map_key(LinkList *list[], char *subToken/*, char *Token[]*/, int start_pos, int sublen);//构建映射表
int judge(LinkList *M_now, int n);//判断该subToken所在的Token是否已经在映射表中被记录过

int /*mapping_*/main (){//之后改成映射函数
	int cnt_token = 2, i = 1;
	Mtoken[1].ch = "ab";
    Mtoken[2].ch = "dnab";
	char subToken[100001];//存放当次子串
    //char Token[100001][100001];//母串 //改为使用新的结构体数组
    int index_Token = 1, sublen = 1, pos = 0, index_subToken = 1;
    //取出键
	for(i = 1; i <= cnt_token; i++){
		pos = 0;
		for(int j = pos; j <= strlen(Mtoken[i].ch) - sublen + 1; j++){
			for(int k = 0; k < sublen; k++){
				subToken[k] = Mtoken[i].ch[k + j];
			}
			subToken[sublen] = '\0';
			map_key(M, subToken, i, sublen);
		}
	}LinkList *p;
	//测试输出
	for(int j = 0;j <= M_book; j++){
		printf("%s",M[j]->contain);
		for(p = M[j]; p; p = p->next){
			printf("%d\n", p->index);
		}
	}//

    //构建对应值
}

LinkList *map_create(/*int n, */char *subToken){
	LinkList *head;//定义头节点
	head = (LinkList*)malloc(sizeof(LinkList));//分配地址
	head->contain = subToken; //存放当前表中不存在的新键
	head->next = NULL;//结束创建
	return head;
}

void map_add(LinkList *list, int n/*, char *subToken*/) {//
	LinkList *t, *in;
	in = (LinkList*)malloc(sizeof(LinkList));
	in->index = n;
	in->next = NULL;
	if(list == NULL) 
		list = in;
	else{
		t = list;
		while (t->next != NULL) 
			t = t->next;	
		t->next = in;//填充t节点的指针域，把t的指针域重新指向in
	}
}

void map_key(LinkList *list[], char *subToken/*, char *Token[]*/, int n, int sublen){//n为当前所在Token串的编号（不计入表中）,Token为当前串
	int now = 0, pos = 0, index = 0, flag = 0;//通过index遍历映射表
	// while (Token[start_pos][pos] && now < sublen){
	// 	if(subToken[now] == Token[index][pos]) 
	// 		now++;
	// 	else 
	// 		now = 0;
	// 	pos++;
	// }
	while (index <= M_book/*list[index]->head[0]*/){
		if(M_book == 0){
			M[M_book] = map_create(subToken);
			M_book++;
			break;
		}
		if(strcmp(subToken, list[index]->contain) == 0 && judge(list[index], n) == 0){ //在内且在该Token内首次出现， 节点后移记录
			map_add(list[index], n);
			flag = 1;
			break;
		}	//链表
		index++;
	}
	if(flag == 0){ // 不在内， 创建新键
		M[M_book] = map_create(subToken);
		M_book++;
	}
}

int judge(LinkList *M_now, int n){//判断该subToken所在的Token是否已经在映射表中被记录过
	int flag = 0; //flag记录是否找到对应子串,未出现则返回0
	LinkList *p;
	for(p = M_now; p; p = p->next){
		if(p->index == n){
			flag = 1;
			break;
		}
	}
	return flag;
}
