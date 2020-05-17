#include "MultiPoints.h"
#include <iostream>
//settery
void MultiPoints::addGeometry(OGRGeometry* _geometry)
{
	printf("%d", _geometry->getGeometryType());
	OGRMultiPoint* poMultipoint = (OGRMultiPoint*)_geometry;
	int NumberOfGeometries = poMultipoint->getNumGeometries();
	multiPoints.push_back(poMultipoint);
}

//gettery
std::vector<OGRMultiPoint*> MultiPoints::getAllMultiPoints()
{
	return multiPoints;
}

OGRMultiPoint* MultiPoints::getMultiPoint(int i) {
	int x = 0;
	for (auto obj : this->multiPoints) {
		if (x == i) {
			return obj;
		}
		x++;
	}
}