#include<stdio.h>
#include "global.h"
#include "clone_class.h" 

int find(int pa[],int v)
{
	if(pa[v]==v)
		return v;
	else
	{ 
		pa[v]=find(pa,pa[v]);
		return find(pa,pa[v]);
	}
}


void clone_class(int pa[])
{
	int t=1;

	for(t=1; t <= cnt_token; t++)
	{
		pa[t] = find(pa,t);
	}
}

