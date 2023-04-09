
#include <stdio.h>
#include "predefine.h"
#include "global.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include<math.h>
#include "token.h"

void token_input_process(struct token *token)
{
	input_vname(token);
    //input_vname_check();
    input_pname(token);
    //input_pname_check();
    input_sname(token->ch);
    //input_sname_check();

}

void token_process(struct token *token)
{
    changevname_all(token);
    changepname_all(token);
    change_struct(token->ch);
    change_type(token);
    changekeyword(token->ch);

    changecompare(token->ch);
    changenumber(token->ch);

    change_function(token->ch);
    deletespace(token->ch);
    // puts(token->ch);
}

void input_vname_check(void)
{
    int i;
    int j;
    if(isname(Variable_name[0][0])==0 ||check_isvalid(Variable_name[0])==0){
       strcpy(Variable_name[0], "##");
    }


    for (i = 1; i < vname_count; i++)
    {
        //printf("Variable_name[%d],%c\n",i,Variable_name[i][0]);
        if (isname(Variable_name[i][0])==0 ||check_isvalid(Variable_name[i])==0)
        {
            //printf("v_wrong=%d,%s\n",i,Variable_name[i]);
            
            strcpy(Variable_name[i], "##");
        }
    }
}

void input_pname_check(void)
{
    int i;
    int j;
    if(isname(Pointer_name[0][0])==0 ||check_isvalid(Pointer_name[0])==0){
        strcpy(Pointer_name[0], "##");
    }
    for (i = 1; i < pname_count; i++)
    {
        if (isname(Pointer_name[i][0])==0 ||check_isvalid(Pointer_name[i])==0)
        {
            strcpy(Pointer_name[i], "##");
        }
    }
}

void input_sname_check(void)
{
    int i;
    int j;
    if(isname(Struct_name[0][0])==0 ||check_isvalid(Struct_name[0])==0){
        strcpy(Struct_name[0], "##");
    }
    for (i = 1; i < sname_count; i++)
    {
        if (isname(Struct_name[i][0])==0 ||check_isvalid(Struct_name[i])==0)
        {
            strcpy(Struct_name[i], "##");
        }
    }
}
//判断名称是否合法
int check_isvalid(char*input){
    int i;
    int flag_isvalid=1;
    for(i=0;i<type_name1_count; i++){
        if(strcmp(type_name1[i],input)==0){
            flag_isvalid=0;
            break;
        }
    }
    for(i=0;i<kname_count; i++){
        if(strcmp(keyword[i],input)==0){
            flag_isvalid=0;
            break;
        }
    }
    return flag_isvalid;

}



void input_sname(char *sptoken)
{
    int i;
    int j, k;
    char *pmove = sptoken;
    char s[10] = {"struct"};
    while (*pmove != '\0')
    {
        if (issame(pmove, s) == 1) //比对寻找”struct”字符
        {                          //跳过struct
            //printf("pmove0=%c ", *pmove);
            while (*pmove != ' ' && *pmove != '*' && *pmove != '\n' && *pmove != '{')
            {
                pmove++;
            }
           //printf("pmove1=%c ", *pmove);
            while (*pmove == ' ' || *pmove == '\n') //跳过struct后空格
            {
                pmove++;
            }

            //printf("pmove2=%c ", *pmove);

            while (*pmove != ' ' && *pmove != '*' && *pmove != '\n' && *pmove != '{'&&*pmove != ')'&& *pmove != '(')
            {
                pmove++;
            }//printf("pmove3=%c ", *pmove);
            if (*pmove == '{')
            {
                continue;
            }
            pmove++;
           //printf("pmove4=%c ", *pmove);
            while (*pmove == ' ' || *pmove == '\n') //跳过类型名后空格
            {
                pmove++;
            }
            //printf("pmove5=%c ", *pmove);
            if (*pmove == '*')
            {
                pmove++;
            }
            while (*pmove == ' ' || *pmove == '\n') //跳过*后空格
            {
                pmove++;
            }
            //printf("pmove6=%c \n", *pmove);
            if(isname(*pmove)!=1){
                     continue;
            }
            for (i = 0; isname(*pmove) == 1; i++) //读入结构变量名，存在数组中
            {
                Struct_name[sname_count][i] = *pmove;
                pmove++;
            }
            Struct_name[sname_count][i] = '\0';
            // printf("sname=%s\n",Struct_name[sname_count]);
            sname_count++;
            i = 0;

            while (*pmove != ';' && *pmove != '(' && *pmove != ')')
            {
                if (*pmove == ',')
                {
                    pmove++;
                    while (*pmove == ' ' || *pmove == '\n')
                    {
                        pmove++;
                    }
                    if (*pmove == '*')
                    {
                        pmove++;
                    }
                    while (*pmove == ' ' || *pmove == '\n')
                    {
                        pmove++;
                    }
                    for (i = 0; isname(*pmove) == 1; i++) //读入结构变量名，存在数组中
                    {
                        Struct_name[sname_count][i] = *pmove;
                        pmove++;
                    }
                    Struct_name[sname_count][i] = '\0';
                    //printf("sname=%s\n", Struct_name[sname_count]);
                    sname_count++;

                    pmove--;
                }
                pmove++;
            }
        }
        pmove++;
    }
}

//�������������ڽṹ���󸴺ϱ�ʾһ�������������滻Ϊs,����->,.��[]�Ա���Ƕ�ײ�������������
void change_struct(char *sptoken)
{
    char *p = sptoken;
    int i;
    int flag = 0;      //�ṹ������ָʾ��
    int flagstart = 0; //��������ʿ�ʼָʾ��
    while (*p != '\0')
    {
        for (i = 0; i < sname_count; i++)
        {

            if (issame(p, Struct_name[i]) == 1)
            {
                // printf("p=%c\n",*p);
                *p = 's';

                flag = 1;
                flagstart = 1;
                p++;
                break;
            }
        }

        if (flag == 1 && flagstart == 0) //�����ڽṹ�����Ҳ��ڽṹ�����ʵ���
        {
            if (isname(*p) == 1)
            {
                *p = ' ';
            }
            else if (isname(*p) == 0 && *p != '[' && *p != ']' && *p != '.' && *p != '-' && *p != '>' && *p != ' ') //��ɾ����Щ����
            {
                flag = 0;
            }
            p++;
        }
        else if (flag == 0)
        {
            p++;
        }

        if (flagstart == 1) //���ṹ�����ʶ�ȡ��������flagstart���0
        {
            flagstart = 0;
        }
    }
}

void change_function(char *sptoken)
{
    char *pmove = sptoken;
    char *pflag = NULL; //���ڱ�Ǻ�����ͷ����λ��
    int count = 0;
    while (*pmove != '\0')
    {
        if (isname(*pmove) == 1)
        {

            count = 0;
            pflag = pmove;
            while (isname(*pmove) == 1)
            {
                pmove++;
                count++;
            }
            //��Ϊ����������Ϊ�����ַ�����ֹ�����硰while(i)��������
            if (count == 1)
            {
                continue;
            }
            if (*pmove == ' ')
            {
                while (*pmove == ' ')
                {
                    pmove++;
                }
            }
            //��������Ϊf
            if (*pmove == '(')
            {

                *pflag = 'f';
                pflag++;
                while (pflag < pmove)
                {
                    *pflag = ' ';
                    pflag++;
                }
            }
        }
        pmove++;
    }
}

void deletespace(char *sptoken)
{
    char *p = sptoken;

    while (*p != '\0')
    {
        if (*p == ' ' || *p == '\n' || *p == '\r'||*p=='\t'||*p == '\v')
        {
            delete (p);
            
        }
        else
        {
            p++;
        }
    }
}

void delete (char *p)
{
    int i;
    //��p���ַ���ǰ�ƶ�һ��
    for (i = 1; *(p + i) != '\0'; i++)
    {
        *(p + i - 1) = *(p + i);
    }
    *(p + i - 1) = '\0';
}

void change_type(struct token *ptoken)
{
    char *p = ptoken->ch;

    while (*p != '\0')
    {
        if (istype1(p))
        {
            *p = 'D';
            p++;
            while (*p != ' ')
            {

                *p = ' ';
                p++;
            }
        }
        else if (istype2(p))
        {

            *p = 'D';
            p++;
            while (*p != ' ' && *p != '*')
            {

                *p = ' ';
                p++;
            }
        }
        p++;
    }
}

void changenumber(char *sptoken)
{
    char *pmove = sptoken;
    int i;
    int j;
    int flag = 0;
    while (*pmove != '\0')
    {
        //�����ĵ�һ�����ֳ��ֻ�Ϊ0
        if (*pmove >= '0' && *pmove <= '9' && flag == 0)
        {
            *pmove = '0';
            flag = 1;
        }
        //�����ÿո����
        else if (*pmove >= '0' && *pmove <= '9' && flag == 1)
        {
            *pmove = ' ';
        }
        //���ִ�����
        else
        {
            flag = 0;
        }
        pmove++;
    }
}

void changecompare(char *sptoken)
{
    char *pmove = sptoken;
    int i;
    int j;
    int len = 1;
    while (*pmove != '\0')
    {
        for (i = 0; i < cname_count; i++)
        {
            if (issame_basic(pmove, compareword[i]) == 1)
            {
                //��ֹ->�е�>���滻
                if (*(pmove - 1) == '-')
                {
                    break;
                }
                *pmove = 'c';
                if (*(pmove + 1) == '=')
                {
                    len = 2;
                }
                else
                {
                    len = 1;
                }

                for (j = 1; j < len; j++)
                {
                    *(pmove + j) = ' ';
                }
            }
        }
        pmove++;
    }
}

void changekeyword(char *sptoken)
{

    char *pmove = sptoken;
    int i;
    int j;
    while (*pmove != '\0')
    {
        for (i = 0; i < kname_count; i++)
        {
            if (issame(pmove, keyword[i]) == 1)
            {
                *pmove = *pmove - 'a' + 'A'; //�ؼ���������ĸ��д���
                for (j = 1; j < strlen(keyword[i]); j++)
                {
                    *(pmove + j) = ' ';
                }
            }
        }
        pmove++;
    }
}

void input_vname(struct token *ptoken)
{

    int i=0;
    int j=0, k=0;
    char *p = ptoken->ch;

    while (*p != '\0')
    {
        //�ж��Ƿ�Ϊ��ͨ��������
        if (istype1(p))
        {
            //�����������Ϳո�

            p = skip_char(p);

            while (*p == ' ')
            {
                p++;
            }

            k = 0;
            if (*p == '*')
            {
                break;
            }
            // printf("pc=%c\n", *p);
            //���������
            // printf("now=%c\n",*p);
            while (isname(*p) != 0)
            {
                Variable_name[vname_count][k] = *p;
                p++;
                k++;
            }
            Variable_name[vname_count][k] = '\0';
            //printf("vname=%s\n",Variable_name[vname_count]);
            vname_count++;
            k = 0;
            int flag_break=0;
            while (*p != ';'&&*p!='('&&*p!=')'&&*p!='{'&&*p!='}'&&flag_break==0)
            {

                if (*p == ',')
                {
                    p++;
                    while (*p == ' ')
                    {
                        p++;
                    }
                    if (*p == '*')
                    {
                        p++;
                        while (*p == ' ')
                        {
                            p++;
                        }
                        // printf("now=%c\n",*p);

                        while (isname(*p) != 0)
                        {
                            Pointer_name[pname_count][k] = *p;
                            p++;
                            k++;
                        }
                        p--;
                        Pointer_name[pname_count][k] = '\0';
                        //printf("pname=%s\n", Pointer_name[pname_count]);
                        pname_count++;
                        int j;
                        for(j=0;j<type_name1_count;j++){
                            if(strcmp(Variable_name[vname_count-1],type_name1[j])==0){
                                vname_count--;
                                flag_break=1;
                                p=p-strlen(type_name1[j])-1;
                                break;
                            }
                        }
                        k = 0;
                    }
                    else
                    {
                        // printf("now=%c\n",*p);
                        while (isname(*p) != 0)
                        {
                            Variable_name[vname_count][k] = *p;
                            p++;
                            k++;
                        }
                        p--;
                        Variable_name[vname_count][k] = '\0';
                        vname_count++;
                        int j;
                        for(j=0;j<type_name1_count;j++){
                            if(strcmp(Variable_name[vname_count-1],type_name1[j])==0){
                                vname_count--;
                                flag_break=1;
                                p=p-strlen(type_name1[j])-1;
                                break;
                            }
                        }



                        //printf("vname=%s\n",Variable_name[vname_count]);
                        
                        k = 0;
                    }
                }

                p++;
            }
        }
        else
            p++;
    }
}

void input_pname(struct token *ptoken)
{

    int i;
    int j, k;
    char *p = ptoken->ch;

    while (*p != '\0')
    {

        if (istype2(p))
        {
            // printf("cfind=%c\n", *p);

            while (*p != ' ' && *p != '*')
            {
                p++;
            }
            // printf("%c\n", *p);
            while (*p == ' ')
            {
                p++;
            }

            p++;
            while (*p == ' ')
            {
                p++;
            }

            k = 0;
            while (isname(*p) != 0)
            {
                Pointer_name[pname_count][k] = *p;
                p++;
                k++;
            }
            Pointer_name[pname_count][k] = '\0';
            // printf("pname=%s\n",Pointer_name[pname_count]);
            pname_count++;

            k = 0;
            int flag_break=0;
            while (*p != ';'&&*p!='('&&*p!=')'&&flag_break==0)
            {

                if (*p == ',')
                {
                    p++;
                    while (*p == ' ')
                    {
                        p++;
                    }
                    if (*p == '*')
                    {
                        p++;
                        while (*p == ' ')
                        {
                            p++;
                        }
                        // printf("now=%c\n",*p);

                        while (isname(*p) != 0)
                        {
                            Pointer_name[pname_count][k] = *p;
                            p++;
                            k++;
                        }
                        p--;
                        Pointer_name[pname_count][k] = '\0';
                        // printf("pname=%s\n", Pointer_name[pname_count]);
                        pname_count++;
                        int j;
                        for(j=0;j<type_name1_count;j++){
                            if(strcmp(Variable_name[vname_count-1],type_name1[j])==0){
                                vname_count--;
                                flag_break=1;
                                p=p-strlen(type_name1[j])-1;
                                break;
                            }
                        }
                        k = 0;
                    }
                    else
                    {
                        // printf("now=%c\n",*p);
                        while (isname(*p) != 0)
                        {
                            Variable_name[vname_count][k] = *p;
                            p++;
                            k++;
                        }
                        p--;
                        Variable_name[vname_count][k] = '\0';
                        // printf("vname=%s\n",Variable_name[vname_count]);
                        vname_count++;
                        int j;
                        for(j=0;j<type_name1_count;j++){
                            if(strcmp(Variable_name[vname_count-1],type_name1[j])==0){
                                vname_count--;
                                flag_break=1;
                                p=p-strlen(type_name1[j])-1;
                                break;
                            }
                        }
                        k = 0;
                    }
                }

                p++;
            }
        }
        else
            p++;
    }
}

int isname(char c)
{
    if (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z' || c == '_' || c >= '0' && c <= '9')
        return 1;
    else
        return 0;
}

int istype1(char *p)
{

    int i;
    int j;
    int flag = 0;
    for (i = 0; i < type_name1_count; i++)
    {
        flag = 1;
        //����������������ȶ�
        for (j = 0; type_name1[i][j] != '\0'; j++)
        {
            if (*(p + j) != type_name1[i][j])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {

            break;
        }
    }
    //�˺���������ͨ��������������Ҫ�ų�ָ�붨������
    if (isname(*(p + j)) == 1 || *(p + j) == '*' || *(p + j + 1) == '*')
    {
        flag = 0;
    }

    return flag;
}

int istype2(char *p)
{

    int i;
    int j;
    int flag = 0;

    for (i = 0; i < type_name1_count; i++)
    {
        flag = 1;
        //���β���ָ��������
        for (j = 0; type_name1[i][j] != '\0'; j++)
        {
            if (*(p + j) != type_name1[i][j])
            {
                flag = 0;
                break;
            }
        }
        if (flag == 1)
        {
            // printf("1find=%s\n", type_name1[i]);
            // printf("c=%c\n", *(p+j));
            while (*(p + j) == ' ')
            {
                j++;
            }
            // printf("c=%c\n", *(p+j));
            if (*(p + j) == '*')
            {
                // printf("2find=%s\n", type_name1[i]);
                break;
            }
            else
            {
                flag = 0;
            }
        }
    }

    return flag;
}

char *skip_char(char *p)
{

    int i;
    for (i = 0; *p != ' '; i++, p++)
        ;
    return p;
}

void changevname(char *sptoken)
{

    struct name *p = (struct name *)malloc(sizeof(struct name));
    find_v(sptoken, Variable_name, p);
    //��ͨ��������Ϊv
    if (p->loc_token != NULL)
    {
        char *pmove;
        pmove = p->loc_token;
        *pmove = 'v';
        pmove++;
        while (isname(*pmove))
        {
            *pmove = ' ';
            pmove++;
        }
    }
}

void changevname_all(struct token *ptoken)
{
    char *p = ptoken->ch;
    int i = 0;
    while (flag_vnameappear == 1)
    {
        changevname(p);
        p++;
    }
}

void changepname(char *sptoken)
{

    struct name *p = (struct name *)malloc(sizeof(struct name));
    find_p(sptoken, Pointer_name, p);
    //ָ���������Ϊp
    if (p->loc_token != NULL)
    {
        char *pmove;
        pmove = p->loc_token;
        *pmove = 'p';
        pmove++;
        while (isname(*pmove))
        {
            *pmove = ' ';
            pmove++;
        }
    }
}

void changepname_all(struct token *ptoken)
{

    char *p = ptoken->ch;

    while (flag_pnameappear == 1)
    {
        changepname(p);

        p++;
    }
}

void find_v(char *stoken, char store[100][100], struct name *p)
{

    char *p_token = NULL; //��¼��������token��λ��
    char *p_store = NULL; //��¼�������ڱ������洢�������λ��
    char *pmove = stoken;
    int flag_isfind = 0; //�������ҵ���ʶ��
    int i=0;
    while (*pmove != '\0')
    {
        for (i = 0; i < vname_count; i++)
        {
            if (issame(pmove, store[i]) == 1)
            {
                //�洢���ݵ��������洢�ṹ
                p_token = pmove;
                p_store = store[i];
                flag_isfind = 1;
                flag_vnameappear = 1;

                break;
            }
        }
        if (flag_isfind == 1)
        {
            break;
        }
        
        pmove++;
    }
    //������δ����
    if (*pmove == '\0')
    {

        flag_vnameappear = 0;
        p->loc_token = NULL;
        p->loc_store = NULL;
    }
    //����������
    else
    {
        p->loc_token = p_token;
        p->loc_store = p_store;
    }
}

void find_p(char *stoken, char store[100][100], struct name *p)
{

    char *p_token = NULL; //��¼ָ������token��λ��
    char *p_store = NULL; //��¼ָ�����ڱ������洢�������λ��
    char *pmove = stoken;
    int flag_isfind = 0; //ָ�����ҵ���ʶ��
    int i;
    while (*pmove != '\0')
    {
        for (i = 0; i < pname_count; i++)
        {
            if (issame(pmove, store[i]) == 1)
            {
                //�洢���ݵ�ָ�����洢�ṹ
                p_token = pmove;
                p_store = store[i];
                flag_isfind = 1;
                flag_pnameappear = 1;

                break;
            }
        }
        if (flag_isfind == 1)
        {
            break;
        }
        pmove++;
    }
    //ָ����δ����
    if (*pmove == '\0')
    {

        flag_pnameappear = 0;
        p->loc_token = NULL;
        p->loc_store = NULL;
    }
    //ָ�����ѳ���
    else
    {
        p->loc_token = p_token;
        p->loc_store = p_store;
    }
}

//ʶ����ַ����󲻿�ֱ�ӽӿ���Ϊ���������ַ�
int issame(char *p, char *s)
{
    int i;
    int flag = 1;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (p[i] != s[i])
        {
            flag = 0;
            break;
        }
    }
    //�жϴ��ַ����Ƿ�Ϊһ���������е�һ����
    if (isname(p[i]) == 1)
    {
        flag = 0;
    }
    if(isname(p[-1])==1){
        flag=0;

    }
    return flag;
}
//������issame
int issame_basic(char *p, char *s)
{
    int i;
    int flag = 1;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (p[i] != s[i])
        {
            flag = 0;
            break;
        }
    }
    if(isname(p[-1])==1){
        flag=0;

    }

    return flag;
}
