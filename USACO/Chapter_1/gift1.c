/*
ID: KJlmfe
LANG: C
TASK: gift1
DATE: 2012.11.14

Problem Name: USACO Chapter 1 Section 1.1 Greedy Gift Givers
Problem Type: Water
Problem Source: http://ace.delos.com/usacoprob2?a=aOMU4eLmHqv&S=gift1

Brief Problem:
	给定NP个人的name(uniquely)和init_money,以及每个人给予接收者的总money和接收者的总人数number以及接收者的name
	计算出每个人的final_money - init_money

Solution:
	由于NP最大是10,所以可以采用数组线性存储人员信息,在根据name查找人时,采用线性扫描即可
	但是,如果NP非常大,线性查找肯定不行,可以采用哈希表存储人员信息,根据name来hash,这样根据name查找人时,时间复杂度为O(1)(无碰撞情况下)
*/

#include <stdio.h>
#define MAXNP 10
#define MAX_NAME_LEN 16

struct person
{
	char name[MAX_NAME_LEN];
	int init_money;
	int final_money;
}group[MAXNP];

int NP;

int find_person_by_name(char *s)
{
	int i;

	for(i=0; i<NP; i++)
		if(strcmp(s, group[i].name) == 0)
			return i;
}

int main()
{
    FILE *fin  = fopen ("gift1.in", "r");
    FILE *fout = fopen ("gift1.out", "w");
	int i, j, money, number;
	char giver_name[MAX_NAME_LEN],receiver_name[MAX_NAME_LEN];

    fscanf(fin, "%d\n", &NP);
	for(i=0; i<NP; i++)
		fscanf(fin, "%s\n", group[i].name);

	while(fscanf(fin, "%s\n", giver_name) != EOF)
	{
		fscanf(fin, "%d %d\n", &money, &number);	

		j = find_person_by_name(giver_name);
		group[j].init_money = money;
		if(number != 0)  // a % b (must b != 0)
			group[j].final_money += money % number;

		for(i=0; i<number; i++)
		{
			fscanf(fin, "%s\n", receiver_name);
			j = find_person_by_name(receiver_name);
			group[j].final_money += money / number;
		}
	}

	for(i=0; i<NP; i++)
		fprintf(fout, "%s %d\n", group[i].name, group[i].final_money-group[i].init_money);

	return 0;
}
