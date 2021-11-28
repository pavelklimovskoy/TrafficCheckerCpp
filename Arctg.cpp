//
//

#include "Arctg.h"

//Вычисление угла(направления) отрезка
double arctg(Seqment s)
{
	double alpha = atan2(s._p1._y - s._p0._y, s._p1._x - s._p0._x) * 180.0 / PI;
	return alpha;
}