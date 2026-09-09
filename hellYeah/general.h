#pragma once
#include <cmath>
#include <iostream>
#include <array>
#include <vector>
#include "pureShape.h"
#include "shape.h"
#include "shapes.h"
#include "float2.h"

#ifndef BACKEND_H
#define BACKEND_H
#define DLL_EXPORT __declspec(dllexport)

extern "C" {
	// void DLL_EXPORT CMSGetShapesSizes(int* shapesSize, int* vertsSize, int* linesSize, int* expressionsSize);
	// void DLL_EXPORT CMSGetPersonalShapesSizes(int* shapesSizes);
	void DLL_EXPORT CMSTick(float v, float h, 
		float* vertsPtr, float* linesPtr, 
		float* expressionsCoefficientsPtr, float* expressionsSelectionsPtr, 
		float* opacityPerShapePtr, float* isSubtractPerShapePtr, float* borderPerShapePtr);
}

#endif

using namespace std;

namespace CMS {
	void getNeighborsIndices(int& prevIndex, int& nextIndex, const float ofAngle, const float* inAngles, const int inAnglesSize, const bool isSeamless = true);

	PureShape mergePureShapes(PureShape fromPureShape, PureShape& toPureShape, float factor);

	PureShape mergePureShapesHorizontally(
		float prevHorizontalAngle,
		float nextHorizontalAngle,
		PureShape* prevHorizontalPureShape,
		PureShape* nextHorizontalPureShape,
		float hAngle);

	// angleVertical = [0-1 (means 0-180)]		angleHorizontal = [0-1 (means 0-360)]
	void tick(
		float v, float h,
		float* vertsPtr, float* linesPtr,
		float* expressionsCoefficientsPtr, float* expressionsSelectionsPtr,
		float* opacityPerShapePtr, float* isSubtractPerShapePtr, float* borderPerShapePtr,
		bool debug = false
	);
};