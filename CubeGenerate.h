#ifndef CUBE_GENERATE_H
#define CUBE_GENERATE_H
#endif
#include <vector>
#include <string>
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
    int index_mid_edge_p; //
    int index_other_edge_p;
};

struct CubieCube_with_color
{
    corner_with_color co_with_color[8];
    edge_with_color eo_with_color[12];
    int index_corner_o;
    int index_corner_p;
    int index_edge_o;
    int index_mid_edge_p; //
    int index_other_edge_p;
};

class CubeGenerate
{ // 表示魔方产生的一个类

private:
    CubieCube Init;
    CubieCube Move[6];
    CubieCube CubeState;
    string disrupt_string; // 打乱公式
public:
    CubeGenerate();                          // 初始化
    void EncodeCorner(CubieCube Cube_State); // encoding
    void DecodeCorner(CubieCube Cube_State); // decoding
    void EncodeEdge(CubieCube Cube_State);
    void DecodeEdge(CubieCube Cube_State);
    void CornerTransform(const CubieCube* origin, const CubieCube* transform, const CubieCube* result); // 角块变换
    void EdgeTramsform(const CubieCube* origin, const CubieCube* transform, const CubieCube* result); // 棱块变换
};
// 求组合数 n是下标，m是上标
long long n_C_m(int n, int m);
