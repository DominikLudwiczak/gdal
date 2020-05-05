#pragma once
#include "ogrsf_frmts.h"
#include <vector>
#include "Geometry.h"
class Points : public Geometry
{
	std::vector<OGRPoint*> points;

public:
	//konstruktory
	Points() : Geometry() {}

	Points(OGRPoint* _poPoint)
	{
		points.push_back(_poPoint);
	}

	//destruktor
	virtual ~Points() {};

	//settery
	void addPoint(OGRPoint* _point);
	void deletePoints(double _x, double _y);

	//gettery
	std::vector<OGRPoint*> getAllPoints();
};

