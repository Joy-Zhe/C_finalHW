
extern char path_opened[300000][300];//存放已打开的文件、路径 
extern int path_book;//用于遍历已打开的文件、路径 
extern int f_path[300000];
extern FILE *file[300000];
extern int cnt_token;//token串数量
extern int M_book;//映射表内的区块个数 
extern int pair[10000];
extern struct token{
    char ch[100000];//鍌ㄥ瓨杩欎釜token鐨勫叿浣撳唴瀹规瘮濡傗�渧oid swap(){int a = 1;........................}鈥�
    char doc[100];//鍌ㄥ瓨杩欎釜token鎵�鍦ㄦ枃浠剁殑鏂囦欢鍚嶆瘮濡傗�渓ibrarysystem.c鈥�
    int startline;//杩欎釜token鐨勭涓�琛岀殑琛屽彿
    int endline;//杩欎釜token鏈�鍚庝竴琛岀殑琛屽彿
}Mtoken[8000],Mtoken_copy[8000];

extern struct s_Token{//閾捐〃琛ㄥご瀛樻斁褰撳墠涓茬殑淇℃伅锛堝洜涓烘棤闇�璁板綍绗竴涓嚭鐜扮殑瀛愪覆锛夛紝鑰屾瘡娆￠亶鍘嗛兘鏄粠澶村紑濮嬬殑锛屾晠鍙皢琛ㄥご浣滀负绱㈠紩
    int index;//瀛樻斁鎵惧埌鐨�
	char contain[50];// 浠呭湪瀛樻斁琛ㄥご鏃舵湁鏁堬紝鍗硈_Token[i]->contain
    struct s_Token *next;
}*M[10000000];

