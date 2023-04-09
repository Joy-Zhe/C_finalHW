#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "global.h"
#include "block_divide.h"

void block_divide(int cnt_file, char *line, char path_opened[300000][300], FILE *file[])
{
	int t, i = 1, j, k;
	int startline, endline, cnt;
	int cnt_openpare = 0;//ǰ����{����
	int cnt_closepare = 0;//������}����
	int flag_semicolon = 0;//��¼�Ƿ������δ�����������е�;
	int cur_line;//��ǰ�ڶ�ȡ���ǵڼ���
	int cur_file;//��ǰ�ڶ��ڼ����ļ�
    for (t = 1; t <= cnt_file; t++)
    {
        file[t] = fopen(path_opened[t], "r+");
        if (!file[t])
        {
            printf("%s ��������\n", path_opened[t]);
        }
        cur_line = 0;
        int flag_annotation = 0;
        int flag_start = 0;
        while (fgets(line, 100000, file[t]))
        {
            cur_line++;
            int n = strlen(line);
            int flag_hash = 0;
            int flag_quotation = 0;
            int cnt_temp=0;//��¼#����ǰ�ж��ٷǿ��ַ����ֹ�
            for (i = 0; line[i] != '\0'; i++)
            {
                
                if (line[i] != '\n' || line[i] != '\r' || line[i] != 9 || line[i] != 32)
                {
                    cnt_temp++;
                }
                if (line[i] == '#' && cnt_temp == 1) flag_hash = 1;//���������һ����#��ͷֱ������
                if (line[i] == '"')
                {
                    flag_quotation = 1;
                }
                
                if (line[i] == '"' && flag_quotation == 1)
                {
                	flag_quotation = 0;
                }
                if (line[i] == '/' && line[i + 1] == '/' && flag_quotation == 0)
                {
                    line[i] = '\n';
                    line[i + 1] = '\0';
                }
                if (line[i] == '/' && line[i + 1] == '*')
                {
                	flag_annotation = 1;
				}
				if (line[i] == '*' && line[i + 1] == '/')
                {
                	flag_annotation = 0;
                	line[i] = 0;
                	line[i + 1] = 0;
                	i = i + 2;
				}
				if (flag_annotation == 1)
				{
					line[i] = 0;
				}
                if (line[i] == '{') cnt_openpare++;
                if (line[i] == '}') cnt_closepare++;
                if (line[i] == ';') flag_semicolon = 1;
            }
            int n_line = strlen(line) ;    
        	int flag_return = 0 ;
        	
            //�������һ����ͨ����䣨;��β��һ�н�����
            if (strlen(line) > 0 && flag_start == 0)
            {
            	flag_start = 1;
            	Mtoken[cnt_token].startline = cur_line;
			}
            if (cnt_openpare == 0 && cnt_closepare == 0 && flag_semicolon == 1)
            {
            	flag_start = 0;
                Mtoken[cnt_token].startline = Mtoken[cnt_token].endline = cur_line;
                flag_semicolon = 0;
                cnt_token++;
                strcpy(Mtoken[cnt_token-1].ch + strlen(Mtoken[cnt_token-1].ch), line);
            	strcpy(Mtoken[cnt_token-1].doc, path_opened[t]);
            }
            //�������һ�������飨������ĵ�һ����;��β��{���ܳ����ں�����ڶ��У�
            /*if (cnt_openpare == 0 && cnt_closepare == 0 && flag_semicolon == 0)
            {
                cnt_token++;
                Mtoken[cnt_token].startline = cur_line;
                if(startline != -1) Mtoken[cnt_token].startline = cur_line;
            }*/
            else if (flag_hash == 1)
			{
				flag_start = 0;
                Mtoken[cnt_token].startline = Mtoken[cnt_token].endline = cur_line;
                flag_semicolon = 0;
                cnt_token++;
                strcpy(Mtoken[cnt_token-1].ch + strlen(Mtoken[cnt_token-1].ch), line);
            	strcpy(Mtoken[cnt_token-1].doc, path_opened[t]);
			} 
            else if (cnt_openpare > 0 && cnt_closepare > 0 && cnt_openpare == cnt_closepare)
            {
            	flag_start = 0;
                cnt_openpare = 0;
                cnt_closepare = 0;
                Mtoken[cnt_token].endline = cur_line;
                flag_semicolon = 0;
                cnt_token++;
                strcpy(Mtoken[cnt_token-1].ch + strlen(Mtoken[cnt_token-1].ch), line);
            	strcpy(Mtoken[cnt_token-1].doc, path_opened[t]);
            }
            else {
            	strcpy(Mtoken[cnt_token].ch + strlen(Mtoken[cnt_token].ch), line);
            	strcpy(Mtoken[cnt_token].doc, path_opened[t]);
			}
        }
    }
    cnt_token--;
    for(i = 1;i <= cnt_token;i++)
	{
		Mtoken_copy[i] = Mtoken[i];
	}
}


