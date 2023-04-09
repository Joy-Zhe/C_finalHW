#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include<math.h>
#include "global.h"
#include "token.h"
#include "block_divide.h"
#include "match.h"
#include "run.h"
#include "predefine.h"

void run(int cnt_file, char *filename[], FILE *file[])
{
	int i, t;
    struct token token1;
   
    char line[100000];
    block_divide(cnt_file, line, filename, file);
    for(i = 1; i<=cnt_token; i++){
    	token_input_process(&Mtoken[i]);
    	//printf("##");
       //puts(Mtoken[i].ch);
       //printf("\n");
	}
    
    input_vname_check();
    
    input_pname_check();
    
    input_sname_check();

/*
    for(i=0;i<vname_count;i++){
       printf("v=%s\n",Variable_name[i]);

    }
    for(i=0;i<pname_count;i++){
       printf("p=%s\n",Pointer_name[i]);

    }
    for(i=0;i<sname_count;i++){
       printf("s=%s\n",Struct_name[i]);

    }
*/

    for(i = 1; i<=cnt_token; i++){
    	token_process(&Mtoken[i]);
        flag_pnameappear = 1;
        flag_vnameappear = 1;
//    	puts(Mtoken[i].ch);
//    	puts(Mtoken[i].doc);
//		printf("%d %d \n",Mtoken[i].startline,Mtoken[i].endline);
	}
	mapping(cnt_token, 5);
	clone_pair(cnt_token, 5); 
//	for(i = 1; i <= cnt_token; i++)
//	{
		//if(i!=pair[i])
//		fprintf("%d %d %d    %d %d %d\n", i, Mtoken[i].startline, Mtoken[i].endline, pair[i], Mtoken[pair[i]].startline, Mtoken[pair[i]].endline);
//	}
}
