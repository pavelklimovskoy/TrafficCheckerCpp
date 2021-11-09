//
//

#include "Agent.h"
using namespace std;

// Агент с его маршрутами
Agent::Agent()
{
	_id = -1;
	_x = 0;
	_y = 0;
	_r = 0;
	_roads.clear();
}

Agent::Agent(int id, double x, double y, double rad)
{
	_id = id;
	_x = x;
	_y = y;
	_r = rad;
	_roads.clear();
}

Agent::Agent(int id, Point point)
{
	_id = id;
	_x = point._x;
	_y = point._y;
	_r = point._rad;
	_roads.clear();
}

void Agent::Show()
{
	cout << "Agent id : " << _id << endl;
	if (_roads.empty())
	{
		cout << "  " << "x0: " << _x << " y0: " << _y << endl;
		cout << "  " << "R: "  << _r << endl;
	}
	else
	{
		for (size_t i = 0; i < _roads.size(); i++)
		{
			cout << "  "   << "Road id : " << i << endl;
			cout << "    " << "x0: "	   << _roads[i]._p0._x	 << " y0: " << _roads[i]._p0._y << endl;
			cout << "    " << "R start : " << _roads[i]._p0._rad << endl;
			cout << "    " << "x1: "	   << _roads[i]._p1._x   << " y1: " << _roads[i]._p1._y << endl;
			cout << "    " << "R end : "   << _roads[i]._p1._rad << endl;
			cout << "    " << "Angle : "   << _roads[i]._ang    << endl;
		}
	}
	cout << endl;
}
