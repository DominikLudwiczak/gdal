#include "funkcje.h"

std::vector<std::vector<double>> read(const  char* name, const  char* layer, const char* field)
{
	std::vector<std::vector<double>> result;
	GDALAllRegister();
	GDALDataset* poDS = static_cast<GDALDataset*>(
		GDALOpenEx(name, GDAL_OF_VECTOR, NULL, NULL, NULL));
	if (poDS == NULL)
	{
		printf("Open failed.\n");
		exit(1);
	}
	OGRLayer* poLayer = poDS->GetLayerByName(layer);
	OGRFeatureDefn* poFDefn = poLayer->GetLayerDefn();
	poLayer->ResetReading();
	OGRFeature* poFeature; 
	OGRFieldDefn oField1(field, OFTInteger64); //typ pola int64 //int string etc -> 32 linia

	std::vector<double> punkt;

	result.clear();
	int i = 0;
	while ((poFeature = poLayer->GetNextFeature()) != NULL)
	{
		for (int iField = 0; iField < poFDefn->GetFieldCount(); iField++)
		{
			OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(iField);
			switch (poFieldDefn->GetType())
			{
			case OFTInteger:
				printf("%d,", poFeature->GetFieldAsInteger(iField));
				break;
			case OFTInteger64:
				printf(CPL_FRMT_GIB ",", poFeature->GetFieldAsInteger64(iField));
				break;
			case OFTReal:
				printf("%.3f,", poFeature->GetFieldAsDouble(iField));
				break;
			case OFTString:
				printf("%s,", poFeature->GetFieldAsString(iField));
				break;
			default:
				printf("%s,", poFeature->GetFieldAsString(iField));
				break;
			}
		}

		OGRGeometry* poGeometry = poFeature->GetGeometryRef();

		if (poGeometry != NULL)
		{
			if (wkbFlatten(poGeometry->getGeometryType()) == wkbPoint) //do punktu
			{
				punkt = readPointShapeFile(poGeometry, poFeature);
				result.push_back(punkt);
				OGRFeature::DestroyFeature(poFeature);
				i++;
			}
			else if (wkbFlatten(poGeometry->getGeometryType()) == wkbMultiPoint) //do multipunktu
			{
				punkt = readMultiPointShapeFile(poGeometry, poFeature);
				result.push_back(punkt);
				OGRFeature::DestroyFeature(poFeature);
				i++;
			}
			else
				printf("no point geometry\n");
		}
		else
			printf("NULL\n");

		punkt.clear();
	}
	GDALClose(poDS);
	return result;
}



std::vector<double> readPointShapeFile(OGRGeometry* poGeometry, OGRFeature* poFeature)
{
	std::vector<double> punkt;

	#if GDAL_VERSION_NUM >= GDAL_COMPUTE_VERSION(2,3,0)
			OGRPoint * poPoint = poGeometry->toPoint();
	#else
			OGRPoint* poPoint = (OGRPoint*)poGeometry;
	#endif

	double x = poPoint->getX();
	double y = poPoint->getY();
	
	printf("%.3f,%3.f\n", x, y);
	punkt.push_back(x);
	punkt.push_back(y);

	return punkt;
}




std::vector<double> readMultiPointShapeFile(OGRGeometry* poGeometry, OGRFeature* poFeature)
{
	std::vector<double> punkt;

	printf("%d", poGeometry->getGeometryType());
	OGRMultiPoint* poMultipoint = (OGRMultiPoint*)poGeometry;
	int NumberOfGeometries = poMultipoint->getNumGeometries();
	for (int j = 0; j < NumberOfGeometries; j++)
	{
		OGRGeometry* poPointGeometry = poMultipoint->getGeometryRef(j);
		OGRPoint* poPoint = (OGRPoint*)poPointGeometry;
		double x = poPoint->getX();
		double y = poPoint->getY();
		punkt.push_back(x);
		punkt.push_back(y);
		printf("%d\n", x, y);
	}

	return punkt;
}




void writePointShapeFile(const char* name, const char* layer, const char* field, std::vector<std::vector<double>> points)
{
	const char* pszDriverName = "ESRI Shapefile";
	GDALDriver* poDriver;

	GDALAllRegister();

	poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName);
	if (poDriver == NULL)
	{
		printf("%s driver not available.\n", pszDriverName);
		exit(1);
	}

	GDALDataset* poDS;

	poDS = poDriver->Create(name, 0, 0, 0, GDT_Unknown, NULL);
	if (poDS == NULL)
	{
		printf("Creation of output file failed.\n");
		exit(1);
	}

	OGRLayer* poLayer;

	poLayer = poDS->CreateLayer(layer, NULL, wkbPoint, NULL);
	if (poLayer == NULL)
	{
		printf("Layer creation failed.\n");
		exit(1);
	}

	OGRFieldDefn oField(field, OFTInteger64);

	oField.SetWidth(10);

	if (poLayer->CreateField(&oField) != OGRERR_NONE)
	{
		printf("Creating Name field failed.\n");
		exit(1);
	}
	char szName[11];
	int i = 0;
	while (!feof(stdin) && i < points.size())
	{
		OGRFeature* poFeature;

		poFeature = OGRFeature::CreateFeature(poLayer->GetLayerDefn());
		poFeature->SetField(field, szName);

		OGRPoint pt;

		pt.setX(points.at(i).at(0));
		pt.setY(points.at(i).at(1));

		poFeature->SetGeometry(&pt);

		if (poLayer->CreateFeature(poFeature) != OGRERR_NONE)
		{
			printf("Failed to create feature in shapefile.\n");
			exit(1);
		}

		OGRFeature::DestroyFeature(poFeature);
		i++;
	}

	GDALClose(poDS);
}

void writeMultiPointShapeFile(const char* name, const char* layer, const char* field, std::vector<std::vector<double>> points)
{
	const char* pszDriverName = "ESRI Shapefile";
	GDALDriver* poDriver;

	GDALAllRegister();

	poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName);
	if (poDriver == NULL)
	{
		printf("%s driver not available.\n", pszDriverName);
		exit(1);
	}

	GDALDataset* poDS;

	poDS = poDriver->Create(name, 0, 0, 0, GDT_Unknown, NULL);
	if (poDS == NULL)
	{
		printf("Creation of output file failed.\n");
		exit(1);
	}

	OGRLayer* poLayer;

	poLayer = poDS->CreateLayer(layer, NULL, wkbMultiPoint, NULL);
	if (poLayer == NULL)
	{
		printf("Layer creation failed.\n");
		exit(1);
	}

	OGRFieldDefn oField(field, OFTInteger64);

	oField.SetWidth(10);

	if (poLayer->CreateField(&oField) != OGRERR_NONE)
	{
		printf("Creating Name field failed.\n");
		exit(1);
	}
	char szName[11];
	int i = 0;
	while (!feof(stdin) && i < points.size()) //tu zrobiæ fora
	{
		OGRFeature* poFeature;

		poFeature = OGRFeature::CreateFeature(poLayer->GetLayerDefn());
		poFeature->SetField(field, szName);

		OGRMultiPoint multi_pt;
		OGRPoint pt;

		pt.setX(points.at(i).at(0));
		pt.setY(points.at(i).at(1));

		multi_pt.addGeometry(&pt);

		poFeature->SetGeometry(&multi_pt);

		if (poLayer->CreateFeature(poFeature) != OGRERR_NONE)
		{
			printf("Failed to create feature in shapefile.\n");
			exit(1);
		}
		OGRFeature::DestroyFeature(poFeature);
		i++;
	}
	GDALClose(poDS);
}

//pocz¹tek funckji która mia³aby zamieniæ dwie powy¿sze procedury
void writePointOrMultiPointShapeFile(const char* name, const char* layer, const char* field, std::vector<std::vector<double>> points, bool check) {
	const char* pszDriverName = "ESRI Shapefile";
	GDALDriver* poDriver;
	GDALAllRegister();
	poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName);
	if (poDriver == NULL) {
		printf("%s driver not available.\n", pszDriverName);
		exit(1);
	}
	GDALDataset* poDS;
	poDS = poDriver->Create(name, 0, 0, 0, GDT_Unknown, NULL);
	if (poDS == NULL)
	{
		printf("Creation of output file failed.\n");
		exit(1);
	}
	OGRLayer* poLayer;
	poLayer = poDS->CreateLayer(layer, NULL, wkbMultiPoint, NULL);
	if (poLayer == NULL) {
		printf("Layer creation failed.\n");
		exit(1);
	}
	OGRFieldDefn oField(field, OFTInteger64);
	oField.SetWidth(10);
	if (poLayer->CreateField(&oField) != OGRERR_NONE) {
		printf("Creating Name field failed.\n");
		exit(1);
	}
	char szName[11];
	int i = 0;
	if (check) {
		while (!feof(stdin) && i < points.size())
		{
			OGRFeature* poFeature;

			poFeature = OGRFeature::CreateFeature(poLayer->GetLayerDefn());
			poFeature->SetField(field, szName);

			OGRPoint pt;

			pt.setX(points.at(i).at(0));
			pt.setY(points.at(i).at(1));

			poFeature->SetGeometry(&pt);

			if (poLayer->CreateFeature(poFeature) != OGRERR_NONE)
			{
				printf("Failed to create feature in shapefile.\n");
				exit(1);
			}

			OGRFeature::DestroyFeature(poFeature);
			i++;
		}
	}
	else {
		while (!feof(stdin) && i < points.size()) //tu zrobiæ fora
		{
			OGRFeature* poFeature;

			poFeature = OGRFeature::CreateFeature(poLayer->GetLayerDefn());
			poFeature->SetField(field, szName);

			OGRMultiPoint multi_pt;
			OGRPoint pt;

			pt.setX(points.at(i).at(0));
			pt.setY(points.at(i).at(1));

			multi_pt.addGeometry(&pt);

			poFeature->SetGeometry(&multi_pt);

			if (poLayer->CreateFeature(poFeature) != OGRERR_NONE)
			{
				printf("Failed to create feature in shapefile.\n");
				exit(1);
			}
			OGRFeature::DestroyFeature(poFeature);
			i++;
		}
	}
	GDALClose(poDS);
}
//koniec funckji
//zapisywanie multipointa