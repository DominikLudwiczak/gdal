#include "Points.h"
#include <iostream>
//settery
void Points::addGeometry(OGRGeometry* _geometry)
{
	#if GDAL_VERSION_NUM >= GDAL_COMPUTE_VERSION(2,3,0)
		OGRPoint* poPoint = _geometry->toPoint();
	#else
		OGRPoint* poPoint = (OGRPoint*)_geometry;
	#endif
	points.push_back(poPoint);
}

//gettery
std::vector<OGRPoint*> Points::getAllPoints()
{
	return points;
}