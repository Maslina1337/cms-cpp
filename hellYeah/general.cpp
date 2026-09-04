//#include "pch.h"
#include "general.h"

//void CMSGetShapesSizes(int* shapesSize_, int* vertsSize_, int* linesSize_, int* expressionsSize_) {
//	*shapesSize_ = shapesSize;
//	*vertsSize_ = vertsSize;
//	*linesSize_ = linesSize;
//	*expressionsSize_ = expressionsSize;
//};
// void CMSGetPersonalShapesSizes(int* shapesSizes) {};
void CMSTick(float v, float h, float* vertsPtr, float* linesPtr, float* expressionsCoefficientsPtr, float* expressionsSelectionsPtr) {
	// Valid test.
	//if (
	//	expressionsSelectionsPtr == nullptr 
	//	or expressionsCoefficientsPtr == nullptr 
	//	or expressionsCoefficientsSize != (expressionsSize + 2) * 10
	//	or expressionsSelectionsSize != (expressionsSize + 2)
	//) return;

	//expressionsSelectionsPtr[0] = true;
	//expressionsSelectionsPtr[9] = true;
	//return;
	CMS::tick(v, h, expressionsCoefficientsPtr, expressionsSelectionsPtr);
};

//int main() {
//	bool* expressionsSelectionsPtr = new bool[(expressionsSize + 2) * 3];
//	float* expressionsCoefficientsPtr = new float[(expressionsSize + 2) * 10];
//
//	CMS::tick(0.5f, 0.5f, expressionsCoefficientsPtr, expressionsSelectionsPtr);
//
//	for (int i = 0; i < (expressionsSize + 2) * 10; i++) {
//		if (i % 10 == 0) cout << endl;
//		cout << expressionsCoefficientsPtr[i] << " ";
//	}
//
//	for (int i = 0; i < (expressionsSize + 2) * 3; i++) {
//		if (i % 3 == 0) cout << endl;
//		cout << expressionsSelectionsPtr[i] << " ";
//	}
//
//	return 0;
//}

namespace CMS {
	void getNeighborsIndices(int& prevIndex, int& nextIndex, const float ofAngle, const float* inAngles, const int inAnglesSize, const bool isSeamless) {
		bool isAnyPrevFound = false;
		bool isAnyNextFound = false;

		// TODO: Rewrite me.
		for (int i = 0; i < inAnglesSize; i++) {
			float currentCheckAngle = *(inAngles + i);
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

	PureShape mergePureShapes(PureShape fromPureShape, PureShape& toPureShape, float factor) {
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

	PureShape mergePureShapesHorizontally(
		float prevHorizontalAngle,
		float nextHorizontalAngle,
		PureShape* prevHorizontalPureShape,
		PureShape* nextHorizontalPureShape,
		float hAngle)
	{
		if (prevHorizontalAngle == nextHorizontalAngle) return *prevHorizontalPureShape;

		return mergePureShapes(
			*prevHorizontalPureShape, *nextHorizontalPureShape,
			(nextHorizontalAngle < prevHorizontalAngle) ?
			(hAngle - prevHorizontalAngle) / (1 - prevHorizontalAngle + nextHorizontalAngle) : // -180, Next, ... Past, h, 180
			(hAngle - prevHorizontalAngle) / (nextHorizontalAngle - prevHorizontalAngle) // -180, ... Past, h, Next, ... 180
		);
	}

	// v = [0-1 (means 0-180)]		h = [0-1 (means 0-360)]
	void tick(float v, float h, float* expressionsCoefficientsPtr, float* expressionsSelectionsPtr) {

		// Raw Expressions.
		for (int i = 0; i < 20; i++) expressionsCoefficientsPtr[i] = 0.0f;
		expressionsCoefficientsPtr[10] = 1.0f;

		expressionsSelectionsPtr[0] = 0;
		expressionsSelectionsPtr[1] = 0;
		//expressionsSelectionsPtr[0] = true;
		//expressionsSelectionsPtr[1] = false;
		//expressionsSelectionsPtr[2] = false;
		//expressionsSelectionsPtr[3] = true;
		//expressionsSelectionsPtr[4] = false;
		//expressionsSelectionsPtr[5] = false;

		//vector<float> expressionsCoefficients = { 
		//	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
		//	1, 0, 0, 0, 0, 0, 0, 0, 0, 0 
		//};

		//vector<bool> expressionsSelections = { 
		//	true, false, false, 
		//	true, false, false 
		//};

		int segmentsCompleted = 2;

		//expressionsCoefficients.reserve((expressionsSize + 2) * 10);
		//expressionsSelections.reserve((expressionsSize + 2) * 3);

		for (int sIndex = 0; sIndex < shapesSize; sIndex++) {

			// Vertical layer
			const int verticalLayerSize = pureShapes[sIndex].size;
			const float* verticalLayerAngles = pureShapes[sIndex].angles;

			int prevIndexV;
			int nextIndexV;
			getNeighborsIndices(prevIndexV, nextIndexV, v, verticalLayerAngles, verticalLayerSize, false);

			// Horizontal layer (lower)
			const int horizontalLayerLowerSize = pureShapes[sIndex].pureShapes[prevIndexV].size;
			const float* horizontalLayerLowerAngles = pureShapes[sIndex].pureShapes[prevIndexV].angles;

			int prevIndexHL;
			int nextIndexHL;
			getNeighborsIndices(prevIndexHL, nextIndexHL, h, horizontalLayerLowerAngles, horizontalLayerLowerSize);

			// Horizontal layer (higher)
			const int horizontalLayerHigherSize = pureShapes[sIndex].pureShapes[nextIndexV].size;
			const float* horizontalLayerHigherAngles = pureShapes[sIndex].pureShapes[nextIndexV].angles;

			int prevIndexHH;
			int nextIndexHH;
			getNeighborsIndices(prevIndexHH, nextIndexHH, h, horizontalLayerHigherAngles, horizontalLayerHigherSize);

			PureShape* pureShapeLowPrevPtr = pureShapes[sIndex].pureShapes[prevIndexV].pureShapes[prevIndexHL];
			PureShape* pureShapeLowNextPtr = pureShapes[sIndex].pureShapes[prevIndexV].pureShapes[nextIndexHL];
			PureShape* pureShapeHighPrevPtr = pureShapes[sIndex].pureShapes[nextIndexV].pureShapes[prevIndexHH];
			PureShape* pureShapeHighNextPtr = pureShapes[sIndex].pureShapes[nextIndexV].pureShapes[nextIndexHH];

			PureShape prevMergeH = mergePureShapesHorizontally(
				horizontalLayerLowerAngles[prevIndexHL],
				horizontalLayerLowerAngles[nextIndexHL],
				pureShapes[sIndex].pureShapes[prevIndexV].pureShapes[prevIndexHL],
				pureShapes[sIndex].pureShapes[prevIndexV].pureShapes[nextIndexHL],
				h);
			
			if (verticalLayerAngles[nextIndexV] == verticalLayerAngles[prevIndexV]) {
				Shape s(prevMergeH, expressionsCoefficientsPtr, expressionsSelectionsPtr, segmentsCompleted);
			}
			else {
				PureShape nextMergeH = mergePureShapesHorizontally(
					horizontalLayerHigherAngles[prevIndexHL],
					horizontalLayerLowerAngles[nextIndexHL],
					pureShapes[sIndex].pureShapes[nextIndexV].pureShapes[prevIndexHH],
					pureShapes[sIndex].pureShapes[nextIndexV].pureShapes[nextIndexHH],
					h);

				PureShape resultMerge = mergePureShapes(prevMergeH, nextMergeH, (v - verticalLayerAngles[prevIndexV]) /
					(verticalLayerAngles[nextIndexV] - verticalLayerAngles[prevIndexV]));
				Shape s(resultMerge, expressionsCoefficientsPtr, expressionsSelectionsPtr, segmentsCompleted);
			}

			
		}
	}
};