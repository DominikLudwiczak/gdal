#pragma once
#include "ogrsf_frmts.h"
#include <vector>
class Geometry
{
public:
	//settery
	virtual void addGeometry(OGRGeometry* _geometry) = 0;

	//gettery
	virtual std::vector<OGRPoint*>getAllPoints() = 0;

	//prze³adowanie operatora indeksowania
	//virtual OGRGeometry*& operator[](int i) = 0;
};