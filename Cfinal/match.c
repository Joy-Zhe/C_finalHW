#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

typedef struct subToken{//链表表头存放当前串的信息（因为无需记录第一个出现的子串），而每次遍历都是从头开始的，故可将表头作为索引
    int index;
	char head[10001] = "";// 仅在存放表头时有效，即subToken_index[i]->head
    struct subToken *next;
}LinkList;
LinkList *subToken_index[100001];

LinkList *creat(int n);
void change(LinkList *list,int n);
void delete(LinkList *list, int n);
void insert(LinkList *list, int n);
void map_key(LinkList *list, char *subToken, char *Token[], int start_pos, int sublen);
void judge(char *s, char *f);//判断s是否在f内

int main (){
    char subToken[100001];//存放当次子串
    char Token[100001][100001];//母串
    int index_Token = 1, sublen = 0, pos = 0;
    //取出键
    while(Token[index_Token][0]){
        for(int i = pos; i < pos + sublen; i++){
            subToken[i - pos] = Token[index_Token][i];
        }
        if(!Token[index_Token][pos + sublen]){
            pos = pos + sublen; //未到达此Token串的尾部则继续存放子串
        }else index_Token++;

    }
    //构建对应值
}

LinkList *create(int n){
	LinkList *head, *node, *end;//定义头节点，普通节点，尾部节点；
	head = (LinkList*)malloc(sizeof(LinkList));//分配地址
	end = head;         //若是空链表则头尾节点一样
	for (int i = 0; i < n; i++) {
		node = (LinkList*)malloc(sizeof(LinkList));
		scanf("%d", &node->index);
		end->next = node;
		end = node;
	}
	end->next = NULL;//结束创建
	return head;
}

void change(LinkList *list,int n) {//n为第n个节点
	LinkList *t = list;
	int i = 0;
	while (i < n && t != NULL) {
		t = t->next;
		i++;
	}
	if (t != NULL) {
		scanf("%d", &t->index);
	}
	else;
}

void delete(LinkList *list, int n) {
	LinkList *t = list, *in;
	int i = 0;
	while (i < n && t != NULL) {
		in = t;
		t = t->next;
		i++;
	}
	if (t != NULL) {
		in->next = t->next;
		free(t);
	}
	else;
}

void insert(LinkList *list, int n) {
	LinkList *t = list, *in;
	int i = 0;
	while (i < n && t != NULL) {
		t = t->next;
		i++;
	}
	if (t != NULL) {
		in = (LinkList*)malloc(sizeof(LinkList));
		scanf("%d", &in->index);
		in->next = t->next;//填充in节点的指针域，也就是说把in的指针域指向t的下一个节点
		t->next = in;//填充t节点的指针域，把t的指针域重新指向in
	}
	else;
}

void map_key(LinkList *list, char *subToken, char *Token[], int start_pos, int sublen){
	int now = 0, pos = 0, index = start_pos;
	while (Token[index][pos] && now < sublen){
		if(subToken[now] == Token[index][pos]) 
			now++;
		else 
			now = 0;
		pos++;
	}
	if(now == sublen)
		if(judge(subToken, M)) // 暴力循环？懒得写了
			{
			M[index_subToken].number = index;
			M[index_subToken] = M[index_subToken]->next;
			}	//链表，瞎写；可变数组也行（应该）
		else
			add index_subToken;
	else ;
}

void judge(char *s, char *f){
	int pos = 0;
	while (*(f + pos)){
		
	}
}