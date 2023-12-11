#ifndef CUBE_GENERATE_H
#define CUBE_GENERATE_H

#include <vector>
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

typedef enum
{
    URF,
    UFL,
    ULB,
    UBR,
    DFR,
    DLF,
    DBL,
    DRB
} Corner;
typedef enum
{
    UR,
    UF,
    UL,
    UB,
    DR,
    DF,
    DL,
    DB,
    FR,
    FL,
    BL,
    BR
} Edge;
typedef enum
{
    U,
    D,
    L,
    R,
    F,
    B
} Direction;
typedef enum
{
    g,
    w,
    o,
    r,
    y,
    b
} Color;

struct corner // 角块
{
    Corner c; //
    int o;    // orient
};

struct edge // 棱块
{
    Edge e;
    int o;
};

struct corner_with_color // 角块带色相 感觉没用
{
    Corner c;
    int color[3];
    int o;
};

struct edge_with_color // 棱块带色相 感觉没用
{
    Edge e;
    int color[2]; // 带的三种颜色
    int o;
};

struct CubieCube
{
    corner co[8];
    edge eo[12];
    int index_corner_o;
    int index_corner_p;
    int index_edge_o;
    int index_edge_p; //
    int index_middle_p;
    int index_other_p;
    int index_combination;
};

struct CubieCube_with_color
{
    corner_with_color co_with_color[8];
    edge_with_color eo_with_color[12];
    int index_corner_o;
    int index_corner_p;
    int index_edge_o;
    int index_edge_p; //
    int index_middle_p;
    int index_other_p;
    int index_combination;
};
// 操作序列
struct Solution
{
    int operate_sequence[10000];
    int len;
    string equation[10000];
};

struct CubeOperate // 魔方操作
{
    Direction a; // 操作的面
    int b;       // 操作方向，顺时针90°、逆时针90°、180°
};

class CubeGenerate
{ // 表示魔方产生的一个类

private:
    CubieCube Init;
    CubieCube move[6];
    string disrupt_string; // 打乱公式
public:
    CubieCube cube_state;
    CubeGenerate() // 初始化
    {
        for (int i = 0; i <= 7; i++)
        {
            cube_state.co[i].c = Corner(i);
            cube_state.co[i].o = 0;
        }
        for (int i = 0; i <= 11; i++)
        {
            cube_state.eo[i].e = Edge(i);
            cube_state.eo[i].o = 0;
        }
        cube_state.index_combination = 0;
        cube_state.index_corner_o = 0;
        cube_state.index_corner_p = 0;
        cube_state.index_edge_o = 0;
        cube_state.index_edge_p = 0;
        cube_state.index_middle_p = 0;
        cube_state.index_other_p = 0;
    }

    void EncodeCorner(void); // encoding
    void DecodeCorner(void); // decoding
    void EncodeEdge(void);
    void DecodeEdge(int num);
    void CornerTransform(const CubieCube *transform); // 角块变换
    void EdgeTransform(const CubieCube *transform);   // 棱块变换
    void EdgeTransform1(const CubieCube *transform);   // 棱块变换
    void CubeMove(int m);
    void GetCube(void);
    // i=0 show o i=1 show c  i=2 show o i=3 show e
    void ShowState(int n = 0);
};
// 求组合数 n是下标，m是上标
long long n_C_m(int n, int m);
// 初始化角块位置转动表
void InitCpMoveTable();
// 初始化上下层棱块位置转动表
void InitEpudMoveTable();
// 初始化中间层棱块位置转动表
void InitEpmMoveTable();
// 初始化棱块位置组合转动表
void InitSliceMoveTable();
// 初始化角块方向转动表
void InitTwistMoveTable();
// 初始化棱块方向转动表
void initFlipMoveTable();
// 角块方向的剪枝表
void InitTwistPruneTable();
// 棱块方向的剪枝表
void InitFlipPruneTable();
// 棱块位置组合的剪枝表
void InitSlicePruneTable();
// 角块位置剪枝表
void InitCpPruneTable();
// 上下层棱块位置剪枝表
void InitEpudPruneTable();
// 中间层棱块位置剪枝表
void InitEpmPruneTable();
// DFS phase 1
void DFSearch1(CubeGenerate Cube, int twist, int flip, int slice, int togo1);
// DFS phase 2
void DFSearch2(int cp,int epud,int epm,int togo2);
// 搜索
void Search(CubeGenerate Cube);

#endif