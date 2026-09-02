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
	bool doIgnore;

	float opacity;
	float fadeoutAngle;
	float fadeoutLength;

	int index;

	//const int* const vertsSizePtr;
	//const int* const linesSizePtr;
	//const int* const expressionSizePtr;
};

struct shapeSizes {
	int verts;
	int lines;
	int expressions;
};

template<typename type>
struct PureShapeLayer {
	const int size;
	const float* const angles;
	const type* const pureShapes;
};