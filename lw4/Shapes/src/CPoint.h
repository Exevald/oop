#pragma once

#include <cmath>

class CPoint
{
public:
	double x;
	double y;
};

double GetLineLength(CPoint startPoint, CPoint endPoint);