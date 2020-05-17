#pragma once
#include "ogrsf_frmts.h"
#include <vector>

class MultiPoints
{
	std::vector<OGRMultiPoint*> multiPoints;

public:
	//konstruktory
	MultiPoints() {}

	MultiPoints(OGRMultiPoint* _poPoint)
	{
		multiPoints.push_back(_poPoint);
	}

	//destruktor
	virtual ~MultiPoints() {};

	//settery
	virtual void addGeometry(OGRGeometry* _geometry);

	//gettery
	virtual std::vector<OGRMultiPoint*> getAllMultiPoints();
	OGRMultiPoint* getMultiPoint(int i);
};

