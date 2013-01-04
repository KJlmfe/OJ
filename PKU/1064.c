/*
ID: KJlmfe
LANG: C
TASK: Cable master
DATE: 2013.1.4

Problem Name: PKU 1064
Problem Type: Divide-and-Conquer BinarySearch
Problem Source: http://poj.org/problem?id=1064

Brief Problem:
	给定N个长度(小数部分为2位的浮点数)不一样的棍子 之后对每个棍子进行随意切割 但是不能拼接
	切割出K个等长(最短0.01)的小棍子 问小棍子的最大长度是多少?
	如果无法切出K个0.01长度的小棍子 则输出0.00

Solution:
	根据输入 我们可以计算出小棍子的最大长度max 以及最短长度min
	之后在区间[min, max]进行二分查找

	注意：为了避免浮点数的精度问题，我们将每个棍子*100转换为整数长度，之后进行整数区间内的二分查找
*/

#include <stdio.h>

#define MAX_N 10004
int N, K, L[MAX_N];

int check(int len)
{
	if(len == 0)   /*避免除数为0*/
		return 0;

	int sum = 0, i;

	for(i=1; i<=N; i++)
		sum += L[i]/len;

	if(sum >= K)
		return 1;
	else
		return 0;
}

int BinarySearch(int min, int max)
{
	if(min <= max)
	{
		/*printf("%d %d\n", min, max);*/
		int mid = (min+max) / 2;

		if(check(mid) == 1)
			return BinarySearch(mid+1, max);
		else
			return BinarySearch(min, mid-1);
	}
	else
		return max;
}

int main()
{
	int i, min, max;
	double tmpLen;

	while(scanf("%d %d\n", &N, &K) != EOF)
	{
		for(i=1; i<=N; i++)
		{
			scanf("%lf", &tmpLen);
			L[i] = (int)(tmpLen*100);
			if(i == 1) 
			{
				max = L[i];
				min = L[i]/K;
			}
			max = max > L[i] ? max : L[i];
			min = min < L[i]/K ? min : L[i]/K;
		}

		min = min == 0 ? 1 : min;  /* 棍子最短0.01 对应整数1 */
		printf("%.2lf\n", (double)(BinarySearch(min, max)*0.01));
	}

	return 0;
}
