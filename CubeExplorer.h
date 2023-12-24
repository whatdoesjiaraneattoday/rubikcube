#ifndef CUBE_EXPLORER_H
#define CUBE_EXPLORER_H

#define STRATEGY 1

#include<vector>
#include<string>
#include<fstream>
#include<iostream>

//表示某个机械手状态的结构，作为HandState的成员
struct HandStateForOne {
	bool isReady = true;	//机械手是否处于正确的方向（即初始状态的U-D方向，不妨碍另一只机械手的转动）
	bool isTight = true;	//机械手是否夹紧
};

//表示机械手状态的结构，其中left表示左手，right表示右手
struct HandState {
	HandStateForOne left;
	HandStateForOne right;
	//构造方法，满足CubicExplore类的构造函数中默认参数的需求
	HandState(bool lr=true,bool lt=true,bool rr=true,bool rt=true){
		left.isReady = lr;
		left.isTight = lt;
		right.isReady = rr;
		right.isTight = rt;
	}
};

//表示机械手各操作的枚举
enum class Operation {
	R,		//右手顺时针转动
	_R ,	//右手逆时针转动
	F,		//左手顺时针转动
	_F ,	//左手逆时针转动
	R2 ,	//R面转动180°
	F2 ,	//F面转动180°
	LeftLoose,	//左手松开		
	LeftTight,	//左手夹紧
	RightLoose,	//右手松开
	RightTight	//右手夹紧
};

using namespace std;

ostream& operator<<(ostream&, const Operation&);

//表示魔方解决器的一个类
class CubeExplorer {
private:
	vector<string> vecStrSerial;		//保存转换后的串口序列字符串
	vector<string> strNorVec;			//string容器，保存分割后得到的一个个表示单个公式操作的字符串
	vector<Operation> macVec;			//自定义枚举类型Operation容器，保存转换后得到的机械手操作序列
	string target;						//字符串，存储将要处理的普通公式序列
	int shortestTime = 99999;
	vector<Operation> finalVec;
public:
	HandState handState;	//自定义类HandState类型，表示当前机械手状态
	int transCnt = 0;					//记录魔方翻转次数
	
	CubeExplorer(char* cstr="", const HandState& hs=HandState(true,true,true,true));
	
	friend ostream& operator<<(ostream&, const Operation&);		//友元操作符重载函数支持Operation类型和cout的直接使用，主要用于调试

	void SetTarget(string);
	vector<string>& GetVecStrSerial();

	//以下操作定义针对魔方本身，封装机械爪操作
	void OnR(vector<string>::iterator&);		//R面顺时针转动
	void On_R(vector<string>::iterator&);		//R面逆时针转动
	void OnR2(vector<string>::iterator&);		//R面转动180°
	void OnF(vector<string>::iterator&);		//F面类似
	void On_F(vector<string>::iterator&);		//
	void OnF2(vector<string>::iterator&);		//
	void OnRR(vector<string>::iterator&);		//魔方沿R面顺时针方向整体转动
	void On_RR(vector<string>::iterator&);		//魔方沿R面逆时针方向整体转动
	void OnRR2(vector<string>::iterator&);		//魔方沿R面逆时针方向整体转动180°
	void OnFF(vector<string>::iterator&);		//F类似
	void On_FF(vector<string>::iterator&);		//
	void OnFF2(vector<string>::iterator&);		//

	void GetLeftReadyAndTight();	//使左手复位至夹紧且U-D状态(90/270°状态)
	void GetRightReadyAndTight();	//使右手复位至夹紧且U-D状态(90/270°状态)
	void LeftLoose();				//松开左手
	void LeftTight();				//夹紧左手
	void LeftReady();				//左手复位至U-D状态(90/270°状态)
	void RightLoose();				//松开右手
	void RightTight();				//夹紧右手
	void RightReady();				//右手复位至U-D状态(90/270°状态)
	void GetShortestWay();			//核心成员函数，将target中存储的普通公式序列转换为机械手操作序列并存储到macVec容器中
	void ShowOperations();			//打印操作序列，主要用于调试和测试
	int GetOperationTime(vector<Operation> maneuver);         //获取完成操作序列需要的时间
	void GetStrNorVec();            //将魔方序列字符串分割为单个字符
	void Reset();
	void dfs(vector<string> &operation_seq); // 迭代搜索最优机械手操作序列
};


#endif