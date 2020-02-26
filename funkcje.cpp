#include "funkcje.h"

std::vector<std::vector<double>> readPointShapeFile(const  char* name, const  char* layer)
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
		if (poGeometry != NULL
			&& wkbFlatten(poGeometry->getGeometryType()) == wkbPoint)
		{
#if GDAL_VERSION_NUM >= GDAL_COMPUTE_VERSION(2,3,0)
			OGRPoint * poPoint = poGeometry->toPoint();
#else
			OGRPoint* poPoint = (OGRPoint*)poGeometry;
#endif

			printf("%.3f,%3.f\n", poPoint->getX(), poPoint->getY());
		}
		else
		{
			printf("no point geometry\n");
		}

		result.push_back(punkt);
		punkt.clear();
		OGRFeature::DestroyFeature(poFeature);
		i++;
	}
	GDALClose(poDS);
	return result;
}






std::vector<std::vector<double>> readMultiPointShapeFile(const  char* name, const  char* layer, const char* field)
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
	OGRFieldDefn oField1("Number" , OFTString);

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
			printf("%d", poGeometry->getGeometryType());
			if (wkbFlatten(poGeometry->getGeometryType()) == wkbPoint)
			{
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
					printf("%d%s%f%s%f\n", i, " ", x, " ", y);
				}
			}
			else
			{
				printf("no point geometry\n");
			}
		}
		else
			printf("NULL\n");

		result.push_back(punkt);
		punkt.clear();
		OGRFeature::DestroyFeature(poFeature);
		i++;
	}
	GDALClose(poDS);
	return result;
}




void writePointShapeFile(const char* name, const char* layer, const char* field_name, double x, double y)
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

	OGRFieldDefn oField(field_name, OFTInteger64);

	oField.SetWidth(32);

	if (poLayer->CreateField(&oField) != OGRERR_NONE)
	{
		printf("Creating Name field failed.\n");
		exit(1);
	}
	char szName[33];

	while (!feof(stdin)
		&& fscanf_s(stdin, "%lf,%lf,%32s", &x, &y, szName) == 3)
	{
		OGRFeature* poFeature;

		poFeature = OGRFeature::CreateFeature(poLayer->GetLayerDefn());
		poFeature->SetField(field_name, szName);

		OGRPoint pt;

		pt.setX(x);
		pt.setY(y);

		poFeature->SetGeometry(&pt);

		if (poLayer->CreateFeature(poFeature) != OGRERR_NONE)
		{
			printf("Failed to create feature in shapefile.\n");
			exit(1);
		}

		OGRFeature::DestroyFeature(poFeature);
	}

	GDALClose(poDS);
}