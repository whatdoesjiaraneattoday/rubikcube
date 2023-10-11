/**
 * @file CubeGenerate.cpp
 * @author Lou Bin ({3189529472@qq.com})
 * @brief
 * @version 0.1
 * @date 2023-10-06
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "CubeGenerate.h"
using namespace std;
long long n_C_m(int n, int m)

{
	if (n - m < 0)
	{
		return 0;
	}
	else
	{
		if (m < n - m)
		{
			m = n - m;
		}
		long long factor = 1;
		for (int i = m + 1; i <= n; i++)
		{
			factor *= i;
		}
		for (int i = 1; i <= n - m; i++)
		{
			factor /= i;
		}
		return factor;
	}
}

CubeGenerate::CubeGenerate()
{
}

void CubeGenerate::EncodeCorner(CubieCube Cube_State)
{
	int index_p = 0;
	int index_o = 0;
	for (Corner c = URF; c < DRB; c = Corner(int(c) + 1))
	{
		index_o = 3 * index_o + Cube_State.co[c].o;
	}
	Cube_State.index_corner_o = index_o; // 方向编码

	for (int i = DRB; i > URF; i--)
	{
		int s = 0;
		for (int j = i - 1; j >= URF; j--)
		{
			if (Cube_State.co[j].c > Cube_State.co[i].c)
			{
				s++;
			}
		}
		index_p = (index_p + s) * i;
	}
	Cube_State.index_corner_p = index_p; // 康托展开
}

void CubeGenerate::DecodeCorner(CubieCube Cube_State)
{
	int A_9[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880}; // 位置解码
	int power_3[8] = {1, 1, 3, 9, 27, 81, 243, 729};
	int count[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int count_o[3] = {0, 0, 0};
	int index = Cube_State.index_corner_p;
	for (int i = 7; i >= 0; i--) // 康托逆展开；
	{
		int s = index / A_9[i];
		index = index % A_9[i];
		int count_num = index + 1;
		for (int j = 7; j >= 0; j--)
		{
			if (count[j] == 1)
			{
				continue;
			}
			count_num--;
			if (count_num == 0)
			{
				Cube_State.co[j].c = Corner(j);
				count[j] = 1;
			}
		}
	}

	index = Cube_State.index_corner_o;
	for (int i = URF; i <= DBL; i++)
	{
		int s = index / power_3[7 - i];
		index = index % power_3[7 - i];
		Cube_State.co[i].o = s;
		switch (Cube_State.co[i].o)
		{
		case 0 /* constant-expression */:
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
	}
	if (count_o[0] % 2 != 0)
	{
		Cube_State.co[DRB].o = 0;
	}
	else
	{
		if (count_o[1] % 2 != 0)
		{
			Cube_State.co[DRB].o = 1;
		}
		else
		{
			Cube_State.co[DRB].o = 2;
		}
	}
}

void CubeGenerate::EncodeEdge(CubieCube Cube_State)
{
	int index_p = 0;
	int index_o = 0;
	for (Edge e = UR; e < BR; e = Edge(int(e) + 1))
	{
		index_o = 2 * index_o + Cube_State.eo[e].o;
	}
	Cube_State.index_corner_o = index_o; // 方向编码
}
void CubeGenerate::DecodeEdge(CubieCube Cube_State)
{
}