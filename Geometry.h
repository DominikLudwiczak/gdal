#pragma once
#include "ogrsf_frmts.h"
#include <vector>
class Geometry
{
	std::vector<OGRGeometry*> geometry;
public:
	//konstruktory
	Geometry() {}

	Geometry(OGRGeometry* _geometry)
	{
		geometry.push_back(_geometry);
	}

	//destruktor
	virtual ~Geometry() {}

	//settery
	void addGeometry(OGRGeometry* _geometry);

	//gettery
	std::vector<OGRGeometry*>getAllGeometry();

	//prze³adowanie operatora indeksowania
	OGRGeometry*& operator[](int i);
};