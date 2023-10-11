#include <iostream>
#include "CubeGenerate.h"

using namespace std;

int board[10]{1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880}; // 0-9的阶乘
bool book[10]; // 标记数是否已经出现过

int f[20];
int x, num;
int final[20];
void jie_cheng(int n)
{
	f[0] = f[1] = 1; // 0的阶乘为1
	for (int i = 2; i <= n; i++)
		f[i] = f[i - 1] * i;
}

int main()
{
	/*
	string s;
	cin>>s;
	int N;
	cin>>N;
	N--;
	for(int i=s.length() ; i>=1 ; i--){
		int mid = N/board[i-1]+1;
		for(int i=1 ; i<=mid ; i++){
			if(book[i])mid++;
		}
		book[mid] = true;
		cout<<mid;
		N %= board[i-1];
	}
	*/
	cin >> x;
	/*
	int jie[10] = { 1,1,2,6,24,120,720,5040,40320,362880 };//0-9！
	int pan[8] = { 0,0,0,0,0,0,0,0 };
	int final[8]={0,0,0,0,0,0,0,0};
	for (int i = 7; i >= 0; i--)
	{
		int s = x / jie[i];
		x = x % jie[i];			//康托逆展开
		int shu = s + 1;
		for (int j = 7; j >= 0; j--)
		{
			if (pan[j] == 1)
			{
				continue;
			}
			shu--;
			if (shu == 0)
			{
				final[i]= j;
				pan[j] = 1;
			}
		}
	}*/
	int count_o[3]={0,0,0};
	int power_3[8] = {1,1, 3, 9, 27, 81, 243, 729};
	for (int i = URF; i <= DBL; i++)
	{
		int s = x / power_3[7 - i];
		x = x % power_3[7 - i];
		final[i] = s;
	switch (final[i])
		{
		case 0/* constant-expression */:
			/* code */
			count_o[0]++;
			break;
		case 1:
			count_o[1]++;
			break;
		case 2:
			count_o[2]++;
			break;
		default:
			break;
		}
	
	if (count_o[0]%2!=0)
	{
		final[7]=0;
	}
	else
	{
		if(count_o[1]%2!=0)
		{
			final[7]=1;
		}
		else
		{
			final[7]=2;
		}
	}
	}
	for (int i = 0; i < 8; i++)
	{
		/* code */
		cout << final[i];
	}

	return 0;
}