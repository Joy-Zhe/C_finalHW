# Token
## 如何Token化
1) 去除源代码中的空白符、注释、宏定义（去除**非函数代码**）
2) 识别并标记函数粒度的代码片段
3) 对每个函数粒度的源代码进行相应规则的Token元素替换（粒度如何确定？）
## 构建映射
+ ***键：*** 取出的Token串中的某个定长子串 
```
	for(int i = pos; i < pos + sublen; i++)
		subToken[i - pos] = Token[index][i]; // 存入subToken
```
+ ***值：*** 所有包含该“键”的Token串的编号（不记录头的编号）
```
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
```
---
## 构建克隆对
### 定义：
+ **克隆对**：存在克隆关系的两段代码

### 如何构建
##### 编辑距离：两个字符串经过最少的增、删、改步骤达到相等状态。
+ 编辑距离相似度的计算
+ 在建立好的M映射表中查找出所有拥有最多公共子串的$k$个Token串后，再在这$k$个串中分别计算与当前需要构建克隆对的Token串的编辑距离相似度，取最高者作为克隆对对应的Token串，并通过如下方式记录：
```
	Pair[i] = k;// i为需要构建克隆对的串， k为找到的Token串
```
+ 具有重复子串的Token在上述算法中只会被记录一次，如$abababababab$在$sublen = 2$时， 只会在键为$ab$的值中记录一次编号。（跟集合的性质相似）
