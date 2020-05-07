#include <iostream>
#include "funkcje.h"
#include "Geometry.h"
#include "Points.h"

int main()
{
	std::vector<OGRGeometry*> geometry = read("dane/punkty/point_test.shp", "point_test", "id");
	
	Geometry* geom;

	if (wkbFlatten(geometry.at(0)->getGeometryType()) == wkbPoint)
	{
		geom = new Points();
		for (auto row : geometry)
			geom->addGeometry(row);
	}
	else
		geom = new Points();

	std::vector<OGRPoint*> points = geom->getAllPoints();
	std::cout << std::endl;
	for (auto row : points)
		std::cout << row->getX() << " | " << row->getY() << std::endl;
	geometry.clear();


	//write("dane/multipunkty/write/multipunkty_write.shp", "multipunkty_write", "id", points, "multipoints");

	return 0;
}	