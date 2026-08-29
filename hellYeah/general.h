#include <cmath>
#include <iostream>
#include <array>
#include <vector>
#include "pureShape.h"
#include "shapes.h"
#include "float2.h"

#ifndef BACKEND_H
#define BACKEND_H
#define DLL_EXPORT __declspec(dllexport)

extern "C" DLL_EXPORT float Tick(float* expCoefficients, int expCoefficientsSize, float v, float h);

#endif

using namespace std;

namespace CMS {
	void GetNeighborsIndices(int& prevIndex, int& nextIndex, const float ofAngle, const float* inAngles, const int inAnglesSize, const bool isSeamless = true);

	PureShape MergePureShapes(PureShape fromPureShape, PureShape& toPureShape, float factor);

	PureShape MergePureShapesHorizontally(
		int prevHorizontalAngle,
		int nextHorizontalAngle,
		PureShape* prevHorizontalPureShape,
		PureShape* nextHorizontalPureShape,
		float hAngle);

	// angleVertical = [0-1 (means 0-180)]		angleHorizontal = [0-1 (means 0-360)]
	void Tick(float angleVertical, float angleHorizontal);
};