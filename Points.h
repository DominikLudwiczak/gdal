#pragma once
#include "ogrsf_frmts.h"
#include <vector>
#include "Geometry.h"
class Points : public Geometry
{
	std::vector<OGRPoint*> points;

public:
	//konstruktory
	Points(){}

	Points(OGRPoint* _poPoint)
	{
		points.push_back(_poPoint);
	}

	//destruktor
	virtual ~Points() {};

	//settery
	virtual void addGeometry(OGRGeometry* _geometry);

	//gettery
	virtual std::vector<OGRPoint*> getAllPoints();

	//operator prze³adowania indeksuj¹cego[]
	OGRPoint* operator[](int i);

};