#include "Points.h"
//settery
void Points::addPoint(OGRPoint* _point)
{
	points.push_back(_point);
}

void Points::deletePoints(double _x, double _y)
{
	std::vector<OGRPoint*> occurrence;
	std::vector<OGRPoint*>::iterator it = occurrence.begin();
	while (it != occurrence.end())
	{
		occurrence.erase(it);
		it++;
	}
}

//gettery
std::vector<OGRPoint*> Points::getAllPoints()
{
	return points;
}