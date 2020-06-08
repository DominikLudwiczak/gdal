#include <iostream>
#include "funkcje.h"
#include "Points.h"
#include "MultiPoints.h"

#include <winsock.h>
#include "mysql.h"

int main()
{
	Points* points = new Points();
	MultiPoints* multiPoints = new MultiPoints();

	//multipunkty
	std::vector<OGRGeometry*> geometry = read("dane/multipunkty/multipoint_test.shp", "multipoint_test", "id");
	division(*points, *multiPoints, geometry);

	std::cout << std::endl;

	std::vector<OGRMultiPoint*> multiPoint = multiPoints->getAllMultiPoints();
	for (auto row : multiPoint)
	{
		OGRMultiPoint* poMultipoint = (OGRMultiPoint*)row;
		int NumberOfGeometries = poMultipoint->getNumGeometries();
		for (int j = 0; j < NumberOfGeometries; j++)
		{
			OGRGeometry* poPointGeometry = poMultipoint->getGeometryRef(j);
			OGRPoint* poPoint = (OGRPoint*)poPointGeometry;
			std::cout << "Multipoint: " << poPoint->getX() << " | " << poPoint->getY() << std::endl;
		}
	}

	//multiPoints->writeGeometryToShape();

	//punkty
	geometry = read("dane/punkty/point_test.shp", "point_test", "id");
	division(*points, *multiPoints, geometry);

	std::cout << std::endl;

	std::vector<OGRPoint*> point = points->getAllPoints();
	for (auto row : point)
		std::cout << "Point: " << row->getX() << " | " << row->getY() << std::endl;
	
	//points->writeGeometryToShape();

	//connect to database
	/*
	MYSQL* conn;
	MYSQL_RES* res;
	MYSQL_ROW row;
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, "localhost", "root", "", "gdal", 3306, NULL, 0))
		fprintf(stderr, "%s\n", mysql_error(conn));*/

	return 0;
}	