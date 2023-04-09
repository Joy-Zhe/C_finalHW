#ifndef _BLOCK_DIVIDE_H
#define _BLOCK_DIVIDE_H
extern int cnt_token;
static char Variable_name[100][100];
static char Pointer_name[100][100];
static char Struct_name[100][100];
static char type_name1[100][100] = {"char", "short", "int", "long", "float", "double", "struct","void","FILE"};
// static char type_name2[100][100] = {"char*", "short*", "int*", "long*", "float*", "double*", "char *", "short *", "int *", "long *", "float *", "double *"};
static char keyword[100][100] = {"for", "do", "while", "break", "continue", "if", "else", "goto", "switch", "case", "default", "return", "auto", "extern", "register", "static", "const", "sizeof", "typedef", "volatile", "malloc", "calloc", "free", "unsigned", "return","NULL","printf","scanf"};
static char compareword[100][3] = {">", "<", "==", "!="};
//�����鴢�������
static int vname_count = 0;
static int pname_count = 0;
static int kname_count = 28;
static int cname_count = 4;
static int sname_count = 0;
static int type_name1_count = 9;//修改此变量可以添加变量类型

static int flag_pnameappear = 1;
static int flag_vnameappear = 1;

extern int pair[10000];

//���������
struct name
{
    char *loc_token; //ָ�����token��λ��
    char *loc_store; //ָ��������洢������λ��
};

//�����ַ���������ַ�������ѯ���ĵ�һ���ַ�λ��д��p;������ר��
void find_p(char *stoken, char store[100][100], struct name *p);

//�����ַ���������ַ�������ѯ���ĵ�һ���ַ�λ��д��p��ָ����ר��
void find_v(char *stoken, char store[100][100], struct name *p);

//�滻������Ϊv,ֻ�滻���ȶ�����
void changevname(char *ptoken);

//�滻ָ����Ϊp,ֻ�滻���ȶ�����
void changepname(char *ptoken);

//�滻���б�����
void changevname_all(struct token *ptoken);

//�滻����ָ����
void changepname_all(struct token *ptoken);

//�жϵ����Ƿ���ȣ���s��βΪ\0�����Ƚϣ������жϽ�β����һ�������Ƿ�Ϊ��������Ч�ַ�
int issame(char *p, char *s);

//���жϵ����Ƿ���ȣ���s��βΪ\0�����Ƚϣ�
int issame_basic(char *p, char *s);

//��ʶ�𵽵ı������������������
void input_vname(struct token *ptoken);

//��ʶ�𵽵�ָ��������ָ��������
void input_pname(struct token *ptoken);

//�ж���ָ�ַ��Ƿ�Ϊһ���������Ŀ�ͷ
int istype1(char *p);

//�ж���ָ�ַ��Ƿ�Ϊһ��ָ���������Ŀ�ͷ
int istype2(char *p);

//������ǰ����
char *skip_char(char *p);

//�ж��Ƿ��ܹ������ڱ�������
int isname(char);

//�����������滻
void change_type(struct token *ptoken);

//�ؼ����滻
void changekeyword(char *sptoken);

//�Ƚ�������滻
void changecompare(char *sptoken);

//�����滻
void changenumber(char *sptoken);

//�ո񣬻���ɾ��
void deletespace(char *sptoken);
void delete (char *p);

//��ʶ�𵽵Ľ������������
void input_sname(char *sptoken);

//�滻�ṹ����
void change_struct(char *sptoken);
//�ѽ�����������������������ڱ���������

//�����滻
void change_function(char *sptoken);

//检查各种名称存贮是否出现错误，若有错误则删除
void input_vname_check(void);
void input_pname_check(void);
void input_sname_check(void);
int check_isvalid(char*input);

void token_input_process(struct token *token);

//������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���Ϻ���,���ô˺�������
void token_process(struct token *token);
//������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
#endif
