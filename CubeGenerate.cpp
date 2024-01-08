//魔方求解函数，通过DFS甲加上剪枝求解出魔方还原公式
#include "CubeGenerate.h"
#include "CubeExplorer.h"
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

void CubeGenerate::EncodeCorner(void) //
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

	int index = cube_state.index_corner_p; // 位置解码
	for (int i = 7; i >= 0; i--)		   // 康托逆展开；
	{
		int s = index / A_9[i];
		index = index % A_9[i];
		int count_num = s + 1;
		for (int j = 7; j >= 0; j--)
		{
			if (count[j] == 1)
			{
				continue;
			}
			count_num--;
			if (count_num == 0)
			{
				cube_state.co[i].c = Corner(j);
				count[j] = 1;
			}
		}
	}

	index = cube_state.index_corner_o; // 方向解码
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
	int sum;
	sum = count_o[0] * 0 + 1 * count_o[1] + 2 * count_o[2];
	if (sum % 3 == 0)
	{
		cube_state.co[DRB].o = 0;
	}
	else
		cube_state.co[DRB].o = 3 - sum % 3;
}

void CubeGenerate::EncodeEdge(void)
{
	int index_p = 0;
	int index_o = 0;
	int index_c = 0;
	int x = 1;

	// 方向编码
	for (Edge e = UR; e < BR; e = Edge(int(e) + 1))
	{
		index_o = 2 * index_o + cube_state.eo[e].o;
	}
	cube_state.index_edge_o = index_o;

	// 组合数编码
	for (int i = BR; i >= UR; i--)
	{
		if ((cube_state.eo[i].e >= FR) && (cube_state.eo[i].e <= BR))
		{
			index_c += n_C_m(11 - i, x);
			x++;
		}
	}
	cube_state.index_combination = index_c;
	// 所有棱块编码
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
	cube_state.index_edge_p = index_p; // 康托展开

	// 上下层编码
	index_p = 0;
	for (int i = DB; i > UR; i--)
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
	cube_state.index_other_p = index_p; // 康托展开

	// 中间层编码
	index_p = 0;
	for (int i = BR; i > FR; i--)
	{
		int s = 0;
		for (int j = i - 1; j >= FR; j--)
		{
			if (cube_state.eo[j].e > cube_state.eo[i].e)
			{
				s++;
			}
		}
		index_p = (index_p + s) * (i - 8);
	}
	cube_state.index_middle_p = index_p; // 康托展开
}
void CubeGenerate::DecodeEdge(int select_num) // n=0 方向 n=1 全位置解码 n=2 上下层解码 n=3 中间层解码 n=4 位置解码
{
	int A_11[12] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 3628800, 39916800};
	int power_2[13] = {1, 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048};
	int index = 0;
	int count_o[2] = {0, 0};
	// 方向解码
	if (select_num == 0)
	{
		index = cube_state.index_edge_o;
		for (int i = UR; i < BR; i++)
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
		{
			int sum;
			sum = count_o[0] * 0 + 1 * count_o[1];
			if (sum % 2 == 0)
				cube_state.eo[BR].o = 0;
			else
				cube_state.eo[BR].o = 2 - sum % 2;
		}
	}
	else if (select_num == 1)
	{
		// 位置解码
		int count[12] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
		index = cube_state.index_edge_p; // 位置解码
		for (int i = 11; i >= 0; i--)	 // 康托逆展开；
		{
			int s = index / A_11[i];
			index = index % A_11[i];
			int count_num = s + 1;
			for (int j = 11; j >= 0; j--)
			{
				if (count[j] == 1)
				{
					continue;
				}
				count_num--;
				if (count_num == 0)
				{
					cube_state.eo[i].e = Edge(j);
					count[j] = 1;
				}
			}
		}
	}
	else if (select_num == 2)
	{
		// 上下层解码
		index = cube_state.index_other_p; //
		int count_other[8] = {0, 0, 0, 0, 0, 0, 0, 0};
		for (int i = 7; i >= 0; i--)
		{
			int s = index / A_11[i];
			index = index % A_11[i];
			int count_num = s + 1;
			for (int j = 7; j >= 0; j--)
			{
				if (count_other[j] == 1)
				{
					continue;
				}
				count_num--;
				if (count_num == 0)
				{
					cube_state.eo[i].e = Edge(j);
					count_other[j] = 1;
				}
			}
		}
		for (int i = 8; i <= 11; i++)
		{
			cube_state.eo[i].e = Edge(i);
		}
	}
	else if (select_num == 3)
	{
		index = cube_state.index_middle_p;
		int count_middle[4] = {0, 0, 0, 0};
		for (int i = 3; i >= 0; i--)
		{
			int s = index / A_11[i];
			index = index % A_11[i];
			int count_num = s + 1;
			for (int j = 3; j >= 0; j--)
			{
				if (count_middle[j] == 1)
				{
					continue;
				}
				count_num--;
				if (count_num == 0)
				{
					cube_state.eo[8 + i].e = Edge(8 + j);
					count_middle[j] = 1;
				}
			}
		}
		for (int i = 0; i <= 7; i++)
		{
			cube_state.eo[i].e = Edge(i);
		}
	}
	else if (select_num == 4)
	{
		index = cube_state.index_combination;
		int num = 4;
		for (int i = 0; i <= 11; i++)
		{
			cube_state.eo[i].e = Edge(0);
		}
		for (int i = 0; i <= 11; i++)
		{
			if (index >= n_C_m(11 - i, num))
			{
				cube_state.eo[i].e = Edge(12 - num);
				index -= n_C_m(11 - i, num);
				num--;
			}
		}
	}
}

void CubeGenerate::CornerTransform(const CubieCube *transform) // 角块变换
{
	CubieCube temp = cube_state;
	for (Corner i = URF; i <= DRB; i = Corner(int(i) + 1))
	{
		cube_state.co[i].c = temp.co[transform->co[i].c].c;
		cube_state.co[i].o = (temp.co[transform->co[i].c].o + transform->co[i].o) % 3;
	}
	return;
}

void CubeGenerate::EdgeTransform(const CubieCube *transform) // 棱块变换
{
	CubieCube temp = cube_state;
	for (Edge i = UR; i <= BR; i = Edge(int(i) + 1))
	{
		cube_state.eo[i].e = temp.eo[transform->eo[i].e].e;
		cube_state.eo[i].o = (temp.eo[transform->eo[i].e].o + transform->eo[i].o) % 2;
	}
	return;
}
void CubeGenerate::EdgeTransform1(const CubieCube *transform) // 棱块变换
{
	CubieCube temp = cube_state;
	for (Edge i = UR; i <= BR; i = Edge(int(i) + 1))
	{
		cube_state.eo[i].e = temp.eo[transform->eo[i].e].e;
	}
	return;
}
CubieCube movement[6];			   // 六种基本操作变换
void CubeGenerate::CubeMove(int m) // 魔方转动

{
	CornerTransform(&movement[m]);
	EdgeTransform(&movement[m]);
	return;
}
void CubeGenerate::GetCube(void)
{
	string input;
	getline(cin, input);
	input = input + " ";
	disrupt_string = input;
	int len = input.length();
	int pos_b = -1; // 后面的位置
	int pos_f = 0;	// 前面的位置
	for (int i = 0; i <= len - 1; i++)
	{
		if (input.at(i) == ' ')
		{
			pos_f = i;
			int len = pos_f - pos_b - 1;
			string x = input.substr(pos_b + 1, len);
			pos_b = pos_f;
			int ci = 0;
			if (x.length() == 1)
			{
				ci = 1;
			}
			else if (x.substr(1) == "'")
			{
				ci = 3;
			}
			else if (x.at(1) == '2')
			{
				ci = 2;
			}
			int op = 0;
			char tmp = x.at(0);
			switch (tmp)
			{
			case 'U':
				op = 0;
				break;
			case 'D':
				op = 1;
				break; // U1 U1 D1 D D L1
			case 'L':
				op = 2;
				break;
			case 'R':
				op = 3;
				break;
			case 'F':
				op = 4;
				break;
			case 'B':
				op = 5;
				break;
			}
			for (int i = 1; i <= ci; i++)
				CubeMove(op);
		}
	}
}

void CubeGenerate::ShowState(int n) // i=0 show o i=1 show c  i=2 show o i=3 show e n=4
{
	if (n == 0)
	{
		cout << "Cube State" << endl;
		for (int i = 0; i <= 7; i++)
		{
			cout << "co[" << i << "]o:" << cube_state.co[i].o << endl;
		}
	}
	if (n == 1)
	{
		cout << "Cube State" << endl;
		for (int i = 0; i <= 7; i++)
		{
			cout << "co[" << i << "]c:" << cube_state.co[i].c << endl;
		}
	}
	if (n == 2)
	{
		cout << "Cube State" << endl;
		for (int i = 0; i <= 11; i++)
		{
			cout << "eo[" << i << "]o:" << cube_state.eo[i].o << endl;
		}
	}
	if (n == 3)
	{
		cout << "Cube State" << endl;
		for (int i = 0; i <= 11; i++)
		{
			cout << "eo[" << i << "]e:" << cube_state.eo[i].e << endl;
		}
	}
	if (n == 4)
	{
		cout << "Cube State" << endl;
		cout << "index_corner_o:" << cube_state.index_corner_o << endl;
		cout << "index_corner_p:" << cube_state.index_corner_p << endl;
		cout << "index_edge_o:" << cube_state.index_edge_o << endl;
		cout << "index_other_p:" << cube_state.index_other_p << endl;
		cout << "index_combination:" << cube_state.index_combination << endl;
		cout << "index_middle_p:" << cube_state.index_middle_p << endl;
	}
}

const int NMove = 18;	  // 可进行的操作数量，6个面，每个面可执行3个方向(90° -90° 180°)操作
const int NCP = 40320;	  // 角块位置排列的状态数量 8A8=40320
const int NEP_UD = 40320; // 上下层棱块在上下层位置排列的状态数量 8A8=40320
const int NEP_M = 24;	  // 中间层棱块在中间层位置排列的状态数 4A4=24
const int NSLICE = 495;	  // 所有棱块在中间层位置组合的状态数 12C4=495
const int NTWIST = 2187;  // 角块的方向状态数 3^7=2187
const int NFLIP = 2048;	  // 棱块的方向状态数 2^11=2048

int cpMoveTable[NCP][NMove];	   // 存储角块位置转动表，索引第一项为初始状态，第二项为执行的操作
int epudMoveTable[NEP_UD][NMove];  // 存储上下层棱块位置转动表
int epmMoveTable[NEP_M][NMove];	   // 存储中间层棱块位置转动表
int sliceMoveTable[NSLICE][NMove]; // 存储棱块位置组合转动表
int twistMoveTable[NTWIST][NMove]; // 存储角块方向转动表
int flipMoveTable[NFLIP][NMove];   // 存储棱块方向转动表

void InitCpMoveTable() // 初始化角块位置转动表
{
	CubeGenerate a;
	for (int i = 0; i < NCP; i++)
	{
		a.cube_state.index_corner_p = i;
		a.DecodeCorner();
		for (int j = U; j <= B; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				a.CornerTransform(&movement[j]);
				a.EncodeCorner();
				cpMoveTable[i][j * 3 + k] = a.cube_state.index_corner_p;
			}
			a.CornerTransform(&movement[j]);
		}
	}
	return;
}

void InitEpudMoveTable() // 初始化上下层棱块位置转动表
{
	CubeGenerate a;
	for (int i = 0; i < NEP_UD; i++)
	{
		a.cube_state.index_other_p = i;
		a.DecodeEdge(2);
		for (int j = U; j <= B; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				a.EdgeTransform(&movement[j]);
				a.EncodeEdge();
				epudMoveTable[i][j * 3 + k] = a.cube_state.index_other_p;
			}
			a.EdgeTransform(&movement[j]);
		}
	}
	return;
}

void InitEpmMoveTable() // 初始化中间层棱块位置转动表
{
	CubeGenerate a;
	for (int i = 0; i < NEP_M; i++)
	{
		a.cube_state.index_middle_p = i;
		a.DecodeEdge(3);
		for (int j = U; j <= B; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				a.EdgeTransform(&movement[j]);
				a.EncodeEdge();
				epmMoveTable[i][j * 3 + k] = a.cube_state.index_middle_p;
			}
			a.EdgeTransform(&movement[j]);
		}
	}
	return;
}

void InitSliceMoveTable() // 初始化棱块位置组合转动表
{
	CubeGenerate a;
	for (int i = 0; i < NSLICE; i++)
	{
		a.cube_state.index_combination = i;
		a.DecodeEdge(4);
		for (int j = U; j <= B; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				a.EdgeTransform(&movement[j]);
				a.EncodeEdge();
				sliceMoveTable[i][j * 3 + k] = a.cube_state.index_combination;
			}
			a.EdgeTransform(&movement[j]);
		}
	}
	return;
}

void InitTwistMoveTable() // 初始化角块方向转动表
{
	CubeGenerate a;
	for (int i = 0; i < NTWIST; i++)
	{
		a.cube_state.index_corner_o = i;
		a.DecodeCorner();
		for (int j = U; j <= B; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				a.CornerTransform(&movement[j]);
				a.EncodeCorner();

				twistMoveTable[i][j * 3 + k] = a.cube_state.index_corner_o;
			}
			a.CornerTransform(&movement[j]);
		}
	}
	return;
}

void initFlipMoveTable() // 初始化棱块方向转动表
{
	CubeGenerate a;
	for (int i = 0; i < NFLIP; i++)
	{
		a.cube_state.index_edge_o = i;
		a.DecodeEdge(0);
		for (int j = U; j <= B; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				a.EdgeTransform(&movement[j]);
				a.EncodeEdge();
				flipMoveTable[i][j * 3 + k] = a.cube_state.index_edge_o;
			}
			a.EdgeTransform(&movement[j]);
		}
	}
	return;
}

// 存储剪枝表
int cpPruneTable[NCP];
int epudPruneTable[NEP_UD];
int epmPruneTable[NEP_M];
int twistPruneTable[NTWIST];
int flipPruneTable[NFLIP];
int slicePruneTable[NSLICE];

void InitTwistPruneTable() // 角块方向的剪枝表
{
	for (int i = 0; i < NTWIST; i++)
	{
		twistPruneTable[i] = -1; // 初始化表值为-1
	}
	int depth = 0;
	int done = 1;
	int index;
	twistPruneTable[0] = 0; // 目标状态深度为0
	while (done < NTWIST)	// 若表中已填写的状态数小于总状态数
	{
		for (int i = 0; i < NTWIST; i++)
		{

			if (twistPruneTable[i] == depth) // 找到该深度下的状态
			{
				for (int j = 0; j < NMove; j++)
				{
					index = twistMoveTable[i][j];	  // 执行18种转动操作
					if (twistPruneTable[index] == -1) // 若该状态的剪枝表没有填写
					{
						twistPruneTable[index] = depth + 1; // 填写深度值
						done++;								// 已填写数加1
					}
				}
			}
		}
		depth++; // 到下一层深度
	}

	return;
}

void InitFlipPruneTable() // 棱块方向的剪枝表
{
	for (int i = 0; i < NFLIP; i++)
		flipPruneTable[i] = -1;
	int depth = 0;
	int done = 1;
	int index;
	flipPruneTable[0] = 0;
	while (done < NFLIP)
	{
		for (int i = 0; i < NFLIP; i++)
		{
			if (flipPruneTable[i] == depth)
			{
				for (int j = 0; j < NMove; j++)
				{
					index = flipMoveTable[i][j];
					if (flipPruneTable[index] == -1)
					{
						flipPruneTable[index] = depth + 1;
						done++;
					}
				}
			}
		}
		depth++;
	}
	return;
}

void InitSlicePruneTable() // 棱块位置组合的剪枝表
{
	for (int i = 0; i < NSLICE; i++)
		slicePruneTable[i] = -1;
	int depth = 0;
	int done = 1;
	int index;
	slicePruneTable[0] = 0;
	while (done < NSLICE)
	{
		for (int i = 0; i < NSLICE; i++)
		{
			if (slicePruneTable[i] == depth)
			{
				for (int j = 0; j < NMove; j++)
				{
					index = sliceMoveTable[i][j];
					if (slicePruneTable[index] == -1)
					{
						slicePruneTable[index] = depth + 1;
						done++;
					}
				}
			}
		}
		depth++;
	}
	return;
}

// 阶段二允许的魔方操作
CubeOperate operationForStep2[10] = {{U, 0}, {U, 1}, {U, 2}, {D, 0}, {D, 1}, {D, 2}, {L, 1}, {R, 1}, {F, 1}, {B, 1}};
void InitCpPruneTable() // 角块位置剪枝表
{
	for (int i = 0; i < NCP; i++)
		cpPruneTable[i] = -1;
	int depth = 0;
	int done = 1;
	int index;
	cpPruneTable[0] = 0;
	while (done < NCP)
	{
		for (int i = 0; i < NCP; i++)
		{
			if (cpPruneTable[i] == depth)
			{
				for (int j = 0; j < 10; j++)
				{
					int x = operationForStep2[j].a;
					int y = operationForStep2[j].b;
					index = cpMoveTable[i][x * 3 + y];
					if (cpPruneTable[index] == -1)
					{
						cpPruneTable[index] = depth + 1;
						done++;
					}
				}
			}
		}
		depth++;
	}
	return;
}

void InitEpudPruneTable() // 上下层棱块位置剪枝表
{
	for (int i = 0; i < NEP_UD; i++)
		epudPruneTable[i] = -1;
	int depth = 0;
	int done = 1;
	int index;
	epudPruneTable[0] = 0;
	while (done < NEP_UD)
	{
		for (int i = 0; i < NEP_UD; i++)
		{
			if (epudPruneTable[i] == depth)
			{
				for (int j = 0; j < 10; j++)
				{
					int x = operationForStep2[j].a;
					int y = operationForStep2[j].b;
					index = epudMoveTable[i][x * 3 + y];
					if (epudPruneTable[index] == -1)
					{
						epudPruneTable[index] = depth + 1;
						done++;
					}
				}
			}
		}
		depth++;
	}
	return;
}

void InitEpmPruneTable() // 中间层棱块位置剪枝表
{
	for (int i = 0; i < NEP_M; i++)
		epmPruneTable[i] = -1;
	int depth = 0;
	int done = 1;
	int index;
	epmPruneTable[0] = 0;
	while (done < NEP_M)
	{
		for (int i = 0; i < NEP_M; i++)
		{
			if (epmPruneTable[i] == depth)
			{
				for (int j = 0; j < 10; j++)
				{
					int x = operationForStep2[j].a;
					int y = operationForStep2[j].b;
					index = epmMoveTable[i][x * 3 + y];
					if (epmPruneTable[index] == -1)
					{
						epmPruneTable[index] = depth + 1;
						done++;
					}
				}
			}
		}
		depth++;
	}
	return;
}
Solution solution;
int depthLimit = 25;
int flag = 0;
int serialNum = 0;
int equtionNum = 0;
string operationTrans[18] = {"U", "U2", "U'", "D", "D2", "D'", "L", "L2", "L'",
							 "R", "R2", "R'", "F", "F2", "F'", "B", "B2", "B'"};

void DFSearch1(CubeGenerate Cube, int twist, int flip, int slice, int togo1)
{
	if (serialNum >= 5)
		return;
	if (togo1 == 0) // 若阶段一已解决
	{
		if (twist == 0 && flip == 0 && slice == 0)
		{
			int index_corner_p = Cube.cube_state.index_corner_p;
			for (int i = 1; i <= solution.len; i++)
			{
				index_corner_p = cpMoveTable[index_corner_p][solution.operate_sequence[i]];
				for (int j = 0; j <= solution.operate_sequence[i] % 3; j++)
				{
					Cube.EdgeTransform1(&movement[solution.operate_sequence[i] / 3]);
				}
			}
			Cube.EncodeEdge();
			int index_other_p = Cube.cube_state.index_other_p;
			int index_middle_p = Cube.cube_state.index_middle_p;
			// cout<<x<<" "<<y<<" "<<z<<endl;
			int m = max(max(cpPruneTable[index_corner_p], epudPruneTable[index_other_p]), epmPruneTable[index_middle_p]);
			for (int i = m; i <= depthLimit - solution.len; i++)
			{
				if (flag)
					break;
				DFSearch2(index_corner_p, index_other_p, index_middle_p, i);
			}
			flag = 0;
		}
	}
	else
	{
		int flip1, twist1, slice1;
		for (int i = 0; i <= 17; i++)
		{
			int x = solution.operate_sequence[solution.len];
			if (x / 3 == i / 3) // 若连续两步操作同一个面，可以合并成一步，是不必要的操作
				continue;
			if (x / 3 - i / 3 == 1 && (x / 3) % 2 == 1) // 魔方相对两面的转动满足交换律，相对面连续转动是不必要的操作
				continue;
			twist1 = twistMoveTable[twist][i]; // 转动过后新的twist
			flip1 = flipMoveTable[flip][i];	   // 转动过后新的flip
			slice1 = sliceMoveTable[slice][i]; // 转动过后新的slice
			int dist1 = max(max(twistPruneTable[twist1], flipPruneTable[flip1]), slicePruneTable[slice1]);
			if (dist1 > togo1 - 1) // 若步数大于最大深度，剪枝
				continue;
			solution.len++;
			solution.operate_sequence[solution.len] = i;	   // 储存操作到答案序列
			DFSearch1(Cube, twist1, flip1, slice1, togo1 - 1); // 进入下一层
			solution.len--;									   // 回溯
		}
	}
	return;
}

//int shortestTime;
//CubeExplorer cube_explorer;

void DFSearch2(int cp, int epud, int epm, int togo2)
{
	if (serialNum >= 5)
		return;
	if (flag)
		return;
	if (togo2 == 0)
	{
		if (cp == 0 && epud == 0 && epm == 0)
		{
			serialNum++;
			cout << serialNum << ":" << solution.len << " ";
			for (int i = 1; i <= solution.len; i++)
			{
				cout << operationTrans[solution.operate_sequence[i]] << " ";
				solution.equation[equtionNum] = solution.equation[equtionNum] + operationTrans[solution.operate_sequence[i]] + " ";
			}
			cout << endl;
			depthLimit = solution.len;
			flag = 1;

			//cube_explorer.SetTarget(solution.equation[equtionNum]);
			//cube_explorer.GetShortestWay();
			//solution.time = cube_explorer.GetOperationTime();
			//cube_explorer.ShowOperations();
			//cube_explorer.Reset();
			equtionNum++;
		}
		return;
	}
	else
	{
		int cp1, epud1, epm1;
		for (int i = 0; i <= 9; i++)
		{
			if (flag)
				return;
			int x = operationForStep2[i].a;
			int y = operationForStep2[i].b;
			int j = 3 * x + y;
			int m = solution.operate_sequence[solution.len];
			if (m / 3 == x)
				continue;
			if (m / 3 - x == 1 && (m / 3) % 2 == 1)
				continue;
			cp1 = cpMoveTable[cp][j];
			epud1 = epudMoveTable[epud][j];
			epm1 = epmMoveTable[epm][j];
			int dist2 = max(max(cpPruneTable[cp1], epudPruneTable[epud1]), epmPruneTable[epm1]);
			if (dist2 > togo2 - 1)
				continue;
			solution.len++;
			solution.operate_sequence[solution.len] = x * 3 + y;
			DFSearch2(cp1, epud1, epm1, togo2 - 1);
			solution.len--;
		}
	}
	return;
}
void Search(CubeGenerate Cube) 
{
	int x = max(max(twistPruneTable[Cube.cube_state.index_corner_o], flipPruneTable[Cube.cube_state.index_edge_o]), slicePruneTable[Cube.cube_state.index_combination]);

	for (int i = x; i <= depthLimit; i++)
	{
		if (serialNum >= 5)
			return;
		DFSearch1(Cube, Cube.cube_state.index_corner_o, Cube.cube_state.index_edge_o, Cube.cube_state.index_combination, i);
	}
}