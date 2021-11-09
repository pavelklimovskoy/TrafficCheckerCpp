//
//

#include "Reader.h"

//Класс для чтения данных из файла
vector<Agent> Reader::Read()
{
	vector<Agent> res;

	string pathToFile = "Input/data.txt";
	ifstream fin(pathToFile);

	if (!fin.is_open())
	{
		cout << "File not found" << endl;
		return res;
	}

	size_t k;
	fin >> k;
	for (size_t i = 0; i < k; i++)
	{
		Agent curAgent;
		fin >> curAgent._id;

		size_t n;
		fin >> n;

		if (n == 0)
		{
			fin >> curAgent._x;
			fin >> curAgent._y;
			fin >> curAgent._r;
		}

		for (size_t j = 0; j < n; j++) 
		{
			Point _px, _py;
			fin >> _px >> _py;

			Seqment tSeq(_px, _py);

			curAgent._roads.push_back(tSeq);
			curAgent._roads.back()._ang = arctg(tSeq);
		}

		res.push_back(curAgent);
	}

	fin.close();
	return res;
}
