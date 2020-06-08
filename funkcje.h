#pragma once
#include "ogrsf_frmts.h"
#include <vector>
#include "Points.h"
#include "MultiPoints.h"

std::vector<OGRGeometry*> read(const  char* name, const  char* layer, const char* field);

void division(Points& points, MultiPoints& multiPoints, std::vector<OGRGeometry*> geometry);

void write(const char* name, const char* layer, const char* field, std::vector<std::vector<double>> points, const char* type);

void writePointShapeFile(const char* field, OGRLayer* poLayer, std::vector<std::vector<double>> points);

void writeMultiPointShapeFile(const char* field, OGRLayer* poLayer, std::vector<std::vector<double>> points);