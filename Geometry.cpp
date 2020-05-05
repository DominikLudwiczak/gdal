#include "Geometry.h"
//settery
void Geometry::addGeometry(OGRGeometry* _geometry)
{
	geometry.push_back(_geometry);
}

//gettery
std::vector<OGRGeometry*> Geometry::getAllGeometry()
{
	return geometry;
}

//prze³adowanie operatora indeksowania
OGRGeometry*& Geometry::operator[](int i)
{
	return geometry[i];
}