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

extern "C" DLL_EXPORT float Tick(int* fillMe, int fillMeSize, float v, float h);

#endif

using namespace std;

//void main() {
//	//PureShape ps1;
//	//PureShape ps2;
//	//PureShape ps3;
//	//PureShape ps4;
//
//	//int h_angles[2] = { 90, 180 };
//
//	//PureShape* h_shapes1[2] = { &ps1, &ps2 };
//	//PureShapeLayer<PureShape*> hl1 = { .size = 2, .angles = h_angles, .pureShapes = h_shapes1 };
//
//	//PureShape* h_shapes2[2] = { &ps3, &ps4 };
//	//PureShapeLayer<PureShape*> hl2 = { .size = 2, .angles = h_angles, .pureShapes = h_shapes2 };
//
//	//int v_angles[2] = { 0, 180 };
//	//PureShapeLayer<PureShape*> v_shapes2[2] = { hl1, hl2 };
//	//PureShapeLayer<PureShapeLayer<PureShape*>> vl = { .size = 2, .angles = v_angles, .pureShapes = v_shapes2 };
//
//	//PureShapeLayer<PureShapeLayer<PureShape*>> s_shapes[1] = { vl };
//}

// CMS stands for custom mesh shade.
namespace CMS {
	void getNeighborsIndices(int& prevIndex, int& nextIndex, const float ofAngle, const int *inAngles, const int inAnglesSize, const bool isSeamless = true) {
		bool isAnyPrevFound = false;
		bool isAnyNextFound = false;

		// TODO: Rewrite me.
		for (int i = 0; i < inAnglesSize; i++) {
			int currentCheckAngle = *(inAngles + i);
			//int previousCheckAngle = *(inAngles + i - 1);
			if (isAnyPrevFound) {
				if (currentCheckAngle <= ofAngle and currentCheckAngle > inAngles[prevIndex]) prevIndex = i;
			}
			else {
				if (currentCheckAngle <= ofAngle) {
					isAnyPrevFound = true;
					prevIndex = i;
				}
			}

			if (isAnyNextFound) {
				if (currentCheckAngle >= ofAngle and currentCheckAngle < inAngles[nextIndex]) nextIndex = i;
			}
			else {
				if (currentCheckAngle >= ofAngle) {
					isAnyNextFound = true;
					nextIndex = i;
				}
			}
		}

		if (isSeamless) {
			// If it's seamless.
			prevIndex = isAnyPrevFound ? prevIndex : inAnglesSize - 1;
			nextIndex = isAnyNextFound ? nextIndex : 0;
		}
		else {
			// If it's not seamless
			prevIndex = isAnyPrevFound ? prevIndex : nextIndex;
			nextIndex = isAnyNextFound ? nextIndex : prevIndex;
		}
	};

	PureShape MergePureShapes(PureShape fromPureShape, PureShape& toPureShape, float factor) {
		// Modifying the from pure shape.

		// Vectors.
		for (int i = 0; i < fromPureShape.locs.size(); i++)
		fromPureShape.locs[i] += (toPureShape.locs[i] - fromPureShape.locs[i]) * factor;
		
		for (int i = 0; i < fromPureShape.locsMiddles.size(); i++)
		fromPureShape.locsMiddles[i] += (toPureShape.locsMiddles[i] - fromPureShape.locsMiddles[i]) * factor;

		for (int i = 0; i < fromPureShape.fadeoutScales.size(); i++)
		fromPureShape.fadeoutScales[i] += (toPureShape.fadeoutScales[i] - fromPureShape.fadeoutScales[i]) * factor;

		// Bools.
		fromPureShape.isSubtract = factor < 0.5 ? fromPureShape.isSubtract : toPureShape.isSubtract;
		fromPureShape.isCyclic = factor < 0.5 ? fromPureShape.isCyclic : toPureShape.isCyclic;
		fromPureShape.doIgnore = fromPureShape.doIgnore or toPureShape.doIgnore;

		// Floats.
		fromPureShape.opacity += (toPureShape.opacity - fromPureShape.opacity) * factor;
		fromPureShape.fadeoutAngle += (toPureShape.fadeoutAngle - fromPureShape.fadeoutAngle) * factor;
		fromPureShape.fadeoutLength += (toPureShape.fadeoutLength - fromPureShape.fadeoutLength) * factor;

		return fromPureShape;
	}

	PureShape MergePureShapesHorizontally(
		int prevHorizontalAngle,
		int nextHorizontalAngle,
		PureShape* prevHorizontalPureShape,
		PureShape* nextHorizontalPureShape,
		float hAngle) 
	{
		if (prevHorizontalAngle == nextHorizontalAngle) return *prevHorizontalPureShape;
		
		// -180, Next, ... Past, h, 180
		if (nextHorizontalAngle < prevHorizontalAngle) return MergePureShapes(
			*prevHorizontalPureShape, *nextHorizontalPureShape,
			(hAngle - prevHorizontalAngle) / (1 - prevHorizontalAngle + nextHorizontalAngle)
		);

		// -180, ... Past, h, Next, ... 180
		return MergePureShapes(
			*prevHorizontalPureShape, *nextHorizontalPureShape,
			(hAngle - prevHorizontalAngle) / (prevHorizontalAngle - nextHorizontalAngle)
		);
	}

	// angleVertical = [0-1 (means 0-180)]		angleHorizontal = [0-1 (means 0-360)]
	void Tick(float angleVertical, float angleHorizontal) {
		for (int sIndex = 0; sIndex < shapesSize; sIndex++) {

			// Vertical layer
			const int verticalLayerSize = pureShapes[sIndex].size;
			const int* verticalLayerAngles = pureShapes[sIndex].angles;

			int prevIndexV;
			int nextIndexV;
			getNeighborsIndices(prevIndexV, nextIndexV, angleVertical, verticalLayerAngles, verticalLayerSize, false);

			// Horizontal layer (lower)
			const int horizontalLayerLowerSize = pureShapes[sIndex].pureShapes[prevIndexV].size;
			const int* horizontalLayerLowerAngles = pureShapes[sIndex].pureShapes[prevIndexV].angles;

			int prevIndexHL;
			int nextIndexHL;
			getNeighborsIndices(prevIndexHL, nextIndexHL, angleHorizontal, horizontalLayerLowerAngles, horizontalLayerLowerSize);

			// Horizontal layer (higher)
			const int horizontalLayerHigherSize = pureShapes[sIndex].pureShapes[nextIndexV].size;
			const int* horizontalLayerHigherAngles = pureShapes[sIndex].pureShapes[nextIndexV].angles;

			int prevIndexHH;
			int nextIndexHH;
			getNeighborsIndices(prevIndexHH, nextIndexHH, angleHorizontal, horizontalLayerHigherAngles, horizontalLayerHigherSize);

			PureShape* pureShapeLowPrevPtr = pureShapes[sIndex].pureShapes[prevIndexV].pureShapes[prevIndexHL];
			PureShape* pureShapeLowNextPtr = pureShapes[sIndex].pureShapes[prevIndexV].pureShapes[nextIndexHL];
			PureShape* pureShapeHighPrevPtr = pureShapes[sIndex].pureShapes[nextIndexV].pureShapes[prevIndexHH];
			PureShape* pureShapeHighNextPtr = pureShapes[sIndex].pureShapes[nextIndexV].pureShapes[nextIndexHH];

			PureShape prevMergeH = MergePureShapesHorizontally(
				horizontalLayerLowerAngles[prevIndexHL],
				horizontalLayerLowerAngles[nextIndexHL],
				pureShapes[sIndex].pureShapes[prevIndexV].pureShapes[prevIndexHL],
				pureShapes[sIndex].pureShapes[prevIndexV].pureShapes[nextIndexHL],
				angleHorizontal);

			PureShape nextMergeH = MergePureShapesHorizontally(
				horizontalLayerHigherAngles[prevIndexHL],
				horizontalLayerLowerAngles[nextIndexHL],
				pureShapes[sIndex].pureShapes[nextIndexV].pureShapes[prevIndexHH],
				pureShapes[sIndex].pureShapes[nextIndexV].pureShapes[nextIndexHH],
				angleHorizontal);

			PureShape resultMerge = MergePureShapes(prevMergeH, nextMergeH,
				(angleVertical - verticalLayerAngles[prevIndexV]) /
				(verticalLayerAngles[nextIndexV] - verticalLayerAngles[prevIndexV]));
			
			//cout << (angleVertical - verticalLayerAngles[prevIndexV]) /
			//	(verticalLayerAngles[nextIndexV] - verticalLayerAngles[prevIndexV]);
			//for (int i = 0; i < resultMerge.locs.size(); i++) {
			//	cout << resultMerge.locs[i].x << "       " << resultMerge.locs[i].y << endl;
			//}
		}
	}
};

//int main() {
//	CMS::Tick(0.5f, 0.5f);
//	return 0;
//};