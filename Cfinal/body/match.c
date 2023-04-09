#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include "global.h"
#include "match.h"
#include "predefine.h"


void mapping(int cnt_token, int sublen){
	int i, j, k; 
	// Mtoken[1].ch = "#includecstdio.h>";
    // Mtoken[2].ch = "D*p(Dv);";
	// Mtoken[3].ch = "Dv(){Dv;D*p;S(\"%d\",&v);p=p(v);I(p==.)P(\"wronginput!\v\");EP(\"%p\v\",p);R0;}";
	// Mtoken[4].ch = "D*p(Dv){D*p=.;D*p[0]={\"January\",\"February\",\"March\",\"April\",\"May\",\"June\",\"July\",\"August\",\"September\",\"October\",\"November\",\"December\"};I(v>=0&&v<=0){Rp[v-0];}ER.;}";
	// Mtoken[5].ch = "#includecstdio.h>";
	// Mtoken[6].ch = "D*p(Dv);";
	// Mtoken[7].ch = "D*p(Dv){D*p=.;D*p[0]={\"January\",\"February\",\"March\",\"April\",\"May\",\"June\",\"July\",\"August\",\"September\",\"October\",\"November\",\"December\"};I(v>=0&&v<=0){Rp[v-0];}ER.;}";
	// Mtoken[8].ch = "Dv(){Dv;D*p;S(\"%d\",&v);p=p(v);I(p==.)P(\"wronginput!\v\");EP(\"%p\v\",p);R0;}";
	char subToken[100001];//存放当次子串
    //char Token[100001][100001];//母串 //改为使用新的结构体数组
    int index_Token = 1,  pos = 0, index_subToken = 1;
    //取出键
	for(i = 1; i <= cnt_token; i++){
		pos = 0;
		for(j = pos; j <= strlen(Mtoken[i].ch) - sublen; j++){
			for(k = 0; k < sublen; k++){
				subToken[k] = Mtoken[i].ch[k + j];
			}
			subToken[sublen] = '\0';
			map_key(M, subToken, i, sublen);
		}
	}
	struct s_Token *p;
	/*测试输出
	for(j = 0;j < M_book; j++){
		printf("%s:", M[j]->contain);
		for(p = M[j]; p; p = p->next){
			printf("%d ", p->index);
		}
		printf("\n");
	}*/

    //构建对应值
}
/*测试用
int main (){
	mapping(8, 5);
	return 0;
}
*/

struct s_Token *map_create(/*int n, */char *subToken, int n){
	struct s_Token *head;//定义头节点
	int i = 0;
	head = (struct s_Token*)malloc(sizeof(struct s_Token));//分配地址
	while(*(subToken + i)){
		head->contain[i] = *(subToken + i);
		i++;
	}//存放当前表中不存在的新键
	head->contain[i] = '\0';
	head->index = n;
	head->next = NULL;//结束创建
	return head;
}

void map_add(struct s_Token *list, int n/*, char *subToken*/) {//
	struct s_Token *t, *in;
	in = (struct s_Token*)malloc(sizeof(struct s_Token));
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

void map_key(struct s_Token *list[], char *subToken/*, char *Token[]*/, int n, int sublen){//n为当前所在Token串的编号（不计入表中）,Token为当前串
	int now = 0, pos = 0, index = 0, flag = 0;//通过index遍历映射表
	// while (Token[start_pos][pos] && now < sublen){
	// 	if(subToken[now] == Token[index][pos]) 
	// 		now++;
	// 	else 
	// 		now = 0;
	// 	pos++;
	// }
	while (index < M_book/*list[index]->head[0]*/){
		if(M_book == 0){
			M[M_book] = map_create(subToken, n);
			M_book++;
			break;
		}
		if(strcmp(subToken, list[index]->contain) == 0 && judge(list[index], n) == 0){ //在内且在该Token内首次出现， 节点后移记录
			map_add(list[index], n);
			flag = 1;
			break;
		}	//链表
		if(strcmp(subToken, list[index]->contain) == 0 && judge(list[index], n)){ //在内且在该Token内首次出现， 节点后移记录
			flag = 1;
			break;
		}
		index++;
	}
	if(flag == 0){ // 不在内， 创建新键
		M[M_book] = map_create(subToken, n);
		M_book++;
	}
}

int judge(struct s_Token *M_now, int n){//判断该subToken所在的Token是否已经在映射表中被记录过
	int flag = 0; //flag记录是否找到对应子串,未出现则返回0
	struct s_Token *p;
	for(p = M_now; p; p = p->next){
		if(p->index == n){
			flag = 1;
			break;
		}
	}
	return flag;
}
