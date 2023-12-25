#include"CubeExplorer.h"
CubeExplorer::CubeExplorer(char* cstr,const HandState& hs):target(cstr),handState(hs){}

void CubeExplorer::SetTarget(string str) { target = str; }

vector<string>& CubeExplorer::GetVecStrSerial() { return vecStrSerial; }

void CubeExplorer::OnR(vector<string>& operation_seq, vector<Operation>& maneuver) {
	RightTight(maneuver);											//右爪夹紧
	GetLeftReadyAndTight(maneuver);									//左爪调整至90/270°且夹紧
	maneuver.push_back(Operation::R);							//右爪顺时针转动90°（存储到容器内，之后进行发送）
	handState.right.isReady = !handState.right.isReady;		//设置右爪状态参数

	transCnt++;
}

void CubeExplorer::On_R(vector<string>& operation_seq, vector<Operation>& maneuver) {
	RightTight(maneuver);
	GetLeftReadyAndTight(maneuver);
	maneuver.push_back(Operation::_R);
	handState.right.isReady = !handState.right.isReady; 

	transCnt++;
}

void CubeExplorer::OnF(vector<string>& operation_seq, vector<Operation>& maneuver) {
	LeftTight(maneuver);
	GetRightReadyAndTight(maneuver);
	maneuver.push_back(Operation::F);
	handState.left.isReady = !handState.left.isReady;

	transCnt++;
}

void CubeExplorer::On_F(vector<string>& operation_seq, vector<Operation>& maneuver) {
	LeftTight(maneuver);
	GetRightReadyAndTight(maneuver);
	maneuver.push_back(Operation::_F);
	handState.left.isReady = !handState.left.isReady;

	transCnt++;
}

void CubeExplorer::OnRR(vector<string>& operation_seq, vector<Operation>& maneuver) {
	RightTight(maneuver);											//右爪夹紧
	LeftLoose(maneuver);											//左爪松开
	LeftReady(maneuver);											//左爪转动至90/270°状态
	maneuver.push_back(Operation::R);							//右爪顺时针转动90°
	handState.right.isReady = !handState.right.isReady;		//设置右爪状态参数
	for (auto it = operation_seq.begin() + 1; it != operation_seq.end(); it++) {	//由于魔方整体转动后，面的定义发生变化，
		if (*it == "U") *it = "B";							//因此需要遍历之后的操作，全部调整为转变后的定义
		else if (*it == "B") *it = "D";						//
		else if (*it == "D") *it = "F";
		else if (*it == "F") *it = "U";
		else if (*it == "U'") *it = "B'";
		else if (*it == "B'") *it = "D'";
		else if (*it == "D'") *it = "F'";
		else if (*it == "F'") *it = "U'";
		else if (*it == "U2") *it = "B2";
		else if (*it == "B2") *it = "D2";
		else if (*it == "D2") *it = "F2";
		else if (*it == "F2") *it = "U2";
	}

	transCnt++;
}

void CubeExplorer::On_RR(vector<string>& operation_seq, vector<Operation>& maneuver) {
	RightTight(maneuver);
	LeftLoose(maneuver);
	LeftReady(maneuver);
	maneuver.push_back(Operation::_R);
	handState.right.isReady = !handState.right.isReady;
	for (auto it = operation_seq.begin() + 1; it != operation_seq.end(); it++) {
		if (*it == "U") *it = "F";
		else if (*it == "B") *it = "U";
		else if (*it == "D") *it = "B";
		else if (*it == "F") *it = "D";
		else if (*it == "U'") *it = "F'";
		else if (*it == "B'") *it = "U'";
		else if (*it == "D'") *it = "B'";
		else if (*it == "F'") *it = "D'";
		else if (*it == "U2") *it = "F2";
		else if (*it == "B2") *it = "U2";
		else if (*it == "D2") *it = "B2";
		else if (*it == "F2") *it = "D2";
	}

	transCnt++;
}

void CubeExplorer::OnFF(vector<string>& operation_seq, vector<Operation>& maneuver) {
	LeftTight(maneuver);
	RightLoose(maneuver);
	RightReady(maneuver);
	maneuver.push_back(Operation::F);
	handState.left.isReady = !handState.left.isReady;
	for (auto it = operation_seq.begin() + 1; it != operation_seq.end(); it++) {
		if (*it == "U") *it = "R";
		else if (*it == "R") *it = "D";
		else if (*it == "D") *it = "L";
		else if (*it == "L") *it = "U";
		else if (*it == "U'") *it = "R'";
		else if (*it == "R'") *it = "D'";
		else if (*it == "D'") *it = "L'";
		else if (*it == "L'") *it = "U'";
		else if (*it == "U2") *it = "R2";
		else if (*it == "R2") *it = "D2";
		else if (*it == "D2") *it = "L2";
		else if (*it == "L2") *it = "U2";
	}

	transCnt++;
}

void CubeExplorer::On_FF(vector<string>& operation_seq, vector<Operation>& maneuver) {
	LeftTight(maneuver);
	RightLoose(maneuver);
	RightReady(maneuver);
	maneuver.push_back(Operation::_F);
	handState.left.isReady = !handState.left.isReady;
	for (auto it = operation_seq.begin() + 1; it != operation_seq.end(); it++) {
		if (*it == "U") *it = "L";
		else if (*it == "R") *it = "U";
		else if (*it == "D") *it = "R";
		else if (*it == "L") *it = "D";
		else if (*it == "U'") *it = "L'";
		else if (*it == "R'") *it = "U'";
		else if (*it == "D'") *it = "R'";
		else if (*it == "L'") *it = "D'";
		else if (*it == "U2") *it = "L2";
		else if (*it == "R2") *it = "U2";
		else if (*it == "D2") *it = "R2";
		else if (*it == "L2") *it = "D2";
	}

	transCnt++;
}

void CubeExplorer::OnRR2(vector<string>& operation_seq, vector<Operation>& maneuver) {
	RightTight(maneuver);
	LeftLoose(maneuver);
	LeftReady(maneuver);
	maneuver.push_back(Operation::R2);
	for (auto it = operation_seq.begin() + 1; it != operation_seq.end(); it++) {
		if (*it == "U") *it = "D";
		else if (*it == "B") *it = "F";
		else if (*it == "D") *it = "U";
		else if (*it == "F") *it = "B";
		else if (*it == "U'") *it = "D'";
		else if (*it == "B'") *it = "F'";
		else if (*it == "D'") *it = "U'";
		else if (*it == "F'") *it = "B'";
		else if (*it == "U2") *it = "D2";
		else if (*it == "B2") *it = "F2";
		else if (*it == "D2") *it = "U2";
		else if (*it == "F2") *it = "B2";
	}

	transCnt++;
}

void CubeExplorer::OnFF2(vector<string>& operation_seq, vector<Operation>& maneuver) {
	LeftTight(maneuver);
	RightLoose(maneuver);
	RightReady(maneuver);
	maneuver.push_back(Operation::F2);
	for (auto it = operation_seq.begin() + 1; it != operation_seq.end(); it++) {
		if (*it == "U") *it = "D";
		else if (*it == "R") *it = "L";
		else if (*it == "D") *it = "U";
		else if (*it == "L") *it = "R";
		else if (*it == "U'") *it = "D'";
		else if (*it == "R'") *it = "L'";
		else if (*it == "D'") *it = "U'";
		else if (*it == "L'") *it = "R'";
		else if (*it == "U2") *it = "D2";
		else if (*it == "R2") *it = "L2";
		else if (*it == "D2") *it = "U2";
		else if (*it == "L2") *it = "R2";
	}

	transCnt++;
}

void CubeExplorer::OnR2(vector<string>& operation_seq, vector<Operation>& maneuver) {
	RightTight(maneuver);
	GetLeftReadyAndTight(maneuver);
	maneuver.push_back(Operation::R2);

	transCnt++;
}

void CubeExplorer::OnF2(vector<string>& operation_seq, vector<Operation>& maneuver) {
	LeftTight(maneuver);
	GetRightReadyAndTight(maneuver);
	maneuver.push_back(Operation::F2);

	transCnt++;
}

void CubeExplorer::OnRR_2(vector<string>::iterator& iter) {
	RightTight(macVec);											//��צ�н�
	LeftLoose(macVec);											//��צ�ɿ�
	LeftReady(macVec);											//��צת����90/270��״̬
	macVec.push_back(Operation::R);							//��צ˳ʱ��ת��90��
	handState.right.isReady = !handState.right.isReady;		//������צ״̬����
	for (auto it = iter + 1; it != strNorVec.end(); it++) {	//����ħ������ת������Ķ��巢���仯��
		if (*it == "U") *it = "B";							//�����Ҫ����֮��Ĳ�����ȫ������Ϊת���Ķ���
		else if (*it == "B") *it = "D";						//
		else if (*it == "D") *it = "F";
		else if (*it == "F") *it = "U";
		else if (*it == "U'") *it = "B'";
		else if (*it == "B'") *it = "D'";
		else if (*it == "D'") *it = "F'";
		else if (*it == "F'") *it = "U'";
		else if (*it == "U2") *it = "B2";
		else if (*it == "B2") *it = "D2";
		else if (*it == "D2") *it = "F2";
		else if (*it == "F2") *it = "U2";
	}

	transCnt++;
}

void CubeExplorer::On_RR_2(vector<string>::iterator& iter) {
	RightTight(macVec);
	LeftLoose(macVec);
	LeftReady(macVec);
	macVec.push_back(Operation::_R);
	handState.right.isReady = !handState.right.isReady;
	for (auto it = iter + 1; it != strNorVec.end(); it++) {
		if (*it == "U") *it = "F";
		else if (*it == "B") *it = "U";
		else if (*it == "D") *it = "B";
		else if (*it == "F") *it = "D";
		else if (*it == "U'") *it = "F'";
		else if (*it == "B'") *it = "U'";
		else if (*it == "D'") *it = "B'";
		else if (*it == "F'") *it = "D'";
		else if (*it == "U2") *it = "F2";
		else if (*it == "B2") *it = "U2";
		else if (*it == "D2") *it = "B2";
		else if (*it == "F2") *it = "D2";
	}

	transCnt++;
}

void CubeExplorer::OnFF_2(vector<string>::iterator& iter) {
	LeftTight(macVec);
	RightLoose(macVec);
	RightReady(macVec);
	macVec.push_back(Operation::F);
	handState.left.isReady = !handState.left.isReady;
	for (auto it = iter + 1; it != strNorVec.end(); it++) {
		if (*it == "U") *it = "R";
		else if (*it == "R") *it = "D";
		else if (*it == "D") *it = "L";
		else if (*it == "L") *it = "U";
		else if (*it == "U'") *it = "R'";
		else if (*it == "R'") *it = "D'";
		else if (*it == "D'") *it = "L'";
		else if (*it == "L'") *it = "U'";
		else if (*it == "U2") *it = "R2";
		else if (*it == "R2") *it = "D2";
		else if (*it == "D2") *it = "L2";
		else if (*it == "L2") *it = "U2";
	}

	transCnt++;
}

void CubeExplorer::On_FF_2(vector<string>::iterator& iter) {
	LeftTight(macVec);
	RightLoose(macVec);
	RightReady(macVec);
	macVec.push_back(Operation::_F);
	handState.left.isReady = !handState.left.isReady;
	for (auto it = iter + 1; it != strNorVec.end(); it++) {
		if (*it == "U") *it = "L";
		else if (*it == "R") *it = "U";
		else if (*it == "D") *it = "R";
		else if (*it == "L") *it = "D";
		else if (*it == "U'") *it = "L'";
		else if (*it == "R'") *it = "U'";
		else if (*it == "D'") *it = "R'";
		else if (*it == "L'") *it = "D'";
		else if (*it == "U2") *it = "L2";
		else if (*it == "R2") *it = "U2";
		else if (*it == "D2") *it = "R2";
		else if (*it == "L2") *it = "D2";
	}

	transCnt++;
}

void CubeExplorer::OnRR2_2(vector<string>::iterator& iter) {
	RightTight(macVec);
	LeftLoose(macVec);
	LeftReady(macVec);
	macVec.push_back(Operation::R2);
	for (auto it = iter + 1; it != strNorVec.end(); it++) {
		if (*it == "U") *it = "D";
		else if (*it == "B") *it = "F";
		else if (*it == "D") *it = "U";
		else if (*it == "F") *it = "B";
		else if (*it == "U'") *it = "D'";
		else if (*it == "B'") *it = "F'";
		else if (*it == "D'") *it = "U'";
		else if (*it == "F'") *it = "B'";
		else if (*it == "U2") *it = "D2";
		else if (*it == "B2") *it = "F2";
		else if (*it == "D2") *it = "U2";
		else if (*it == "F2") *it = "B2";
	}

	transCnt++;
}

void CubeExplorer::OnFF2_2(vector<string>::iterator& iter) {
	LeftTight(macVec);
	RightLoose(macVec);
	RightReady(macVec);
	macVec.push_back(Operation::F2);
	for (auto it = iter + 1; it != strNorVec.end(); it++) {
		if (*it == "U") *it = "D";
		else if (*it == "R") *it = "L";
		else if (*it == "D") *it = "U";
		else if (*it == "L") *it = "R";
		else if (*it == "U'") *it = "D'";
		else if (*it == "R'") *it = "L'";
		else if (*it == "D'") *it = "U'";
		else if (*it == "L'") *it = "R'";
		else if (*it == "U2") *it = "D2";
		else if (*it == "R2") *it = "L2";
		else if (*it == "D2") *it = "U2";
		else if (*it == "L2") *it = "R2";
	}

	transCnt++;
}


void CubeExplorer::LeftLoose(vector<Operation>& maneuver) {
	if (handState.left.isTight) {
		maneuver.push_back(Operation::LeftLoose);
		handState.left.isTight = false;
	}
}

void CubeExplorer::LeftTight(vector<Operation>& maneuver) {
	if (!handState.left.isTight) {
		if ((!handState.right.isReady) && (!handState.left.isReady)) {
			maneuver.push_back(Operation::F);
		}
		maneuver.push_back(Operation::LeftTight);
		handState.left.isTight = true;
	}
}

void CubeExplorer::LeftReady(vector<Operation>& maneuver) {
	if (!handState.left.isReady) {
		maneuver.push_back(Operation::F);
		handState.left.isReady = true;
	}
}

void CubeExplorer::RightLoose(vector<Operation>& maneuver) {
	if (handState.right.isTight) {
		maneuver.push_back(Operation::RightLoose);
		handState.right.isTight = false;
	}
}


void CubeExplorer::RightTight(vector<Operation>& maneuver) {
	if (!handState.right.isTight) {
		if ((!handState.right.isReady) && (!handState.left.isReady)) {
			maneuver.push_back(Operation::R);
		}
		maneuver.push_back(Operation::RightTight);
		handState.right.isTight = true;
	}
}

void CubeExplorer::RightReady(vector<Operation>& maneuver) {
	if (!handState.right.isReady) {
		maneuver.push_back(Operation::R);
		handState.right.isReady = true;
	}
}

void CubeExplorer::GetLeftReadyAndTight(vector<Operation>& maneuver) {
	if (handState.left.isReady) {
		if (!handState.left.isTight) {
			maneuver.push_back(Operation::LeftTight);
			handState.left.isTight = true;
		}
	}
	else {
		if (handState.left.isTight) {
			maneuver.push_back(Operation::LeftLoose);
			maneuver.push_back(Operation::F);
			maneuver.push_back(Operation::LeftTight);
		}
		else {
			maneuver.push_back(Operation::F);
			maneuver.push_back(Operation::LeftTight);
			handState.left.isTight = true;
		}
		handState.left.isReady = true;
	}
}

void CubeExplorer::GetRightReadyAndTight(vector<Operation>& maneuver) {
	if (handState.right.isReady) {
		if (!handState.right.isTight) {
			maneuver.push_back(Operation::RightTight);
			handState.right.isTight = true;
		}
	}
	else {
		if (handState.right.isTight) {
			maneuver.push_back(Operation::RightLoose);
			maneuver.push_back(Operation::R);
			maneuver.push_back(Operation::RightTight);
		}
		else {
			maneuver.push_back(Operation::R);
			maneuver.push_back(Operation::RightTight);
			handState.right.isTight = true;
		}
		handState.right.isReady = true;
	}
}

void CubeExplorer::GetStrNorVec() {
	string::size_type lastSpace = 0;	//记录上一次遇到空格的位置
	//将原始字符串分割为多个表示单个操作的字符串并存放到strNorVec容器中
	string::size_type i = 0;
	for (; i < target.length(); i++) {
		if (target[i] == ' ') {
			string strTemp;
			for (string::size_type index = lastSpace; index < i; index++) {
				strTemp.push_back(target[index]);
			}
			strNorVec.push_back(strTemp);
			lastSpace = i + 1;
		}
	}
}

void CubeExplorer::dfs(vector<string> operation_seq, vector<Operation> maneuver) {
	if (operation_seq.size() == 0) {
		if (CubeExplorer::GetOperationTime(maneuver) < shortestTime) {
			shortestTime = CubeExplorer::GetOperationTime(maneuver);
			macVec = maneuver;
		}
	}
	else {
		auto iter = operation_seq.begin();
		vector<string> operation_seq2 = operation_seq;
		vector<Operation> maneuver2 = maneuver;
		if (*iter == "R") {
			OnR(operation_seq2, maneuver2);
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "F") {
			OnF(operation_seq2, maneuver2);
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "R'") {
			On_R(operation_seq2, maneuver2);
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "F'") {
			On_F(operation_seq2, maneuver2);
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "R2") {
			OnR2(operation_seq2, maneuver2);
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "F2") {
			OnF2(operation_seq2, maneuver2);
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "B") {
			OnRR2(operation_seq2, maneuver2);
			OnF(operation_seq2, maneuver2);
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "L") {
			OnFF2(operation_seq2, maneuver2);
			OnR(operation_seq2, maneuver2);
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "U") {
			OnFF(operation_seq2, maneuver2);
			OnR(operation_seq2, maneuver2); // 策略1
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);

			operation_seq2 = operation_seq;
			On_RR(operation_seq2, maneuver2);
			OnF(operation_seq2, maneuver2); // 策略2
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "D") {
			OnRR(operation_seq2, maneuver2);
			OnF(operation_seq2, maneuver2); // 策略1
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);

			operation_seq2 = operation_seq;
			On_FF(operation_seq2, maneuver2);
			OnR(operation_seq2, maneuver2); // 策略2
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "B'") {
			OnRR2(operation_seq2, maneuver2);
			On_F(operation_seq2, maneuver2);
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "L'") {
			OnFF2(operation_seq2, maneuver2);
			On_R(operation_seq2, maneuver2);
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "U'") {
			OnFF(operation_seq2, maneuver2);
			On_R(operation_seq2, maneuver2); // 策略1
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);

			operation_seq2 = operation_seq;
			On_RR(operation_seq2, maneuver2);
			On_F(operation_seq2, maneuver2); // 策略2
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "D'") {
			On_FF(operation_seq2, maneuver2);
			On_R(operation_seq2, maneuver2); // 策略1
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);

			operation_seq2 = operation_seq;
			OnRR(operation_seq2, maneuver2);
			On_F(operation_seq2, maneuver2); // 策略2
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "B2") {
			OnRR2(operation_seq2, maneuver2);
			OnF2(operation_seq2, maneuver2);
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "L2") {
			OnFF2(operation_seq2, maneuver2);
			OnR2(operation_seq2, maneuver2);
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "U2") {
			OnFF(operation_seq2, maneuver2);
			OnR2(operation_seq2, maneuver2); // 策略1
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);

			operation_seq2 = operation_seq;
			On_RR(operation_seq2, maneuver2);
			OnF2(operation_seq2, maneuver2); // 策略2
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
		else if (*iter == "D2") {
			On_FF(operation_seq2, maneuver2);
			OnR2(operation_seq2, maneuver2); // 策略1
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);

			operation_seq2 = operation_seq;
			OnRR(operation_seq2, maneuver2);
			OnF2(operation_seq2, maneuver2); // 策略2
			operation_seq2.erase(operation_seq2.begin());
			dfs(operation_seq2, maneuver2);
		}
	}
}

void CubeExplorer::GetShortestWay() {
	string::size_type lastSpace = 0;	//记录上一次遇到空格的位置
	//将原始字符串分割为多个表示单个操作的字符串并存放到strNorVec容器中
	string::size_type i = 0;
	for (; i < target.length(); i++) {
		if (target[i] == ' ') {
			string strTemp;
			for (string::size_type index = lastSpace; index < i; index++) {
				strTemp.push_back(target[index]);
			}
			strNorVec.push_back(strTemp);
			lastSpace = i + 1;
		}
	}

	transCnt = 0;
	for (auto iter = strNorVec.begin(); iter != strNorVec.end(); iter++) {
		if (*iter == "R") OnR(strNorVec,macVec);				//F和R面系列操作，无需魔方的整体转动就可以直接操作
		else if (*iter == "F") OnF(strNorVec, macVec);			//
		else if (*iter == "R'") On_R(strNorVec, macVec);			//
		else if (*iter == "F'") On_F(strNorVec, macVec);			//
		else if (*iter == "R2") OnR2(strNorVec, macVec);			//
		else if (*iter == "F2") OnF2(strNorVec, macVec);			//
		else if (*iter == "B") {
			OnRR2_2(iter);							//通用公式“B“，首先要魔方整体沿R方向旋转180°
			OnF(strNorVec, macVec);								//此时原来的B面成为F面，F面顺时针转动90°即可完成操作
		}
		else if (*iter == "L") {
			OnFF2_2(iter);
			OnR(strNorVec, macVec);
		}
		else if (*iter == "U") {
			if (STRATEGY == 1) {
				OnFF_2(iter);
				OnR(strNorVec, macVec);
			}
			else {
				//对于U、B两面的操作，有两个不同策略：1.魔方沿F面整体旋转后，右爪进行操作；2.魔方沿R面整体旋转后，左爪进行操作
				//我们需要根据机械爪的当前状态和当前操作其后紧跟的操作判断，哪一种策略得到的指令最少
				if (handState.left.isReady) {														//左爪处于90/270°状态
					if (handState.right.isReady &&													//右爪处于90/270°状态
						(iter + 1 != strNorVec.end()) &&											//紧跟的下一个操作是F、B面操作
						(*(iter + 1) == "F" || *(iter + 1) == "F'" || *(iter + 1) == "F2" ||		//
							*(iter + 1) == "B" || *(iter + 1) == "B'" || *(iter + 1) == "B2")) {		//
						   //若左右手都处于90/270°状态，那么无论先F后R或先R后F，当前操作需要的指令数是一样的。因此仅考虑当前操作之后的操作
						   //如果紧跟的操作是F面和B面操作，那么对于当前操作之后的那个操作，策略1比策略2少4个机械爪指令，因此采用策略1
						OnFF_2(iter);
						OnR(strNorVec, macVec);
					}
					else {
						//若左手处于90/270°状态而右手处于0/180°状态，那么对于当前操作，策略2比策略1少4个机械爪指令
						//若当前操作其后紧跟的那个操作不是对F、B面的操作，那么策略2得到的机械爪指令不大于策略1
						//（当紧跟的是R、L面操作时，策略2比策略1少4个指令；当紧跟的是D面操作时，两个策略等效），因此采用策略2
						On_RR_2(iter);
						OnF(strNorVec, macVec);
					}
				}
				else {
					//若左手处于0/180°状态，对于当前操作，策略1比策略2少4个指令
					//其后紧跟的指令，若为L、R面操作，则策略1比策略2少4个指令，这两个因素相互抵消；若为F、B面操作，策略1比策略2少4个指令
					//只要左手处于这个状态，就选择策略1
					OnFF_2(iter);
					OnR(strNorVec, macVec);
				}
			}
			
			
		}
		else if (*iter == "D") {
			if (STRATEGY == 1) {
				OnRR_2(iter);
				OnF(strNorVec, macVec);
			}
			else {
				if (handState.left.isReady) {
					if (handState.right.isReady &&
						(iter + 1 != strNorVec.end()) &&
						(*(iter + 1) == "F" || *(iter + 1) == "F'" || *(iter + 1) == "F2" || *(iter + 1) == "B" || *(iter + 1) == "B'" || *(iter + 1) == "B2")) {
						On_FF_2(iter);
						OnR(strNorVec, macVec);
					}
					else {
						OnRR_2(iter);
						OnF(strNorVec, macVec);
					}
				}
				else {
					On_FF_2(iter);
					OnR(strNorVec, macVec);
				}
			}
		}
		else if (*iter == "B'") {
			OnRR2_2(iter);
			On_F(strNorVec, macVec);
		}
		else if (*iter == "L'") {
			OnFF2_2(iter);
			On_R(strNorVec, macVec);
		}
		else if (*iter == "U'") {
			if (STRATEGY == 1) {
				OnFF_2(iter);
				On_R(strNorVec, macVec);
			}
			else {
				if (handState.left.isReady) {
					if (handState.right.isReady &&
						(iter + 1 != strNorVec.end()) &&
						(*(iter + 1) == "F" || *(iter + 1) == "F'" || *(iter + 1) == "F2" || *(iter + 1) == "B" || *(iter + 1) == "B'" || *(iter + 1) == "B2")) {
						OnFF_2(iter);
						On_R(strNorVec, macVec);
					}
					else {
						On_RR_2(iter);
						On_F(strNorVec, macVec);
					}
				}
				else {
					OnFF_2(iter);
					On_R(strNorVec, macVec);
				}
			}
		}
		else if (*iter == "D'") {
			if (STRATEGY == 1) {
				OnRR_2(iter);
				On_F(strNorVec, macVec);
			}
			else {
				if (handState.left.isReady) {
					if (handState.right.isReady &&
						(iter + 1 != strNorVec.end()) &&
						(*(iter + 1) == "F" || *(iter + 1) == "F'" || *(iter + 1) == "F2" || *(iter + 1) == "B" || *(iter + 1) == "B'" || *(iter + 1) == "B2")) {
						On_FF_2(iter);
						On_R(strNorVec, macVec);
					}
					else {
						OnRR_2(iter);
						On_F(strNorVec, macVec);
					}
				}
				else {
					On_FF_2(iter);
					On_R(strNorVec, macVec);
				}
			}
		}
		else if (*iter == "B2") {
			OnRR2_2(iter);
			OnF2(strNorVec, macVec);
		}
		else if (*iter == "L2") {
			OnFF2_2(iter);
			OnR2(strNorVec, macVec);
		}
		else if (*iter == "U2") {
			if (STRATEGY == 1) {
				OnFF_2(iter);
				OnR2(strNorVec, macVec);
			}
			else {
				if (handState.left.isReady) {
					if (handState.right.isReady &&
						(iter + 1 != strNorVec.end()) &&
						(*(iter + 1) == "F" || *(iter + 1) == "F'" || *(iter + 1) == "F2" || *(iter + 1) == "B" || *(iter + 1) == "B'" || *(iter + 1) == "B2")) {
						OnFF_2(iter);
						OnR2(strNorVec, macVec);
					}
					else {
						On_RR_2(iter);
						OnF2(strNorVec, macVec);
					}
				}
				else {
					OnFF_2(iter);
					OnR2(strNorVec, macVec);
				}
			}
		}
		else if (*iter == "D2") {
			if (STRATEGY == 1) {
				OnRR_2(iter);
				OnF2(strNorVec, macVec);
			}
			else {
				if (handState.left.isReady) {
					if (handState.right.isReady &&
						(iter + 1 != strNorVec.end()) &&
						(*(iter + 1) == "F" || *(iter + 1) == "F'" || *(iter + 1) == "F2" || *(iter + 1) == "B" || *(iter + 1) == "B'" || *(iter + 1) == "B2")) {
						On_FF_2(iter);
						OnR2(strNorVec, macVec);
					}
					else {
						OnRR_2(iter);
						OnF2(strNorVec, macVec);
					}
				}
				else {
					On_FF_2(iter);
					OnR2(strNorVec, macVec);
				}
			}
		}
	}

	for (auto iter = macVec.begin(); iter != macVec.end(); iter++) {
		switch (*iter) {
		case Operation::F:
			vecStrSerial.push_back("#1P6T200\r\n");
			break;
		case Operation::_F:
			vecStrSerial.push_back("#1P7T200\r\n");
			break;
		case Operation::F2:
			vecStrSerial.push_back("#1P8T200\r\n");
			break;
		case Operation::LeftLoose:
			vecStrSerial.push_back("#2P0T200\r\n");
			break;
		case Operation::LeftTight:
			vecStrSerial.push_back("#2P1T200\r\n");
			break;
		case Operation::R:
			vecStrSerial.push_back("#3P6T200\r\n");
			break;
		case Operation::_R:
			vecStrSerial.push_back("#3P7T200\r\n");
			break;
		case Operation::R2:
			vecStrSerial.push_back("#3P8T200\r\n");
			break;
		case Operation::RightLoose:
			vecStrSerial.push_back("#4P0T200\r\n");
			break;
		case Operation::RightTight:
			vecStrSerial.push_back("#4P1T200\r\n");
			break;
		}
	}
}

void CubeExplorer::ShowOperations() {
	int cnt = 0;
	for (auto iter = macVec.cbegin(); iter != macVec.cend(); iter++) {
		if (*iter != Operation::LeftLoose&&*iter != Operation::LeftTight&&*iter != Operation::RightLoose&&*iter != Operation::RightTight) {
			cnt++;
		}
		cout << *iter <<"   ";
	}
	int maneuver_time;
	maneuver_time = GetOperationTime(macVec);

	cout << endl;
	cout << "Final operation time: " << maneuver_time << endl;
	cout << "All operations' count: " << macVec.size() << endl;
	cout << endl;
}

int CubeExplorer::GetOperationTime(vector<Operation> maneuver) {
	int time = 0;
	for (auto iter = maneuver.cbegin(); iter != maneuver.cend(); iter++) {
		switch (*iter) {
			case Operation::R: time += 1; break;
			case Operation::_R: time += 1; break;
			case Operation::F: time += 1; break;
			case Operation::_F: time += 1; break;
			case Operation::R2: time += 1; break;
			case Operation::F2: time += 1; break;
			case Operation::LeftLoose: time += 1; break;
			case Operation::LeftTight: time += 1; break;
			case Operation::RightLoose: time += 1; break;
			case Operation::RightTight: time += 1; break;
		}
	}
	//cout << time << endl;
	return time;
}

void CubeExplorer::GetSerial()
{
	for (auto iter = macVec.begin(); iter != macVec.end(); iter++) {
		switch (*iter) {
		case Operation::F:
			vecStrSerial.push_back("#1P6T200\r\n");
			break;
		case Operation::_F:
			vecStrSerial.push_back("#1P7T200\r\n");
			break;
		case Operation::F2:
			vecStrSerial.push_back("#1P8T200\r\n");
			break;
		case Operation::LeftLoose:
			vecStrSerial.push_back("#2P0T200\r\n");
			break;
		case Operation::LeftTight:
			vecStrSerial.push_back("#2P1T200\r\n");
			break;
		case Operation::R:
			vecStrSerial.push_back("#3P6T200\r\n");
			break;
		case Operation::_R:
			vecStrSerial.push_back("#3P7T200\r\n");
			break;
		case Operation::R2:
			vecStrSerial.push_back("#3P8T200\r\n");
			break;
		case Operation::RightLoose:
			vecStrSerial.push_back("#4P0T200\r\n");
			break;
		case Operation::RightTight:
			vecStrSerial.push_back("#4P1T200\r\n");
			break;
		}
	}
}

void CubeExplorer::PrintSerial() {
	for (auto iter = vecStrSerial.cbegin(); iter != vecStrSerial.cend(); iter++) {
		cout << *iter << "  ";
	}
}

void CubeExplorer::Reset() {
	handState = HandState(true, true, true, true);
	strNorVec.clear();
	macVec.clear();
	vecStrSerial.clear();
}

ostream& operator<<(ostream& os, const Operation& oper) {
	switch (oper) {
	case Operation::F:
		os << "F";
		break;
	case Operation::F2:
		os << "F2";
		break;
	case Operation::LeftLoose:
		os << "LeftLoose";
		break;
	case Operation::LeftTight:
		os << "LeftTight";
		break;
	case Operation::R:
		os << "R";
		break;
	case Operation::R2:
		os << "R2";
		break;
	case Operation::RightLoose:
		os << "RightLoose";
		break;
	case Operation::RightTight:
		os << "RightTight";
		break;
	case Operation::_F:
		os << "_F";
		break;
	case Operation::_R:
		os << "_R";
		break;
	}
	return os;
}
