Skip to content
Search or jump to…
Pull requests
Issues
Marketplace
Explore
 
@Joy-Zhe 
Joy-Zhe
/
C_finalHW
Public
Code
Issues
Pull requests
Actions
Projects
Wiki
Security
Insights
Settings
C_finalHW/temp_md/token.md
@Joy-Zhe
Joy-Zhe Add files via upload
Latest commit 5f6df53 5 minutes ago
 History
 1 contributor
40 lines (39 sloc)  1.12 KB
   
Token
如何Token化
去除源代码中的空白符、注释、宏定义（去除非函数代码）
识别并标记函数粒度的代码片段
对每个函数粒度的源代码进行相应规则的Token元素替换（粒度如何确定？）
构建映射
键： 取出的Token串中的某个定长子串
	for(int i = pos; i < pos + sublen; i++)
		subToken[i - pos] = Token[index][i]; // 存入subToken
值： 所有包含该“键”的Token串的编号
	int now = 0, pos = 0;
	while (Token[index][pos] && now < sublen){
		if(subToken[now] == Token[index][pos]) 
			now++;
		else 
			now = 0;
		pos++;
	}
	if(now == sublen)
		if(subToken in M) // 暴力循环？懒得写了
			{}
			M[index_subToken].number = index;
			M[index_subToken] = M[index_subToken]->next;
			}	//链表，瞎写；可变数组也行（应该）
		else
			add index_subToken;
	else ;
构建克隆对
定义：
克隆对：存在克隆关系的两段代码
如何构建
通过对一段Token串先在映射表M中进行比对，查找公共子串最多的Token串
编辑距离（？）
© 2022 GitHub, Inc.
Terms
Privacy
Security
Status
Docs
Contact GitHub
Pricing
API
Training
Blog
About
Loading complete
