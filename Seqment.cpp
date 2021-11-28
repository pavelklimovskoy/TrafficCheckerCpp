//
//

#include "Seqment.h"

// Пустой конструктор
Seqment::Seqment()
{
	_p0 = Point();
	_p1 = Point();
	_ang = 0;
	_idr = -1;
}

// Конустрктор от двух точек
Seqment::Seqment(Point p0, Point p1)
{
	_p0 = p0;
	_p1 = p1;
	_ang = -1;
	_idr = -1;
}


// Конструктор от четырёх координат
Seqment::Seqment(double x1, double y1, double x2, double y2, double rad1, double rad2)
{
	_p0 = Point(x1, y1, rad1);
	_p1 = Point(x2, y2, rad2);
	_ang = -1;
	_idr = -1;
}

//Seqment::Seqment(Point p, Agent a)
//{
//	_p0 = Point(p._x, p._y, p._rad);
//	_p1 = Point(a._x, a._y, a._r);
//	_ang = -1;
//}

