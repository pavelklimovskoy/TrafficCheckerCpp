#include "Point.h"

// Пустой конструктор
Point::Point()
{
	_x = 0;
	_y = 0;
	_rad = -1;
}

// Конструктор от координат
Point::Point(double x, double y, double rad)
{
	_x = x;
	_y = y;
	_rad = rad;
}

std::istream& operator>> (std::istream& in, Point& point)
{
	in >> point._x;
	in >> point._y;
	in >> point._rad;

	return in;
}