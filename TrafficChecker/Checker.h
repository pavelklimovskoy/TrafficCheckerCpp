#pragma once
//
//

#include "Agent.h"

//  ласс с методами проверки агентов
class Checker
{
public:
	// ѕроверка пересечени€
	static bool IsCrossing(Seqment s1, Seqment s2);

	// ѕроверка принадлежности одной траектории двух отрезков
	static bool IsOnTrajectory(Seqment s1, Seqment s2);

	// ѕроверка принадлежности одной траектории агента и отрезка
	static bool IsOnTrajectoryAgent(Seqment s1, Agent a);

	// ѕроверка пересечени€ концов отрезка
	static bool IsMatch(Seqment s1, Seqment s2);

	// ѕроверка пересечени€ отрезка с радиусом агента
	static bool IsAgentRoadMatch(Seqment s, Agent a);

	// ѕроверка взаимодействи€ агента с агентом
	static bool IsAgentAgentMatch(Agent a, Agent b);
};