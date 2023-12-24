#include"CubeExplorer.h"
CubeExplorer::CubeExplorer(char* cstr,const HandState& hs):target(cstr),handState(hs){}

void CubeExplorer::SetTarget(string str) { target = str; }

vector<string>& CubeExplorer::GetVecStrSerial() { return vecStrSerial; }

void CubeExplorer::OnR(vector<string>::iterator& iter) {
	RightTight();											//右爪夹紧
	GetLeftReadyAndTight();									//左爪调整至90/270°且夹紧
	macVec.push_back(Operation::R);							//右爪顺时针转动90°（存储到容器内，之后进行发送）
	handState.right.isReady = !handState.right.isReady;		//设置右爪状态参数

	transCnt++;
}

void CubeExplorer::On_R(vector<string>::iterator& iter) {
	RightTight();
	GetLeftReadyAndTight();
	macVec.push_back(Operation::_R);
	handState.right.isReady = !handState.right.isReady; 

	transCnt++;
}

void CubeExplorer::OnF(vector<string>::iterator& iter) {
	LeftTight();
	GetRightReadyAndTight();
	macVec.push_back(Operation::F);
	handState.left.isReady = !handState.left.isReady;

	transCnt++;
}

void CubeExplorer::On_F(vector<string>::iterator& iter) {
	LeftTight();
	GetRightReadyAndTight();
	macVec.push_back(Operation::_F);
	handState.left.isReady = !handState.left.isReady;

	transCnt++;
}

void CubeExplorer::OnRR(vector<string>::iterator& iter) {
	RightTight();											//右爪夹紧
	LeftLoose();											//左爪松开
	LeftReady();											//左爪转动至90/270°状态
	macVec.push_back(Operation::R);							//右爪顺时针转动90°
	handState.right.isReady = !handState.right.isReady;		//设置右爪状态参数
	for (auto it = iter + 1; it != strNorVec.end(); it++) {	//由于魔方整体转动后，面的定义发生变化，
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

void CubeExplorer::On_RR(vector<string>::iterator& iter) {
	RightTight();
	LeftLoose();
	LeftReady();
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

void CubeExplorer::OnFF(vector<string>::iterator& iter) {
	LeftTight();
	RightLoose();
	RightReady();
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

void CubeExplorer::On_FF(vector<string>::iterator& iter) {
	LeftTight();
	RightLoose();
	RightReady();
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

void CubeExplorer::OnRR2(vector<string>::iterator& iter) {
	RightTight();
	LeftLoose();
	LeftReady();
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

void CubeExplorer::OnFF2(vector<string>::iterator& iter) {
	LeftTight();
	RightLoose();
	RightReady();
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

void CubeExplorer::OnR2(vector<string>::iterator& iter) {
	RightTight();
	GetLeftReadyAndTight();
	macVec.push_back(Operation::R2);

	transCnt++;
}

void CubeExplorer::OnF2(vector<string>::iterator& iter) {
	LeftTight();
	GetRightReadyAndTight();
	macVec.push_back(Operation::F2);

	transCnt++;
}

void CubeExplorer::LeftLoose() {
	if (handState.left.isTight) {
		macVec.push_back(Operation::LeftLoose);
		handState.left.isTight = false;
	}
}

void CubeExplorer::LeftTight() {
	if (!handState.left.isTight) {
		if ((!handState.right.isReady) && (!handState.left.isReady)) {
			macVec.push_back(Operation::F);
		}
		macVec.push_back(Operation::LeftTight);
		handState.left.isTight = true;
	}
}

void CubeExplorer::LeftReady() {
	if (!handState.left.isReady) {
		macVec.push_back(Operation::F);
		handState.left.isReady = true;
	}
}

void CubeExplorer::RightLoose() {
	if (handState.right.isTight) {
		macVec.push_back(Operation::RightLoose);
		handState.right.isTight = false;
	}
}

void CubeExplorer::RightTight() {
	if (!handState.right.isTight) {
		if ((!handState.right.isReady) && (!handState.left.isReady)) {
			macVec.push_back(Operation::R);
		}
		macVec.push_back(Operation::RightTight);
		handState.right.isTight = true;
	}
}

void CubeExplorer::RightReady() {
	if (!handState.right.isReady) {
		macVec.push_back(Operation::R);
		handState.right.isReady = true;
	}
}

void CubeExplorer::GetLeftReadyAndTight() {
	if (handState.left.isReady) {
		if (!handState.left.isTight) {
			macVec.push_back(Operation::LeftTight);
			handState.left.isTight = true;
		}
	}
	else {
		if (handState.left.isTight) {
			macVec.push_back(Operation::LeftLoose);
			macVec.push_back(Operation::F);
			macVec.push_back(Operation::LeftTight);
		}
		else {
			macVec.push_back(Operation::F);
			macVec.push_back(Operation::LeftTight);
			handState.left.isTight = true;
		}
		handState.left.isReady = true;
	}
}

void CubeExplorer::GetRightReadyAndTight() {
	if (handState.right.isReady) {
		if (!handState.right.isTight) {
			macVec.push_back(Operation::RightTight);
			handState.right.isTight = true;
		}
	}
	else {
		if (handState.right.isTight) {
			macVec.push_back(Operation::RightLoose);
			macVec.push_back(Operation::R);
			macVec.push_back(Operation::RightTight);
		}
		else {
			macVec.push_back(Operation::R);
			macVec.push_back(Operation::RightTight);
			handState.right.isTight = true;
		}
		handState.right.isReady = true;
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
		if (*iter == "R") OnR(iter);				//F和R面系列操作，无需魔方的整体转动就可以直接操作
		else if (*iter == "F") OnF(iter);			//
		else if (*iter == "R'") On_R(iter);			//
		else if (*iter == "F'") On_F(iter);			//
		else if (*iter == "R2") OnR2(iter);			//
		else if (*iter == "F2") OnF2(iter);			//
		else if (*iter == "B") {
			OnRR2(iter);							//通用公式“B“，首先要魔方整体沿R方向旋转180°
			OnF(iter);								//此时原来的B面成为F面，F面顺时针转动90°即可完成操作
		}
		else if (*iter == "L") {
			OnFF2(iter);
			OnR(iter);
		}
		else if (*iter == "U") {
			if (STRATEGY == 1) {
				OnFF(iter);
				OnR(iter);
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
						OnFF(iter);
						OnR(iter);
					}
					else {
						//若左手处于90/270°状态而右手处于0/180°状态，那么对于当前操作，策略2比策略1少4个机械爪指令
						//若当前操作其后紧跟的那个操作不是对F、B面的操作，那么策略2得到的机械爪指令不大于策略1
						//（当紧跟的是R、L面操作时，策略2比策略1少4个指令；当紧跟的是D面操作时，两个策略等效），因此采用策略2
						On_RR(iter);
						OnF(iter);
					}
				}
				else {
					//若左手处于0/180°状态，对于当前操作，策略1比策略2少4个指令
					//其后紧跟的指令，若为L、R面操作，则策略1比策略2少4个指令，这两个因素相互抵消；若为F、B面操作，策略1比策略2少4个指令
					//只要左手处于这个状态，就选择策略1
					OnFF(iter);
					OnR(iter);
				}
			}
			
			
		}
		else if (*iter == "D") {
			if (STRATEGY == 1) {
				OnRR(iter);
				OnF(iter);
			}
			else {
				if (handState.left.isReady) {
					if (handState.right.isReady &&
						(iter + 1 != strNorVec.end()) &&
						(*(iter + 1) == "F" || *(iter + 1) == "F'" || *(iter + 1) == "F2" || *(iter + 1) == "B" || *(iter + 1) == "B'" || *(iter + 1) == "B2")) {
						On_FF(iter);
						OnR(iter);
					}
					else {
						OnRR(iter);
						OnF(iter);
					}
				}
				else {
					On_FF(iter);
					OnR(iter);
				}
			}
		}
		else if (*iter == "B'") {
			OnRR2(iter);
			On_F(iter);
		}
		else if (*iter == "L'") {
			OnFF2(iter);
			On_R(iter);
		}
		else if (*iter == "U'") {
			if (STRATEGY == 1) {
				OnFF(iter);
				On_R(iter);
			}
			else {
				if (handState.left.isReady) {
					if (handState.right.isReady &&
						(iter + 1 != strNorVec.end()) &&
						(*(iter + 1) == "F" || *(iter + 1) == "F'" || *(iter + 1) == "F2" || *(iter + 1) == "B" || *(iter + 1) == "B'" || *(iter + 1) == "B2")) {
						OnFF(iter);
						On_R(iter);
					}
					else {
						On_RR(iter);
						On_F(iter);
					}
				}
				else {
					OnFF(iter);
					On_R(iter);
				}
			}
		}
		else if (*iter == "D'") {
			if (STRATEGY == 1) {
				OnRR(iter);
				On_F(iter);
			}
			else {
				if (handState.left.isReady) {
					if (handState.right.isReady &&
						(iter + 1 != strNorVec.end()) &&
						(*(iter + 1) == "F" || *(iter + 1) == "F'" || *(iter + 1) == "F2" || *(iter + 1) == "B" || *(iter + 1) == "B'" || *(iter + 1) == "B2")) {
						On_FF(iter);
						On_R(iter);
					}
					else {
						OnRR(iter);
						On_F(iter);
					}
				}
				else {
					On_FF(iter);
					On_R(iter);
				}
			}
		}
		else if (*iter == "B2") {
			OnRR2(iter);
			OnF2(iter);
		}
		else if (*iter == "L2") {
			OnFF2(iter);
			OnR2(iter);
		}
		else if (*iter == "U2") {
			if (STRATEGY == 1) {
				OnFF(iter);
				OnR2(iter);
			}
			else {
				if (handState.left.isReady) {
					if (handState.right.isReady &&
						(iter + 1 != strNorVec.end()) &&
						(*(iter + 1) == "F" || *(iter + 1) == "F'" || *(iter + 1) == "F2" || *(iter + 1) == "B" || *(iter + 1) == "B'" || *(iter + 1) == "B2")) {
						OnFF(iter);
						OnR2(iter);
					}
					else {
						On_RR(iter);
						OnF2(iter);
					}
				}
				else {
					OnFF(iter);
					OnR2(iter);
				}
			}
		}
		else if (*iter == "D2") {
			if (STRATEGY == 1) {
				OnRR(iter);
				OnF2(iter);
			}
			else {
				if (handState.left.isReady) {
					if (handState.right.isReady &&
						(iter + 1 != strNorVec.end()) &&
						(*(iter + 1) == "F" || *(iter + 1) == "F'" || *(iter + 1) == "F2" || *(iter + 1) == "B" || *(iter + 1) == "B'" || *(iter + 1) == "B2")) {
						On_FF(iter);
						OnR2(iter);
					}
					else {
						OnRR(iter);
						OnF2(iter);
					}
				}
				else {
					On_FF(iter);
					OnR2(iter);
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
	cout << endl;
	cout << "Final operations' count: " << cnt << endl;
	cout << "All operations' count: " << macVec.size() << endl;
	cout << endl;
}

int CubeExplorer::GetOperationTime() {
	int time = 0;
	for (auto iter = macVec.cbegin(); iter != macVec.cend(); iter++) {
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
