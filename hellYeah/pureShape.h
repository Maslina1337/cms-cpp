#pragma once
#include <vector>
#include "float2.h"

using namespace std;

struct PureShape {
	vector<float2> locs;
	vector<float2> locsMiddles;
	vector<float> fadeoutScales;

	bool isSubtract;
	bool isCyclic;
	// bool doIgnore; // Unused for now.

	float opacity;
	float fadeoutAngle;
	float fadeoutLength;

	float2 fadeoutShift; // Exists just in case.

	int index;
};

struct shapeSizes {
	int verts;
	int lines;
	int expressions;

	int vertsPrev;
	int linesPrev;
	int expressionsPrev;
};

template<typename type>
struct PureShapeLayer {
	const int size;
	const float* const angles;
	const type* const pureShapes;
};