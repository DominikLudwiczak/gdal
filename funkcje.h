#pragma once
#include "ogrsf_frmts.h"
#include <vector>
#include "Points.h"
#include "MultiPoints.h"

std::vector<OGRGeometry*> read(const  char* name, const  char* layer, const char* field);

void division(Points& points, MultiPoints& multiPoints, std::vector<OGRGeometry*> geometry);

void color(OGRFeature* poFeature);