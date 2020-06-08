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

void Points::writeGeometryToShape()
{
	GDALDriver* poDriver;
	poDriver = GetGDALDriverManager()->GetDriverByName("ESRI Shapefile");

	GDALDataset* poDS;
	poDS = poDriver->Create("dane/punkty/write/", 0, 0, 0, GDT_Unknown, NULL);

	OGRLayer* poLayer;
	poLayer = poDS->CreateLayer("point_test_write", NULL, wkbPoint, NULL);

	int i = 0;
	while (i < points.size())
	{
		OGRFeature* poFeature;
		poFeature = OGRFeature::CreateFeature(poLayer->GetLayerDefn());
		poFeature->SetField("field", i);
		poFeature->SetGeometry(points.at(i));

		if (poLayer->CreateFeature(poFeature) != OGRERR_NONE)
		{
			printf("Failed to create feature in shapefile.\n");
			exit(1);
		}
		OGRFeature::DestroyFeature(poFeature);
		i++;
	}
}

//gettery
std::vector<OGRPoint*> Points::getAllPoints()
{
	return points;
}

OGRPoint* Points::getPoint(int i) {
	int x = 0;
	for (auto obj : this->points) {
		if (x == i) {
			return obj;
		}
		x++;
	}
}