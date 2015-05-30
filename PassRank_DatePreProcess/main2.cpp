// passrank.cpp : ??????????????
////#include "stdafx.h"

#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

#define INPUT "F://12306_top100_frequence_count.txt"
#define OUT1 "F://out1.txt"

#define psNum 15000000
#define maxDist 100
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
char pswd[psNum][35];//??
int flag[psNum];
int pscnt[psNum];	//??
char out[psNum][35];
int idx = 0;
/*
struct stru
{
int a[10000];
int end;
};
stru index[10000];	//??,index???????????,????????????(???a?),end???????????
int group = 1;*/
//int psWeight[psNum];

int levenshtein(char *s1, char *s2) 
{
	int x, y, s1len, s2len;
	s1len = strlen(s1);
	s2len = strlen(s2);
	if( (s1len-s2len >3) || (s2len-s1len >3) )
		return -1;
	int matrix[35][35];
	matrix[0][0] = 0;
	for (x = 1; x <= s2len; x++)
	matrix[x][0] = matrix[x-1][0] + 1;
	for (y = 1; y <= s1len; y++)
	matrix[0][y] = matrix[0][y-1] + 1;
	for (x = 1; x <= s2len; x++)
	for (y = 1; y <= s1len; y++)
	matrix[x][y] = MIN3(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));
	
	return(matrix[s2len][s1len]);
}




int main()
{
	int num = 0;
	memset(flag,0,sizeof(int));
	ifstream in;
	in.open(INPUT);
	if (!in)
		cout << "in error" << endl;
	ofstream out1,out2;
	out1.open(OUT1);
	if (!out1)
		cout << "out1 error" << endl;
	//out2.open(OUT2);
	//if (!out2)
	//	cout << "out2 error" << endl;
	char password[50];
	while (!in.eof())
	{
	
		in>> password;
		in >> pscnt[num];
		/*
		int len = strlen(password);
		len--;
		for (int i = 0;i < len;i++)
		password[i] = password[i+1];
		password[len] = '\0';*/
		strcpy(pswd[num],password);
		num++;
	
	}
	int p = 0;
	//int i = 0;
	while (p < psNum)
	{
		int b = 1;
		for (int i = 0;i < num;i++)
		{
			if (flag[i] == 0)
			{
				p = i;
				b = 0;
				break;
			}
		}
		if (b)
		break;
		strcpy(out[0],pswd[p]);
		flag[p] = 1;
		int outend = 1;
		
		for (int outi = 0;outi < outend;outi++)
		{
			for (int j = 0;j < num;j++)
			{
				if (flag[j] != 0)
				continue;
				int ed = levenshtein(out[outi],pswd[j]);
				if (ed <= 3 && ed > 0)
				{
					flag[j] = 1;
					strcpy(out[outend],pswd[j]);
					outend++;
					//cout << outend << endl;
				}
			
			}
		}
		
		for (int i = 0;i < outend;i++)
		{
			out1 << out[i] << ',';
		}
		out1 << endl;
	}
	
	return 0;
}



