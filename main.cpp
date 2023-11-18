#include "CubeGenerate.h"
int main()
{
	extern CubieCube movement[6];
	movement[U] = {// URF槽的元素被UFL槽的元素替代，且顺时针扭转，方向加1
				   {{UBR, 0}, {URF, 0}, {UFL, 0}, {ULB, 0}, {DFR, 0}, {DLF, 0}, {DBL, 0}, {DRB, 0}},
				   {{UB, 0}, {UR, 0}, {UF, 0}, {UL, 0}, {DR, 0}, {DF, 0}, {DL, 0}, {DB, 0}, {FR, 0}, {FL, 0}, {BL, 0}, {BR, 0}},
				   0,
				   0,
				   0,
				   0,
				   0,
				   0,
				   0

	};
	movement[D] = {// URF槽的元素被UFL槽的元素替代，且顺时针扭转，方向加1
				   {{URF, 0}, {UFL, 0}, {ULB, 0}, {UBR, 0}, {DLF, 0}, {DBL, 0}, {DRB, 0}, {DFR, 0}},
				   {{UR, 0}, {UF, 0}, {UL, 0}, {UB, 0}, {DF, 0}, {DL, 0}, {DB, 0}, {DR, 0}, {FR, 0}, {FL, 0}, {BL, 0}, {BR, 0}},
				   0,
				   0,
				   0,
				   0,
				   0,
				   0,
				   0};
	movement[L] = {// URF槽的元素被UFL槽的元素替代，且顺时针扭转，方向加1
				   {{URF, 0}, {ULB, 1}, {DBL, 2}, {UBR, 0}, {DFR, 0}, {UFL, 2}, {DLF, 1}, {DRB, 0}},
				   {{UR, 0}, {UF, 0}, {BL, 0}, {UB, 0}, {DR, 0}, {DF, 0}, {FL, 0}, {DB, 0}, {FR, 0}, {UL, 0}, {DL, 0}, {BR, 0}},
				   0,
				   0,
				   0,
				   0,
				   0,
				   0,
				   0};
	movement[R] = {// URF槽的元素被UFL槽的元素替代，且顺时针扭转，方向加1
				   {{DFR, 2}, {UFL, 0}, {ULB, 0}, {URF, 1}, {DRB, 1}, {DLF, 0}, {DBL, 0}, {UBR, 2}},
				   {{FR, 0}, {UF, 0}, {UL, 0}, {UB, 0}, {BR, 0}, {DF, 0}, {DL, 0}, {DB, 0}, {DR, 0}, {FL, 0}, {BL, 0}, {UR, 0}},
				   0,
				   0,
				   0,
				   0,
				   0,
				   0,
				   0};
	movement[F] = {// URF槽的元素被UFL槽的元素替代，且顺时针扭转，方向加1
				   {{UFL, 1}, {DLF, 2}, {ULB, 0}, {UBR, 0}, {URF, 2}, {DFR, 1}, {DBL, 0}, {DRB, 0}},
				   {{UR, 0}, {FL, 1}, {UL, 0}, {UB, 0}, {DR, 0}, {FR, 1}, {DL, 0}, {DB, 0}, {UF, 1}, {DF, 1}, {BL, 0}, {BR, 0}},
				   0,
				   0,
				   0,
				   0,
				   0,
				   0,
				   0};
	movement[B] = {// URF槽的元素被UFL槽的元素替代，且顺时针扭转，方向加1
				   {{URF, 0}, {UFL, 0}, {UBR, 1}, {DRB, 2}, {DFR, 0}, {DLF, 0}, {ULB, 2}, {DBL, 1}},
				   {{UR, 0}, {UF, 0}, {UL, 0}, {BR, 1}, {DR, 0}, {DF, 0}, {DL, 0}, {BL, 1}, {FR, 0}, {FL, 0}, {UB, 1}, {DB, 1}},
				   0,
				   0,
				   0,
				   0,
				   0,
				   0,
				   0};
	CubeGenerate Cube;
	
	InitCpMoveTable();
	InitEpudMoveTable();
	InitEpmMoveTable();
	InitSliceMoveTable();
	InitTwistMoveTable();
	initFlipMoveTable();

  	InitTwistPruneTable();
 	InitFlipPruneTable();
	InitSlicePruneTable();
	InitCpPruneTable();
	InitEpudPruneTable();
	InitEpmPruneTable();   

	cout << "欢迎来到简化版kociemba algorithm解魔方程序" << endl;
	cout << "请输入标准打乱公式" << endl;
	//Cube.GetCube();
	//
	/*
	Cube.DecodeCorner();
	Cube.DecodeEdge();
	Cube.EncodeCorner();
	Cube.EncodeEdge();
	*/

/* 	int i;
	Cube.cube_state.index_edge_o=3;
	Cube.cube_state.index_other_p=4000;
	Cube.cube_state.index_middle_p=10;
	Cube.cube_state.index_combination=100;
	Cube.DecodeEdge(4);
	Cube.ShowState(3);
 */
/*
	string debug;
	getline(cin,debug);
	for(int i=0;i<=11;i++)
	{
		Cube.cube_state.eo[i].e=(Edge)((int)debug[i]-int('0'));
	}
	Cube.EncodeEdge();
	Cube.ShowState(4);
*/
}