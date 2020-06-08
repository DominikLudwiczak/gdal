#include "funkcje.h"
#include "Points.h"

std::vector<OGRGeometry*> read(const  char* name, const  char* layer, const char* field)
{
	std::vector<OGRGeometry*> result;
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
	OGRFieldDefn oField1(field, OFTInteger64);

	result.clear();
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
			result.push_back(poGeometry);
		else
			printf("NULL\n");
	}
	GDALClose(poDS);
	return result;
}




void division(Points& points, MultiPoints& multiPoints, std::vector<OGRGeometry*> geometry)
{
	if (wkbFlatten(geometry.at(0)->getGeometryType()) == wkbPoint)
		for (auto row : geometry)
			points.addGeometry(row);
	else if (wkbFlatten(geometry.at(0)->getGeometryType()) == wkbMultiPoint)
		for (auto row : geometry)
			multiPoints.addGeometry(row);
}




void color(OGRFeature* poFeature)
{
	OGRStyleTable oStyleTable;

	OGRStyleMgr* poStyleMgr = new OGRStyleMgr(&oStyleTable);

	// Create a new style in the style table by specifying the whole style string

	if (poStyleMgr->AddStyle("@Name","PEN(c:#123456;w:10px);BRUSH(c:#345678);SYMBOL(c:#345678;id:'1')"))
		poStyleMgr->SetFeatureStyleString(poFeature, "@Name", TRUE);

	oStyleTable.SaveStyleTable("ttt.tbl");
}