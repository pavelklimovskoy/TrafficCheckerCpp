//
//

#pragma once
#include <iostream>


// Геометрическая точка
class Point
{
public:
	double _x;
	double _y;
	double _rad;

	// Пустой конструктор
	Point();

	// Конструктор от координат
	Point(double x, double y, double rad);

	// Перегрузка оператора ввода
	friend std::istream& operator>> (std::istream& in, Point& point);
};