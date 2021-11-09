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
	ofstream fout("output/output.txt");

	map<int, vector<int>> _mp;
	auto it = _mp.begin();

	for (size_t i = 0; i < aList.size(); i++)
	{
		vector<int> interList;
		for (size_t j = 0; j < aList.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			size_t lim = aList[i]._roads.size();

			// Дорога-дорога
			for (size_t k = 0; k < lim; k++)
			{
				size_t lim2 = aList[j]._roads.size();
				for (size_t f = 0; f < lim2; f++)
				{
					Seqment s1 = Seqment(aList[i]._roads[k]._p0, aList[i]._roads[k]._p1);
					Seqment s2 = Seqment(aList[j]._roads[f]._p0, aList[j]._roads[f]._p1);

					bool IsAnglesEqual = false;
					IsAnglesEqual = ((aList[i]._roads[k]._ang == aList[j]._roads[f]._ang));

					if (Checker::IsMatch(s1, s2) || Checker::IsCrossing(s1, s2))
					{
						fout << "Roads Crossing : " << i << ' ' << j << endl;
					}

					if (Checker::IsOnTrajectory(s1, s2) && IsAnglesEqual)
					{
						interList.push_back(aList[j]._id);
					}
				}
			}

			// Агент-Дорога
			// Проверка что j-ый агент
			bool isAgent = (!aList[i]._roads.empty()) && (aList[j]._roads.empty());
			for (size_t f = 0; (f < lim) && isAgent; f++)
			{
				Seqment curRoad = aList[i]._roads[f];

				if(Checker::IsOnTrajectoryAgent(curRoad, aList[j]))
				{
					interList.push_back(aList[j]._id);
				}
			}
		}
		if (interList.size() && it != _mp.end())
		{
			_mp.insert(make_pair(aList[i]._id, interList));
			it++;
			it->second = Sorting(aList, it->second, aList[i]._id);
		}
	}

	//Результат композиции
	for (auto iter = _mp.begin(); iter != _mp.end(); iter++)
	{
		bool break_flag = false;
		for (size_t i = 0; i < iter->second.size(); i++)
		{
			if (break_flag == true)
			{
				break;
			}

			if (!iter->second.empty())
			{
				fout << "Roads Crossing(composition) : " << iter->first << ' ' << iter->second[i] << endl;
				for (size_t j = 0; j < aList.size(); j++)
				{
					if ((iter->second[i] == aList[j]._id) && (aList[j]._roads.size()))
					{
						break_flag = true;
						break;
					}
				}
			}
		}
	}

	//Перебор для проверки пересечения отрезка с агентом
	for (size_t i = 0; i < aList.size(); i++)
	{
		for (size_t j = 0; j < aList.size(); j++)
		{
			for (size_t k = 0; k < aList[j]._roads.size(); k++)
			{
				if (i != j && aList[i]._roads.size() == 0)
				{
					Seqment s = aList[j]._roads[k];
					if (Checker::IsAgentRoadMatch(s, aList[i]))
					{
						fout << "Agent-Road Crossing : " << i << ' ' << j << endl;
					}
				}
			}
		}
	}

	//Перебор для проверки взаимодействия агентов
	for (size_t i = 0; i < aList.size(); i++)
	{
		for (size_t j = i + 1; j < aList.size(); j++)
		{
			if (Checker::IsAgentAgentMatch(aList[i], aList[j]))
			{
				fout << "Agent-Agent Crossing : " << i << ' ' << j << endl;
			}
		}
	}

	fout.close();
}