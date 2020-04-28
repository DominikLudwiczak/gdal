#pragma once
#include "ogrsf_frmts.h"
#include <vector>
class Points
{
	std::vector<OGRPoint*> points;

public:
	//konstruktory
	Points() = default;
	Points(OGRPoint* _poPoint)
	{
		points.push_back(_poPoint);
	}

	//settery
	void addPoint(OGRPoint* _point);
	void deletePoints(double _x, double _y);

	//gettery
	std::vector<OGRPoint*> getAllPoints();
	std::vector<OGRPoint*> getPoints(double _x, double _y);
	OGRPoint* getPoint(double _x, double _y);
};

