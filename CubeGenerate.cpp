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

CubieCube movement[6];

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

void CubeGenerate::EncodeCorner(void)
{
	int index_p = 0;
	int index_o = 0;
	for (Corner c = URF; c < DRB; c = Corner(int(c) + 1))
	{
		index_o = 3 * index_o + cube_state.co[c].o;
	}
	cube_state.index_corner_o = index_o; // 方向编码

	for (int i = DRB; i > URF; i--)
	{
		int s = 0;
		for (int j = i - 1; j >= URF; j--)
		{
			if (cube_state.co[j].c > cube_state.co[i].c)
			{
				s++;
			}
		}
		index_p = (index_p + s) * i;
	}
	cube_state.index_corner_p = index_p; // 康托展开
}

void CubeGenerate::DecodeCorner(void)
{
	int A_9[10] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880}; 
	int power_3[8] = {1, 1, 3, 9, 27, 81, 243, 729};
	int count[8] = {0, 0, 0, 0, 0, 0, 0, 0};
	int count_o[3] = {0, 0, 0};

	int index = cube_state.index_corner_p;// 位置解码
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
				cube_state.co[j].c = Corner(j);
				count[j] = 1;
			}
		}
	}

	index = cube_state.index_corner_o;//方向解码
	for (int i = URF; i <= DBL; i++)
	{
		int s = index / power_3[7 - i];
		index = index % power_3[7 - i];
		cube_state.co[i].o = s;
		switch (cube_state.co[i].o)
		{
		case 0:
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
		cube_state.co[DRB].o = 0;
	}
	else
	{
		if (count_o[1] % 2 != 0)
		{
			cube_state.co[DRB].o = 1;
		}
		else
		{
			cube_state.co[DRB].o = 2;
		}
	}
}

void CubeGenerate::EncodeEdge(void)
{
	int index_p = 0;
	int index_o = 0;
	int x = 1;
	for (Edge e = UR; e < BR; e = Edge(int(e) + 1))
	{
		index_o = 2 * index_o + cube_state.eo[e].o;
	}
	cube_state.index_corner_o = index_o; // 方向编码
	/*
	组合数编码 
	for (int i = BR; i >= UR; i--)
	{
		if ((cube_state.eo[i].e >= FR) && (cube_state.eo[i].e >= FR))
		{
			index_p += n_C_m(11 - i, x);
			x++;
		}
	}
	cube_state.index_edge_p = index_p;
	*/
	for (int i = BR; i > UR; i--)
	{
		int s = 0;
		for (int j = i - 1; j >= UR; j--)
		{
			if (cube_state.eo[j].e > cube_state.eo[i].e)
			{
				s++;
			}
		}
		index_p = (index_p + s) * i;
	}
	cube_state.index_corner_p = index_p; // 康托展开
}
void CubeGenerate::DecodeEdge(void)
{
	int power_2[12] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
	int index = 0;
	int count_o[2] = {0, 0};
	// 方向解码
	index = cube_state.index_corner_o;
	for (int i = UR; i <= BR; i++)
	{
		int s = index / power_2[11 - i];
		index = index % power_2[11 - i];
		cube_state.eo[i].o = s;
		switch (cube_state.eo[i].o)
		{
		case 0:
			count_o[0]++;
			break;
		case 1:
			count_o[1]++;
			break;
		default:
			break;
		}
	}
	if (count_o[0] % 2 != 0)
	{
		cube_state.eo[BR].o = 0;
	}
	else
	{
		cube_state.eo[BR].o = 1;
	}
	//位置解码
	int A_11[12]={1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880,3628800,39916800};
	int count[12]={0,0,0,0,0,0,0,0,0,0,0,0};
	index = cube_state.index_edge_p;// 位置解码
	for (int i = 11; i >= 0; i--) // 康托逆展开；
	{
		int s = index / A_11[i];
		index = index % A_11[i];
		int count_num = index + 1;
		for (int j = 11; j >= 0; j--)
		{
			if (count[j] == 1)
			{
				continue;
			}
			count_num--;
			if (count_num == 0)
			{
				cube_state.eo[j].e = Edge(j);
				count[j] = 1;
			}
		}
	}
}

void CubeGenerate::CornerTransform(const CubieCube* transform) // 角块变换 
{
	for (Corner i = URF; i <= DRB; i = Corner(int(i) + 1))
	{
		cube_state.co[i].c = cube_state.co[transform->co[i].c].c;
		cube_state.co[i].o = (cube_state.co[transform->co[i].c].o + transform->co[i].o) % 3;
	}
	return;
}

void CubeGenerate::EdgeTransform(const CubieCube* transform) //棱块变换
{
	for (Edge i = UR; i <= BR; i = Edge(int(i) + 1))
	{
		cube_state.eo[i].e = cube_state.eo[transform->eo[i].e].e;
		cube_state.eo[i].o = (cube_state.eo[transform->eo[i].e].o + transform->eo[i].o) % 2;
	}
	return;
}

void CubeGenerate::CubeMove(int m) // 魔方转动
{
	CornerTransform(&movement[m]);
	EdgeTransform(&movement[m]);
	return;
}

const int NMove = 18; // 可进行的操作数量，6个面，每个面可执行3个方向(90° -90° 180°)操作
const int NCP = 40320; // 角块位置排列的状态数量
const int NEP_UD = 40320; // 上下层棱块位置排列的状态数量

int movement[6]; // 六种基本操作
int cpMoveTable[NCP][NMove]; // 存储角块位置转动表，索引第一项为初始状态，第二项为执行的操作


void initcpMoveTable() // 初始化角块位置转动表
{
	CubeGenerate a;
	for (int i = 0; i <= NCP - 1; i++)
	{
		a.cube_state.index_corner_o = i;
		a.DecodeCorner();
		for (int j = U; i <= B; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				a.CornerTransform(&movement[j]);
				cpMoveTable[i][j * 3 + k] = a.cube_state.index_corner_o;
			}
			a.CornerTransform(&movement[j]);
		}
	}
}
