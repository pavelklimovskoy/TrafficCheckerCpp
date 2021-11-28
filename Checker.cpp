//
//

#include "Checker.h"

// ѕроверка пересечени€
bool Checker::IsCrossing(Seqment s1, Seqment s2)
{
	bool flag = false;

	double v1 = (s2._p1._x - s2._p0._x) * (s1._p0._y - s2._p0._y) - (s2._p1._y - s2._p0._y) * (s1._p0._x - s2._p0._x);
	double v2 = (s2._p1._x - s2._p0._x) * (s1._p1._y - s2._p0._y) - (s2._p1._y - s2._p0._y) * (s1._p1._x - s2._p0._x);
	double v3 = (s1._p1._x - s1._p0._x) * (s2._p0._y - s1._p0._y) - (s1._p1._y - s1._p0._y) * (s2._p0._x - s1._p0._x);
	double v4 = (s1._p1._x - s1._p0._x) * (s2._p1._y - s1._p0._y) - (s1._p1._y - s1._p0._y) * (s2._p1._x - s1._p0._x);

	if ((v1 * v2 < 0) * (v3 * v4 < 0))
	{
		flag = true;
	}

	return flag;
}

//ѕроверка концов в одной точке
bool Checker::InSamePoint(Seqment s1, Seqment s2)
{
	bool flag = false;

	if (s1._p1._x == s2._p1._x && s1._p1._y == s2._p1._y)
	{
		flag = true;
	}

	return flag;
}

// ѕроверка принадлежности одной траектории двух отрезков
bool Checker::IsOnTrajectory(Seqment s1, Seqment s2)
{
	bool flag = false;

	double a1 = (s2._p0._x - s1._p0._x) * (s1._p1._y - s1._p0._y);
	double a2 = (s2._p0._y - s1._p0._y) * (s1._p1._x - s1._p0._x);

	double a3 = (s2._p1._x - s1._p0._x) * (s1._p1._y - s1._p0._y);
	double a4 = (s2._p1._y - s1._p0._y) * (s1._p1._x - s1._p0._x);

	if ((abs(a1 - a2) <= 1e-6) || (abs(a3 - a4) <= 1e-6))
	{
		flag = true;
	}

	return flag;
}

// ѕроверка принадлежности одной траектории агента и отрезка
bool Checker::IsOnTrajectoryAgent(Seqment road, Agent agent)
{
	bool flag = false;

	double len1 = sqrt(pow(road._p1._x - road._p0._x, 2) + pow(road._p1._y - road._p0._y, 2));
	double len2 = sqrt(pow(road._p0._x - agent._x, 2) + pow(road._p0._y - agent._y, 2));

	Seqment seqToAgent = Seqment(road._p0, Point(agent._x, agent._y, agent._r));

	double param = sin(arctg(road) - arctg(seqToAgent));

	if (param == 0)
	{
		flag = true;
	}
	return flag;
}

// ѕроверка пересечени€ концов отрезка
bool Checker::IsMatch(Seqment s1, Seqment s2)
{
	bool flag = false;

	double length_between_ends = sqrt(pow((s2._p1._x - s1._p1._x), 2) + pow((s2._p1._y - s1._p1._y), 2));
	
	if ((length_between_ends - abs(s1._p1._rad + s2._p1._rad)) <= 1e-6)
	{
		flag = true;
	}
	return flag;
}


// ѕроверка пересечени€ отрезка с радиусом агента
bool Checker::IsAgentRoadMatch(Seqment s, Agent a)
{
	bool flag = false;

	double rebro1 = sqrt(pow((s._p1._x - s._p0._x), 2) + pow((s._p1._y - s._p0._y), 2));
	double rebro2 = sqrt(pow((s._p1._x - a._x), 2) + pow((s._p1._y - a._y), 2));
	double rebro3 = sqrt(pow((s._p0._x - a._x), 2) + pow((s._p0._y - a._y), 2));
	double polup = (rebro1 + rebro2 + rebro3) / 2;

	double h = 2 * sqrt(polup * (polup - rebro1) * (polup - rebro2) * (polup - rebro3));
	h /= rebro1;

	double length_between_ag_st = -1;
	double length_between_ag_end = -1;

	length_between_ag_st = sqrt(pow((s._p0._x - a._x), 2) + pow((s._p0._y - a._y), 2));
	length_between_ag_end = sqrt(pow((s._p1._x - a._x), 2) + pow((s._p1._y - a._y), 2));
	//if ((abs((h - rebro1 * (a._r))) <= 1e-6) && a._r != 0)
	if ((h - a._r <= 1e-6) && (h != 0))
	{
		flag = true;
	}

	if ((length_between_ag_st != -1 && length_between_ag_st <= (s._p0._rad + a._r)) || (length_between_ag_end != -1 && length_between_ag_end <= (s._p1._rad + a._r)))
	{
		flag = true;
	}
	return flag;
}

// ѕроверка взаимодействи€ агента с агентом
bool Checker::IsAgentAgentMatch(Agent a, Agent b)
{
	bool flag = false;

	double length = sqrt(pow((a._x - b._x), 2) + pow((a._y - b._y), 2));

	if ((length != 0) && (length <= (a._r + b._r)) )
	{
		flag = true;
	}

	return flag;
}