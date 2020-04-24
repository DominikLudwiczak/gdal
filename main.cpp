#include <iostream>
#include "funkcje.h"

int main()
{
	//std::vector<std::vector<double>> punkty = read("dane/punkty/point_test.shp", "point_test", "id");
	//std::vector<std::vector<double>> punkty = read("dane/multipunkty/multipoint_test.shp", "multipoint_test", "id");
	std::vector<std::vector<double>> punkty = read("dane/linie/linie_test.shp", "linie_test", "id");
	//std::vector<std::vector<double>> punkty = read("dane/multilinie/multilinie_test.shp", "multilinie_test", "id");

	std::cout << std::endl << std::endl;
	for (auto row : punkty)
	{
		for (auto wiersz : row)
			std::cout << wiersz << " ";
		std::cout << std::endl;
	}

	std::cout << std::endl;

	std::vector<std::vector<double>> points;
	std::vector<double>punkt;
	punkt.push_back(1.69);
	punkt.push_back(0.56);
	points.push_back(punkt);
	punkt.clear();
	punkt.push_back(2.69);
	punkt.push_back(-1.56);
	points.push_back(punkt);
	punkt.clear();
	punkt.push_back(1.69);
	punkt.push_back(0.56);
	points.push_back(punkt);
	punkt.clear();

	//write("dane/multipunkty/write/multipunkty_write.shp", "multipunkty_write", "id", points, "multipoints");
	//write("dane/punkty/write/punkty_write.shp", "punkty", "id", points, "points");

	return 0;
}	