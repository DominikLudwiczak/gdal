#pragma once
#include "ogrsf_frmts.h"
#include <vector>

std::vector<std::vector<double>> read(const  char* name, const  char* layer, const char* field);

std::vector<double> readPointShapeFile(OGRGeometry* poGeometry, OGRFeature* poFeature);

std::vector<double> readMultiPointShapeFile(OGRGeometry* poGeometry, OGRFeature* poFeature);

void write(const char* name, const char* layer, const char* field, std::vector<std::vector<double>> points, bool check);

void writePointShapeFile(const char* name, const char* layer, const char* field, std::vector<std::vector<double>> points);

void writeMultiPointShapeFile(const char* name, const char* layer, const char* field, std::vector<std::vector<double>> points);