#pragma once
//
//

#include <iostream>
#include <fstream>
#include <vector>
#include "Point.h"
#include "Seqment.h"
#include "Agent.h"
#include "Arctg.h"
using namespace std;

//����� ��� ������ ������ �� �����
class Reader
{
public:
	static vector<Agent> Read();
};
