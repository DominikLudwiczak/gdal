#pragma once
#include <vector>
#include "ogrsf_frmts.h"

std::vector<std::vector<double>> readPointShapeFile(const  char* name, const  char* layer);

std::vector<std::vector<double>> readMultiPointShapeFile(const  char* name, const  char* layer, const char* field);

void writePointShapeFile(const char* name, const char* layer, const char* field_name, double x, double y);