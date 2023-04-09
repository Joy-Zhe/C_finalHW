#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "clone_pair.h"


//创建一个存放不同subtoken出现情况的映射表 
void clone_pair(int cnt_token, int sublen){
	int i, j, k, l;
	//对每个token依次检测
	for(i = 1; i <= cnt_token; i++)
	{
		int cnt[10000]={0};
		for(j = 0; j <= strlen(Mtoken[i].ch)-sublen;j++)
		{
			char tmp[1000];
	
			for(k = 0,  l = j; k<sublen;k++, l++)
			{
				tmp[k] = Mtoken[i].ch[l];
			}
			tmp[sublen] = '\0';
			//从映射表中所有区块进行遍历，找到此时subtoken对应的字符串在映射表中的位置 
			for(k = 0; k <= M_book;k++)
			{
				//判断此时选择的映射表位置是否正确 
				if(strcmp(tmp, M[k]->contain) == 0)
				{
					//判断正确，我们在曾经出现过包含subtoken的token位置处加一，意思是该token与我们正在检测的第i个token增加一点相似度 
					//在这里，我们只记录那些token编号大于i的token，这是为了避免重复 
					struct s_Token *p = M[k];
					while(p != NULL)
					{
						if(p->index > i) cnt[p->index]++;
						p = p->next;
					}
					break;
				}
			}
		
		}
		//top存储重复频度第一大、第二大、第三大......第k大的token位置编号 
		int top[1000];
		int flag[10000]={0};
		int topk = 2;
		for(k = 1; k <= topk; k++)
		{
			//max代表着第i个token后第k大的token位置编号，初始值是i+1，这是为了避免重复 
			int max = i + 1;
			for(l = i + 2; l <= cnt_token; l++)
			{
				if((cnt[l]>cnt[max]) && flag[l] == 0 || flag[max] > flag[l])
				{
					max = l;
				}
			}
			flag[max] = 1;
			top[k] = max;
		}
	 
		//先把每个token所对应的克隆对选择为自己，再开始匹配工作 
		pair[i] = i;
	
		//我们找到了重复度最高的topk个token的位置编号，但是可能会出现“即使是重复频度最高的几项，在数值上看依然很低，不构成克隆”
		//因此我们需要增加数值上的门槛，这里采用的是“一个长度为n的token一共能构成n-sublen+1个subtoken”
		//那么这里可以把门槛设置为 (n-sublen+1)*0.7

		while(topk >= 1)
		{
			int threshold = (strlen(Mtoken[i].ch) - sublen + 1 + strlen(Mtoken[top[topk]].ch) - sublen + 1) / 2 *0.6;
			if(cnt[top[topk]] < threshold) topk--;
			else break;
		}
		//如果一个满足门槛的其他token都没有，那就进入下一个token 
		if(topk < 1) continue;
		//找到topk个疑似克隆对象中编辑距离最小的那个
		int minpair = top[1];
		for(j = 2;j <= topk; j++)
		{
			if(lev(Mtoken[i].ch, Mtoken[top[j]].ch, 0, 0) < lev(Mtoken[i].ch, Mtoken[minpair].ch, 0, 0))
			{
				minpair = top[j];
			}
		}
		pair[i] = minpair;
	}
}
//Levenshtein Distance 编辑距离算法
int lev(char *a, char *b, int i, int j) 
{
	int len1 = strlen(a);
	int len2 = strlen(b);
	int levmap[len1+1][len2+1];
	for(i=0; i<=len1; i++)
	{
		levmap[i][0] = i;
	}
	for(j=0; j<=len2; j++)
	{
		levmap[0][j] = j;
	}
	for(i=1; i<=len1; i++)
	{
		for(j=1; j<=len2; j++)
		{
			levmap[i][j] = min3(levmap[i-1][j]+1, levmap[i][j-1]+1,levmap[i-1][j-1]-isSame(a, b, i, j));
		}
	}
	return levmap[len1][len2];
}

//返回三个里最小的数 
int min3(int a, int b, int c)
{
	int tmp = a;
	if(a>b) tmp = b;
	if(tmp>c) tmp = c;
	return tmp;
}

//检测a[i],b[j]是否相等，不相等返回 
int isSame(char *a, char *b, int i, int j)
{
	if(a[i] != b[j]) return 1;
	if(a[i] == b[j]) return 0;
	
}
