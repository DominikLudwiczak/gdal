#include <iostream>
#include "funkcje.h"

int main()
{
	//read("dane/punkty/point_test.shp", "point_test", "id");

	read("dane/multipunkty/multipoint_test.shp", "multipoint_test", "id");

	std::cout << std::endl;
	
	//readMultiPointShapeFile("dane/multipunkty/multipoint_test.shp", "multipoint_test", "id");

	std::vector<std::vector<double>> points;
	std::vector<double>punkt;
	punkt.push_back(1.69);
	punkt.push_back(0.56);
	points.push_back(punkt);
	punkt.clear();
	punkt.push_back(3.78);
	punkt.push_back(0.98);
	points.push_back(punkt);
	punkt.clear();
	//writePointShapeFile("dane/punkty/write/punkty_write.shp", "punkty_write", "id", points);

	writeMultiPointShapeFile("dane/multipunkty/write/multipunkty_write.shp", "multipunkty_write", "id", points);

	return 0;
}