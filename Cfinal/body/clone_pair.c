#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "global.h"
#include "clone_pair.h"


//����һ����Ų�ͬsubtoken���������ӳ��� 
void clone_pair(int cnt_token, int sublen){
	int i, j, k, l;
	//��ÿ��token���μ��
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
			//��ӳ���������������б������ҵ���ʱsubtoken��Ӧ���ַ�����ӳ����е�λ�� 
			for(k = 0; k <= M_book;k++)
			{
				//�жϴ�ʱѡ���ӳ���λ���Ƿ���ȷ 
				if(strcmp(tmp, M[k]->contain) == 0)
				{
					//�ж���ȷ���������������ֹ�����subtoken��tokenλ�ô���һ����˼�Ǹ�token���������ڼ��ĵ�i��token����һ�����ƶ� 
					//���������ֻ��¼��Щtoken��Ŵ���i��token������Ϊ�˱����ظ� 
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
		//top�洢�ظ�Ƶ�ȵ�һ�󡢵ڶ��󡢵�����......��k���tokenλ�ñ�� 
		int top[1000];
		int flag[10000]={0};
		int topk = 2;
		for(k = 1; k <= topk; k++)
		{
			//max�����ŵ�i��token���k���tokenλ�ñ�ţ���ʼֵ��i+1������Ϊ�˱����ظ� 
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
	 
		//�Ȱ�ÿ��token����Ӧ�Ŀ�¡��ѡ��Ϊ�Լ����ٿ�ʼƥ�乤�� 
		pair[i] = i;
	
		//�����ҵ����ظ�����ߵ�topk��token��λ�ñ�ţ����ǿ��ܻ���֡���ʹ���ظ�Ƶ����ߵļ������ֵ�Ͽ���Ȼ�ܵͣ������ɿ�¡��
		//���������Ҫ������ֵ�ϵ��ż���������õ��ǡ�һ������Ϊn��tokenһ���ܹ���n-sublen+1��subtoken��
		//��ô������԰��ż�����Ϊ (n-sublen+1)*0.7

		while(topk >= 1)
		{
			int threshold = (strlen(Mtoken[i].ch) - sublen + 1 + strlen(Mtoken[top[topk]].ch) - sublen + 1) / 2 *0.6;
			if(cnt[top[topk]] < threshold) topk--;
			else break;
		}
		//���һ�������ż�������token��û�У��Ǿͽ�����һ��token 
		if(topk < 1) continue;
		//�ҵ�topk�����ƿ�¡�����б༭������С���Ǹ�
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
//Levenshtein Distance �༭�����㷨
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

//������������С���� 
int min3(int a, int b, int c)
{
	int tmp = a;
	if(a>b) tmp = b;
	if(tmp>c) tmp = c;
	return tmp;
}

//���a[i],b[j]�Ƿ���ȣ�����ȷ��� 
int isSame(char *a, char *b, int i, int j)
{
	if(a[i] != b[j]) return 1;
	if(a[i] == b[j]) return 0;
	
}
