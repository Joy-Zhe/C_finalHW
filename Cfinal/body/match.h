#ifndef _MATCH_H
#define _MATCH_H



struct s_Token *map_create(/*int n, */char *subToken, int n);//遇到未加入映射表的subToken，建立新的键, n为第一次遇到时的Token编号，后续编号从M[]->next开始

void map_add(struct s_Token *list, int n/*, char *subToken*/);

void map_key(struct s_Token *list[], char *subToken/*, char *Token[]*/, int start_pos, int sublen);//构建映射表

int judge(struct s_Token *M_now, int n);//判断该subToken所在的Token是否已经在映射表中被记录过

#endif
