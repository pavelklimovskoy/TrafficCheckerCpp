#pragma once
//
//

#include "Agent.h"

// ����� � �������� �������� �������
class Checker
{
public:
	// �������� �����������
	static bool IsCrossing(Seqment s1, Seqment s2);

	// �������� �������������� ����� ���������� ���� ��������
	static bool IsOnTrajectory(Seqment s1, Seqment s2);

	// �������� �������������� ����� ���������� ������ � �������
	static bool IsOnTrajectoryAgent(Seqment s1, Agent a);

	// �������� ����������� ������ �������
	static bool IsMatch(Seqment s1, Seqment s2);

	// �������� ����������� ������� � �������� ������
	static bool IsAgentRoadMatch(Seqment s, Agent a);

	// �������� �������������� ������ � �������
	static bool IsAgentAgentMatch(Agent a, Agent b);
};