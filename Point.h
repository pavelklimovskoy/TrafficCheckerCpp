//
//

#pragma once
#include <iostream>


// �������������� �����
class Point
{
public:
	double _x;
	double _y;
	double _rad;

	// ������ �����������
	Point();

	// ����������� �� ���������
	Point(double x, double y, double rad);

	// ���������� ��������� �����
	friend std::istream& operator>> (std::istream& in, Point& point);
};