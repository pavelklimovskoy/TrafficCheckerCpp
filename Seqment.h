#pragma once
//
//

#include "Point.h"

// �������������� �������
class Seqment
{
public:
	Point _p0;
	Point _p1;
	double _ang;
	int _idr;

	// ������ �����������
	Seqment();

	// ����������� �� ���� �����
	Seqment(Point p0, Point p1);

	// ����������� �� ������ ���������
	Seqment(double x1, double y1, double x2, double y2, double rad1, double rad2);
};