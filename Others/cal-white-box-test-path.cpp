/*
ID: KJlmfe
LANG: C++
TASK: cal-white-box-test-path
DATE: 2012.11.21

Problem Name: 软件工程作业3: 自动生成白盒测试基本路径
Problem Type: DFS
Problem Source: https://cms.hit.edu.cn/mod/assignment/view.php?id=891

Brief Problem:
	给定一个源程序的控制流程图(有向图 边有三种类型)
	输出该源程序白盒测试的圈复杂度CC和所有路径

Solution:
	对有向图按照题目要求的优先顺序(按照N->F->T的顺序)去DFS生成路径
	在无路可走或者在当前路径上出现重复节点时停止当前路径前进
	对每次新生成的路径进行合法检查(是否在该路径中至少有一条边是之前所有已生成路径中没有出现过的)
	DFS结束后 按照题目的要求进行排序
	对于扩展情况:
		x,AND 或者 x,OR
		其实就是把原来指向x的边全都指向(10*x+1) 原来x指向别人的边全都指向(10*x+2)
		如果是AND 增加(10*x+1)-(T)>(10*x+2) 并且让(10*x+1)-(F)->[(10*x+2)的F边指向的点]
		如果是OR  增加(10*x+1)-(F)>(10*x+2) 并且让(10*x+1)-(T)->[(10*x+2)的F边指向的点]
		注意如果x是start节点 需要把start替换成(10*x+1)
	有可能节点编号很大 例如99999 这样是不能作数组下标的 所以我们采取给每个读入的新节点从1-N按序映射一个编号
*/

#include <iostream>
#include <cstring>
using namespace std;

#define MAXNODE 50  //最大节点个数
#define MAX_SUM_ROUTE 500 //最多路径个数
#define MAXSTRLEN 32	

int start, CC, total_node;
int edge[MAXNODE][3], node[MAXNODE];
int route[MAX_SUM_ROUTE][MAXNODE], new_route[MAXNODE];

//在字符串str第i位开始找到第一个base进制的合法数 将之后连续的合法base进制数 按照base进制转换成整数赋值给*num
int strToNum(char *str, int *num, int i = 0, int base = 10) 
{
	int tmp = 0;	

	while(!(str[i]>='0' && str[i]<base+'0')) 
		i++;

	while(str[i]>='0' && str[i]<base+'0')  
	{
		tmp = tmp * base + str[i] - '0';
		i++;
	}

	*num = tmp;

	return i;   //返回更新后的i
}
/*
查看p是否存储在node里 
	如果不存在  则将其存储并返回其对应的编号i 
	如果存在	则返回对应的编号i
*/
int nodeMapping(int p)  
{
	for(int i=1; i<=total_node; i++)
		if(node[i] == p)
			return i;

	node[++total_node] = p;	
	return total_node;
}
void addEdge(int a, int b, char op)  //a到b有一条边 其边的条件为op
{
	if(op == 'N')
		edge[a][0] = b;
	if(op == 'F')
		edge[a][1] = b;
	if(op == 'T')
		edge[a][2] = b;
}
void updateEdge(int p, char op)  //根据[p为节点 op为条件 AND(A)或者OR(O)]更新边
{
    int a = nodeMapping(p*10+1);
    int b = nodeMapping(p*10+2);

	if(node[1] == p)
		start = a;

	p = nodeMapping(p);

	int i, j;
	for(i=1; i<=total_node; i++)
		for(j=0; j<3; j++)
			if(edge[i][j] == p)
				edge[i][j] = a;

	for(i=0; i<3; i++)
	{
		edge[b][i] = edge[p][i];
		edge[p][i] = 0;
	}

	if(op == 'A')  //AND
	{
		edge[a][1] = edge[b][1];
		edge[a][2] = b;
	}
	else	//OR
	{
		edge[a][1] = b;
		edge[a][2] = edge[b][2];
	}
}
void inputEXT() //读取EXT行后面的数据 
{
	int a, i;
	char str[MAXSTRLEN];
	while(1)
	{
		cin >> str;
		if(strcmp(str, "END") == 0)
			return;
		i = strToNum(str, &a, 0);
		updateEdge(a, str[i+1]);
	}
}
void Input()
{
    char str[MAXSTRLEN];
	int a, b, i;
    cin >> start;
	start = nodeMapping(start);

    while(1)
    {
		cin >> str;
		if(strcmp(str,"END") == 0)
	  		return;
		if(strcmp(str,"EXT") == 0)
			return inputEXT();

		i = strToNum(str, &a, 0);
		i = strToNum(str, &b, i);
		a = nodeMapping(a);
		b = nodeMapping(b);
		addEdge(a, b, str[i+1]);
	}
}
int hasIndependentEdge(int *new_route)  //判断new_route路径是否有一条在之前所有路径中都不存在的边
{
	int a,b,i,j,k;

	if(CC == 0)
		return 1;

	for(int i=1; i<new_route[0]; i++)
	{
		a = new_route[i];
		b = new_route[i+1];
		for(j=1; j<=CC; j++)
		{
			for(k=1; k<route[j][0]; k++)
				if(a == route[j][k] && b==route[j][k+1]) 
					break;
			if(k < route[j][0])
				break;
		}
		if(j > CC)
			return 1;
	}
	return 0;
}
int circleCheck(int *new_route, int p, int count) //检查p是否在new_route里已经出现过
{
	for(int i=1; i<count; i++)
		if(new_route[i] == p)
			return 1;

	return 0;
}
void DFS(int now, int sum)
{
    new_route[++sum] = now;

	if(circleCheck(new_route, now, sum) == 0)
		for(int i=0; i<3; i++)
		{
			int next = edge[now][i];
			if(next > 0)		
				DFS(next, sum);
		}

	new_route[0] = sum;
	if(hasIndependentEdge(new_route))
	{
		CC++;
    	for(int i=0; i<=new_route[0]; i++)
			route[CC][i] = new_route[i];
	}
}
void routeUnNodeMapping()  //恢复本身节点号
{
	for(int i=1; i<=CC; i++)
		for(int j=1; j<=route[i][0]; j++)
			route[i][j] = node[route[i][j]];
}
void swapRoute(int i, int j)  //交换route[i]和route[j]两个数组
{
	int len = route[i][0] > route[j][0] ? route[i][0] : route[j][0];

	for(int k=0; k<=len; k++)
	{
		route[0][k] = route[j][k];
		route[j][k] = route[i][k];
		route[i][k] = route[0][k];
	}
}
void Sort() 
{
	for(int i=1; i<=CC; i++)
	    for(int j=1; j<=CC-i; j++)
			if(route[j][0] > route[j+1][0])
				swapRoute(j, j+1);
			else if(route[j][0] == route[j+1][0])
				for(int k=1; k<=route[j][0]; k++)
					if(route[j][k] != route[j+1][k])
					{
						if(route[j][k] > route[j+1][k])
							swapRoute(j, j+1);
						break;
					}
}
void Output()
{
	int i, j;

    cout << "CC=" << CC << endl;
    for(i=1; i<=CC; i++)
	{
		for(j=1; j<route[i][0]; j++)
    		cout << route[i][j] << ",";
		cout << route[i][j] << endl;
	}
}
int main()
{
    Input();
    DFS(start, 0);
	routeUnNodeMapping();
    Sort();
    Output();
    return 0;   
}
