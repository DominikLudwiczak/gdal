#include "MultiPoints.h"
#include <iostream>
//settery
void MultiPoints::addGeometry(OGRGeometry* _geometry)
{
	OGRMultiPoint* poMultipoint = (OGRMultiPoint*)_geometry;
	int NumberOfGeometries = poMultipoint->getNumGeometries();
	multiPoints.push_back(poMultipoint);
}

void MultiPoints::writeGeometryToShape()
{
	GDALDriver* poDriver;
	poDriver = GetGDALDriverManager()->GetDriverByName("ESRI Shapefile");

	GDALDataset* poDS;
	poDS = poDriver->Create("dane/multipunkty/write/", 0, 0, 0, GDT_Unknown, NULL);

	OGRLayer* poLayer;
	poLayer = poDS->CreateLayer("multipoint_test_write", NULL, wkbMultiPoint, NULL);

	int i = 0;
	while (!feof(stdin) && i < multiPoints.size())
	{
		OGRFeature* poFeature;
		poFeature = OGRFeature::CreateFeature(poLayer->GetLayerDefn());
		poFeature->SetField("field", i);
		poFeature->SetGeometry(multiPoints.at(i));

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