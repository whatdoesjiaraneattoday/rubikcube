#include <iostream>
#include "CubeGenerate.h"

using namespace std;

int board[10]{1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880}; // 0-9的阶乘
bool book[10]; // 标记数是否已经出现过

int f[20];
string str, num;
int final[20];
void jie_cheng(int n)
{
	f[0] = f[1] = 1; // 0的阶乘为1
	for (int i = 2; i <= n; i++)
		f[i] = f[i - 1] * i;
}

int main()
{

	/*cin >> str;

	int index_p = 0;
	int index_o = 0;
	int x=1;
	for (int i=BR;i>=UR;i--)
	{
		if(str[i]=='1')
		{
			index_p+=n_C_m(11-i,x);
			x++;
		}
	}
	*/
	//cout<<index_p;
	struct state
	{
		int i;
		state(int _i)
		{
			i=_i;
		}
	};
	state &s=state(5);
	cout<<s.i;
	return 0;
}