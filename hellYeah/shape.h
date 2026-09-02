#pragma once
#include <vector>
#include <array>
#include <cmath>
#include <iostream>

#include "float2.h"
#include "segment.h"
#include "pureShape.h"
#include "shapes.h"

using namespace std;

enum VERT_TYPE {
	OUT,
	IN,
};

struct lineSided {
	int from = 0; // Index of vertex (from)
	int to = 0; // Index of vertex (to)
	VERT_TYPE fromType = VERT_TYPE::OUT; // Type of vertex (from)
	VERT_TYPE toType = VERT_TYPE::OUT; // Type of vertex (to)
	vector<float2>* fromArrPtr; // Pointer to the array to which the vertex index belongs (from)
	vector<float2>* toArrPtr; // Pointer to the array to which the vertex index belongs (to)

	float2 sideVert; // Vertex itself. Defines the positive side of the lineSided.
	int expressionIndexFit = 0; // Index of expression if the check is on positive side. 
	int expressionIndexOtherwise = 0; // Index of expression if the check is on negative side. 
};

struct lineExpressioned { 
	int from;
	int to;
	int expressionIndex;
};

//template<bool isCyclic> // Size - is a number of arcs. (Except the ends when is not cyclic)
class Shape {
public:
	PureShape sourcePureShape;

	vector<array<float, 10>> expressionsCoefficients = {};
	vector<array<bool, 3>> expressionsSelection = {};

private:
	vector<float2> vertsIn;
	vector<float2> vertsOut;

	vector<lineSided> linesIn;
	vector<lineSided> linesOut;
	vector<lineSided> linesBetween;

	bool defaultExpressionIndex = 0;

public:
	Shape(PureShape ps, vector<float>* expressionsCoefficientsPtr, vector<bool>* expressionsSelectionPtr);

private:
	bool isVertOnLeftOfLine(const float2& lineVert1, const float2& lineVert2, const float2& sideVert) const;

	bool isVertHigherThanLine(const float2& lineVert1, const float2& lineVert2, const float2& sideVert) const;

	int getProperExp(const float2& lineVert1, const float2& lineVert2, const float2& sideVert, const int expressionIndexFit, const int expressionIndexOtherwise);

	// TODO: vert1 is useless in segments next to first one.
	void lineDefine(
		//float2& vert1,
		float2& vert2,
		vector<float2>* vertsPtr,
		vector<lineSided>& lines,
		float2 sideVert,
		VERT_TYPE vertType,
		int expressionIndexFit,
		int expressionIndexOtherwise,
		float& leftestVertX,
		bool& defaultExpressionIndex
		//bool isFirstSegment = false
	);

	void lineBetweenDefine(
		int indexIn,
		int indexOut,
		vector<float2>* vertsInPtr,
		vector<float2>* vertsOutPtr,
		vector<lineSided>& lines,
		float2 sideVert,
		int expressionIndexFit,
		int expressionIndexOtherwise
	);
};