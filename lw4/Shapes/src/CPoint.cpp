#include "CPoint.h"

double GetLineLength(CPoint startPoint, CPoint endPoint)
{
	return std::hypot((endPoint.x - startPoint.x), (endPoint.y - startPoint.y));
}