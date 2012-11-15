/*
ID: KJlmfe
LANG: C
TASK: friday
DATE: 2012.11.15

Problem Name: USACO Chapter 1 Section 1.1 Friday the Thirteenth
Problem Type: Water
Problem Source: http://ace.delos.com/usacoprob2?a=sgBvDgEg3kU&S=friday

Brief Problem:
	统计从1900年到1900+N-1年,每年每月13号是星期几

Solution:
	用days表示1900+i年j+1月13号距离1900年1月1号的总天数,用该数%7就可算得是星期几
	注意days随着i的增加,可能会越来越大,可能会益处int范围
	所以可以采用下面这个公式:
		(a+b)%c = (a%c+b)%c
*/

#include <stdio.h>
#define START_YEAR 1900

int is_leap_year(int year)
{
	if((year%4 == 0 && year%100 != 0) || (year%400 == 0))
		return 1;  // is leap_year
	else
		return 0; 
}

int main()
{
	FILE *fin  = fopen ("friday.in", "r");
	FILE *fout = fopen ("friday.out", "w");

	int i, j, k, N, days = 13;
	int week[7] = {0};												
	int month[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
						{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

    fscanf(fin, "%d\n", &N);
	for(i=0; i<N; i++)
	{
		k = is_leap_year(START_YEAR + i);
		for(j=0; j<12; j++)
		{
			week[days % 7]++;
			//days += month[k][j]; maybe days overflow
			days = (days + month[k][j]) % 7;
		}
	}

	fprintf(fout, "%d", week[6]);
	for(i=0; i<6; i++)
		fprintf(fout, " %d", week[i]); 
	fprintf(fout, "\n");

	return 0;
}
