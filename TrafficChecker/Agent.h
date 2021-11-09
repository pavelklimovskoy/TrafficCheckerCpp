#pragma once
//
//

#include <iostream>
#include <vector>
#include "Point.h"
#include "Seqment.h"
#include "Arctg.h"
using namespace std;

// Агент с его маршрутами
struct Agent
{
	int _id;
	double _x;
	double _y;
	double _r;
	vector<Seqment> _roads;

	Agent();

	Agent(int id, double x, double y, double rad);

	Agent(int id, Point point);

	void Show();
};