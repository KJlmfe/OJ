/*
ID: KJlmfe
LANG: C
TASK: Sort it
DATE: 2012.12.28

Problem Name: HDU 2689 Sort it
Problem Type: Sort MergeSort
Problem Source: http://acm.hdu.edu.cn/showproblem.php?pid=2689

Brief Problem:
	计算一个数列的逆序数

Solution:
	使用冒泡排序，每当交换相邻两个数时，逆序数+1，但是冒泡排序时间复杂度较高，我们使用归并排序

	在合并两个已经排序好的数列时，如果发现右数列中的某个数key更小，则逆序数加上此时左数列中剩余的个数，因为这些数都比key大
*/

#include <stdio.h>

#define MAX_N 1024
int ans;

void Merge(int A[], int start, int mid, int end)
{
	int LLength = mid - start + 1;
	int RLength = end - mid;
     
	int *L = (int *)malloc(sizeof(int)*LLength);
	int *R = (int *)malloc(sizeof(int)*RLength);
     
	int i;
     
	for(i=0; i<LLength; i++)
		L[i] = A[i+start];
	for(i=0; i<RLength; i++)
		R[i] = A[i+mid+1];
       
	int LPos = 0, RPos = 0;

	for(i=start; LPos<LLength && RPos<RLength; i++)
		if(L[LPos] <= R[RPos])
			A[i] = L[LPos++];           
		else
		{
			A[i] = R[RPos++];
			ans += LLength - LPos;  /*计算逆序数*/
		}
     
	while(LPos < LLength)
		A[i++] = L[LPos++];
	while(RPos < RLength)
		A[i++] = R[RPos++];                 

	free(L);
	free(R);
}

void MergeSort(int A[], int start, int end)
{
	if(start < end)
	{
		int mid = (start+end)/2;
		MergeSort(A, start, mid);
		MergeSort(A, mid+1, end);
		Merge(A, start, mid, end);
	}     
}

int main()
{
	int n, A[MAX_N], i;
    
	while(scanf("%d", &n) != EOF)
	{
		ans = 0;
		for(i=1; i<=n; i++)
			scanf("%d",&A[i]);
		MergeSort(A, 1, n);

		printf("%d\n",ans); 
	}
         
	return 0;
}
