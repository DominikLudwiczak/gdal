#include <iostream>
#include "funkcje.h"
#include "Points.h"
#include "MultiPoints.h"

int main()
{
	Points* points = new Points();
	MultiPoints* multiPoints = new MultiPoints();

	std::vector<OGRGeometry*> geometry = read("dane/punkty/point_test.shp", "point_test", "id");
	division(*points, *multiPoints, geometry);

	std::cout << std::endl;

	std::vector<OGRPoint*> point = points->getAllPoints();
	for (auto row : point)
		std::cout << row->getX() << " | " << row->getY() << std::endl;

	//sprawdzenie czy geometrie dopisuj¹ siê do jednego obiektu

	geometry = read("dane/punkty/point_test.shp", "point_test", "id");
	division(*points, *multiPoints, geometry);

	std::cout << std::endl;

	point = points->getAllPoints();
	for (auto row : point)
		std::cout << row->getX() << " | " << row->getY() << std::endl;
	
	//write("dane/multipunkty/write/multipunkty_write.shp", "multipunkty_write", "id", points, "multipoints");

	return 0;
}	