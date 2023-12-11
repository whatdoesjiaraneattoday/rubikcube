#ifndef CUBE_EXPLORER_H
#define CUBE_EXPLORER_H

#define STRATEGY 1

#include "OperationBinaryTree.h"

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




using namespace std;

ostream& operator<<(ostream&, const Operation&);

//表示魔方解决器的一个类
class CubeExplorer {
private:
	vector<string> vecStrSerial;		//保存转换后的串口序列字符串
	vector<string> strNorVec;			//string容器，保存分割后得到的一个个表示单个公式操作的字符串
	vector<Operation> macVec;			//自定义枚举类型Operation容器，保存转换后得到的机械手操作序列
	string target;						//字符串，存储将要处理的普通公式序列
public:
	HandState handState;	//自定义类HandState类型，表示当前机械手状态
	int transCnt = 0;					//记录魔方翻转次数
	
	CubeExplorer(char* cstr="", const HandState &hs=HandState(true,true,true,true));
	
	friend ostream& operator<<(ostream&, const Operation&);		//友元操作符重载函数支持Operation类型和cout的直接使用，主要用于调试

	void SetTarget(string);
	vector<string>& GetVecStrSerial();

	//以下操作定义针对魔方本身，封装机械爪操作
	void OnR(vector<string>::iterator&,int direction=0);		//R面顺时针转动
	void On_R(vector<string>::iterator&,int direction=0);		//R面逆时针转动
	void OnR2(vector<string>::iterator&,int direction=0);		//R面转动180°
	void OnF(vector<string>::iterator&,int direction=0);		//F面类似
	void On_F(vector<string>::iterator&,int direction=0);		//
	void OnF2(vector<string>::iterator&,int direction=0);		//
	void OnRR(vector<string>::iterator&,int direction=0);		//魔方沿R面顺时针方向整体转动
	void On_RR(vector<string>::iterator&,int direction=0);		//魔方沿R面逆时针方向整体转动
	void OnRR2(vector<string>::iterator&,int direction=0);		//魔方沿R面逆时针方向整体转动180°
	void OnFF(vector<string>::iterator&,int direction=0);		//F类似
	void On_FF(vector<string>::iterator&,int direction=0);		//
	void OnFF2(vector<string>::iterator&,int direction=0);		//

	void GetLeftReadyAndTight(int direction=0);	//使左手复位至夹紧且U-D状态(90/270°状态)
	void GetRightReadyAndTight(int direction=0);	//使右手复位至夹紧且U-D状态(90/270°状态)
	void LeftLoose(int direction=0);				//松开左手
	void LeftTight(int direction=0);				//夹紧左手
	void LeftReady(int direction=0);				//左手复位至U-D状态(90/270°状态)
	void RightLoose(int direction=0);				//松开右手
	void RightTight(int direction=0);				//夹紧右手
	void RightReady(int direction=0);				//右手复位至U-D状态(90/270°状态)
	void GetShortestWay();			//核心成员函数，将target中存储的普通公式序列转换为机械手操作序列并存储到macVec容器中
	void ShowOperations();			//打印操作序列，主要用于调试和测试
	void Reset();
};


#endif