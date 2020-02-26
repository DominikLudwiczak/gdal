#include <iostream>
#include "funkcje.h"

int main()
{
	readPointShapeFile("dane/punkty/point_test.shp", "point_test");

	//readMultiPointShapeFile("dane/multipunkty/multipoint_test.shp", "multipoint_test", "id");

	writePointShapeFile("dane/punkty/punkty_write.shp", "punkty_write", "id", 1.937, 1);

	return 0;
}