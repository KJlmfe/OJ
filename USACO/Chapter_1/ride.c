/*
ID: KJlmfe
LANG: C
TASK: ride
DATE: 2012.11.12

Problem Name: USACO Chapter 1 Section 1.1 Your Ride Is Here
Problem Type: Water
Problem Source: http://ace.delos.com/usacoprob2?a=B3TD8bjoREl&S=ride 

Brief Problem:
	读入两个字符串,判断两个字符串的hash值是否相等,hash函数题目已给定

Solution:
	No
*/

#include <stdio.h>
#define MAXLEN 8

int hash(char *s)
{
	int i, h=1;

	for(i=0; s[i]!='\0'; i++)
		h *= s[i] - 'A' + 1;	
	h %= 47;

	return h;
}

int main()
{
    FILE *fin  = fopen ("ride.in", "r");
    FILE *fout = fopen ("ride.out", "w");

	char group[MAXLEN], comet[MAXLEN];

    fscanf(fin, "%s\n%s", comet, group);

	if(hash(group) == hash(comet))
    	fprintf(fout, "GO\n");
	else
    	fprintf(fout, "STAY\n");

	return 0;
}
