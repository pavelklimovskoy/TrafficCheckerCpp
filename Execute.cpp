//
//

#include "Execute.h"
#include <algorithm>

//Функция сортировки агентов по расстоянию
vector<int> Sorting(const vector<Agent> &aList, const vector<int> &v, int i)
{
	vector<pair<double, int>> lengths;

	for (size_t j = 0; j < v.size(); j++)
	{
		if (aList[v[j]]._roads.size())
		{
			double len = sqrt(pow((aList[i]._roads[0]._p1._x - aList[v[j]]._roads[0]._p0._x), 2) + pow((aList[i]._roads[0]._p1._y - aList[v[j]]._roads[0]._p0._y), 2));
			lengths.push_back(make_pair(len, aList[v[j]]._id));// длина - id
		}
		else
		{
			double x0 = aList[v[j]]._x;
			double y0 = aList[v[j]]._y;
			double len = sqrt(pow((aList[i]._roads[0]._p1._x - x0), 2) + pow((aList[i]._roads[0]._p1._y - y0), 2));
			lengths.push_back(make_pair(len, aList[v[j]]._id));// длина - id
		}
	}

	sort(lengths.begin(), lengths.end());

	vector<int> res;
	for (size_t k = 0; k < lengths.size(); k++)
	{
		res.push_back(lengths[k].second);
	}
	return res;
}

//Функция запуска
void Execute(vector<Agent> &aList)
{
	//Перебор для проверки пересечения отрезков
	ofstream fout("Output/output.txt");

	vector<pair<int, vector<int>>> interList;

	vector<pair<pair<int, vector<int>>, int>> type1; // По траектории
	vector<pair<pair<int, vector<int>>, int>> type2; // По радиусу и обычное пересечение
	vector<pair<pair<int, vector<int>>, int>> type3; // По треугольнику агент-дорога

	for (size_t i = 0; i < aList.size(); i++)
	{
		for (size_t k = 0; k < aList[i]._roads.size(); k++)
		{
			vector<int> tempout1;
			for (size_t j = 0; j < aList.size(); j++)
			{
				for (size_t f = 0; f < aList[j]._roads.size(); f++)
				{
					if (i != j)
					{
						Seqment s1 = Seqment(aList[i]._roads[k]._p0, aList[i]._roads[k]._p1);
						Seqment s2 = Seqment(aList[j]._roads[f]._p0, aList[j]._roads[f]._p1);

						bool IsAnglesEqual = false;
						IsAnglesEqual = ((aList[i]._roads[k]._ang == aList[j]._roads[f]._ang));

						if (Checker::IsOnTrajectory(s1, s2) && IsAnglesEqual)
						{
							tempout1.push_back(aList[j]._id);
						}
					}
				}
			}

			//D
			tempout1.erase(unique(tempout1.begin(), tempout1.end()), tempout1.end());

			if (tempout1.size())
			{
				type1.push_back(make_pair(make_pair(aList[i]._id, tempout1), aList[i]._roads[k]._idr));
				type1.back().first.second = Sorting(aList, type1.back().first.second, aList[i]._id);
			}
		}
	}


	//Вывод 1 тип
	fout << "On Trajectory:" << endl;
	for (size_t i = 0; i < type1.size(); i++)
	{
		fout << 'A' << type1[i].first.first + 1 << " : A" << type1[i].first.second[0] + 1 << " by R" << type1[i].second + 1 << endl;
	}
	fout << "-------------------------------------------------" << endl;

	//Перебор для проверки фактического персечения(2 тип)
	for (size_t i = 0; i < aList.size(); i++)
	{
		for (size_t k = 0; k < aList[i]._roads.size(); k++)
		{
			vector<int> tmpout2;
			for (size_t j = 0; j < aList.size(); j++)
			{
				for (size_t f = 0; f < aList[j]._roads.size(); f++)
				{
					if (i != j)
					{
						Seqment s1 = Seqment(aList[i]._roads[k]._p0, aList[i]._roads[k]._p1);
						Seqment s2 = Seqment(aList[j]._roads[f]._p0, aList[j]._roads[f]._p1);

						if(Checker::IsCrossing(s1, s2) || Checker::InSamePoint(s1,s2))
						{
							tmpout2.push_back(aList[j]._id);
						}
					}
				}
			}
			//D
			tmpout2.erase(unique(tmpout2.begin(), tmpout2.end()), tmpout2.end());

			if (tmpout2.size())
			{
				type2.push_back(make_pair(make_pair(aList[i]._id, tmpout2), aList[i]._roads[k]._idr));
			}
		}
	}

	//Вывод 2 тип
	for (size_t i = 0; i < type2.size(); i++)
	{
		for (size_t j = 0; j < type2.size(); j++)
		{
			if ((i != j) && (type2[i].first.first == type2[j].first.first) && (type2[i].second == type2[j].second))
			{
				for (size_t k = 0; k < type2[j].first.second.size(); k++)
				{
					type2[i].first.second.push_back(type2[j].first.second[k]);
				}

				type2.erase(type2.begin() + j);
			}
		}
	}

	fout << "Factical crossing:" << endl;
	for (size_t i = 0; i < type2.size(); i++)
	{
		fout << 'A' << type2[i].first.first + 1 << " : {";
		for (size_t j = 0; j < type2[i].first.second.size(); j++)
		{
			if (j != type2[i].first.second.size() - 1)
			{
				fout << 'A' << type2[i].first.second[j] + 1 << ", ";
			}
			else fout << 'A' << type2[i].first.second[j] + 1;
		}
		fout << '}' << " by R" << type2[i].second + 1 << endl;
	}
	fout << "-------------------------------------------------" << endl;

	//Перебор для проверки пересечения отрезка с агентом(тип 3)
	for (size_t i = 0; i < aList.size(); i++)
	{
		for (size_t k = 0; k < aList[i]._roads.size(); k++)
		{
			vector<int> tmpout3;
			for (size_t j = 0; j < aList.size(); j++)
			{
				if (i != j && aList[j]._roads.size() == 0)
				{
					Seqment s = aList[i]._roads[k];
					if (Checker::IsAgentRoadMatch(s, aList[j]))
					{
						tmpout3.push_back(aList[j]._id);
					}
				}
			}
			//D
			tmpout3.erase(unique(tmpout3.begin(), tmpout3.end()), tmpout3.end());

			if (tmpout3.size())
			{
				type3.push_back(make_pair(make_pair(aList[i]._id, tmpout3), aList[i]._roads[k]._idr));
			}
		}
	}

	//Вывод 3 тип
	for (size_t i = 0; i < type3.size(); i++)
	{
		for (size_t j = 0; j < type3.size(); j++)
		{
			if ((i != j) && (type3[i].first.first == type3[j].first.first) && (type3[i].second == type3[j].second))
			{
				for (size_t k = 0; k < type3[j].first.second.size(); k++)
				{
					type3[i].first.second.push_back(type3[j].first.second[k]);
				}

				type3.erase(type3.begin() + j);
			}
		}
	}

	fout << "Agent-Road crossing:" << endl;
	for (size_t i = 0; i < type3.size(); i++)
	{
		fout << 'A' << type3[i].first.first + 1 << " : {";
		for (size_t j = 0; j < type3[i].first.second.size(); j++)
		{
			if (j != type3[i].first.second.size() - 1)
			{
				fout << 'A' << type3[i].first.second[j] + 1 << ", ";
			}
			else fout << 'A' << type3[i].first.second[j] + 1;
		}
		fout << '}' <<" by R"<< type3[i].second + 1 << endl;
	}

	fout.close();
}