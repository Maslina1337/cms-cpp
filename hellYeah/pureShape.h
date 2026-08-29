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
};

template<typename type>
struct PureShapeLayer {
	const int size;
	const int* const angles;
	const type* const pureShapes;
};