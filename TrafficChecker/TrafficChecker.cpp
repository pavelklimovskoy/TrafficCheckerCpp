//
//

#include <iostream>
#include <fstream>
#include <vector>
#include "Reader.h"
#include "Execute.h"
using namespace std;

int main(void)
{
	vector<Agent> agentList = Reader::Read();

#ifdef _DEBUG
	for (auto agent : agentList)
	{
		agent.Show();
	}
#endif

	Execute(agentList);

	return 0;
}