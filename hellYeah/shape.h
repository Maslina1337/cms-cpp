//#pragma once
//#include <vector>
//#include <array>
//#include <cmath>
//#include "float2.h"
//#include "segment.h"
//#include "pureShape.h"
//
//////
//#define SEGMENT_MEMBERS_THIEF \
//expressionsSelection.push_back(segment.expressionSelection); \
//expressionsCoefficients.push_back(segment.expressionCoefficients); \
//array<float2, 3> vertsInS = segment.vertsIn; \
//bool isVertsInSTriple = segment.isVertsInTriple; \
//array<float2, 3> vertsOutS = segment.vertsOut; \
//bool isVertsOutSTriple = segment.isVertsOutTriple; \
//////
//
//using namespace std;
//
//
//
//
//
//
//enum VERT_TYPE {
//	OUT,
//	IN,
//	INTER,
//};
//
//
//
//
//
//
//struct line {
//	int from = 0; // Index of vertex (from)
//	int to = 0; // Index of vertex (to)
//	VERT_TYPE fromType = VERT_TYPE::OUT; // Type of vertex (from)
//	VERT_TYPE toType = VERT_TYPE::OUT; // Type of vertex (to)
//	vector<float2>& fromArrRef; // Reference to the array to which the vertex index belongs (from)
//	vector<float2>& toArrRef; // Reference to the array to which the vertex index belongs (to)
//
//	float2 otherVert; // Vertex itself. Defines the positive side of the line.
//	int expFits = 0; // Index of expression if the check is on positive side. 
//	int expOtherwise = 0; // Index of expression if the check is on negative side. 
//};
//
//
//
//
//
//template<bool isCyclic_, int size_> // Size - is a number of arcs. (Except the ends when is not cyclic)
//class Shape {
//public:
//	bool isCyclic = isCyclic_;
//	bool size = size_
//
//	bool isSubtract;
//	
//
//private:
//	vector<float2> vertsIn;
//	vector<float2> vertsOut;
//	vector<float2> vertsInter;
//
//	float rightestVertX = numeric_limits<float>::lowest(); // Smth really far left.
//	VERT_TYPE rightestVertType = VERT_TYPE::OUT; // Useless actually
//
//	vector<array<int, 2>> bothExpsPerInterVert;
//
//	vector<array<float, 10>> expressionsCoefficients = { { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } };
//	vector<array<bool, 3>> expressionsSelection = { { true, false, false }, { true, false, false } };
//
//public:
//	Shape(const PureShape& pureShape) {
//		this->isSubtract = pureShape.isSubtract;
//
//		const int locsSize = size + (not isCyclic) * 2;
//		const int locsMiddlesSize = size + not isCyclic;
//
//		// Calculating locs fadeout
//		const float2 shift = float2(cos(fadeoutAngle), sin(fadeoutAngle)) * fadeoutLength;
//		vector<float2> locsFadeout(locsSize);
//		vector<float2> locsMiddlesFadeout(locsMiddlesSize);
//
//		locsMiddlesFadeout[0] = locsMiddlesFadeout[0] + shift;
//
//		//// Fadeout verts define.
//		for (int i = 1; i < locsMiddlesSize-isCyclic; i++) {
//			locsMiddlesFadeout[i]((locsMiddles[i] - locsMiddles[i - 1]) * fadeoutScales[i - 1] + locsMiddlesFadeout[i - 1]);
//		}
//
//		if constexpr (isCyclic) {
//			for (int i = 0; i < size; i++) {
//				locsFadeout[i] = (locs[i] - locsMiddles[(i - 1 + size) % size]) * fadeoutScales[(i - 1 + size) % size] + locsMiddlesFadeout[(i - 1 + size) % size];
//			};
//		}
//		else {
//			for (int i = 0; i < size; i++) {
//				locsFadeout[i] = (locs[i] - locsMiddles[i]) * fadeoutScales[i] + locsMiddlesFadeout[i];
//			};
//		}
//
//		float2 nonCyclicLocStart;
//		float2 nonCyclicLocEnd;
//		float2 nonCyclicLocFadeoutStart;
//		float2 nonCyclicLocFadeoutEnd;
//
//		// Continuing tails.
//		if (isCyclic) {
//			nonCyclicLocStart = (locsMiddles[0] - locs[0]).getNormalized() * 2 + locs[0];
//			nonCyclicLocEnd = (locsMiddles[-1] - locs[-1]).getNormalized() * 2 + locs[-1];
//			nonCyclicLocFadeoutStart = (locsMiddlesFadeout[0] - locsFadeout[0]).getNormalized() * 2 + locsFadeout[0];
//			nonCyclicLocFadeoutEnd = (locsMiddlesFadeout[-1] - locsFadeout[-1]).getNormalized() * 2 + locsFadeout[-1];
//		}
//		////
//
//		vector<line> linesIn = {};
//		vector<line> linesOut = {};
//		vector<line> linesBetween = {};
//
//		//// Creating segments
//
//		// First segment.
//		if constexpr (isCyclic) {
//			Segment<true> segment = Segment<true>(
//				{ locsMiddles[size-1], locs[0], locsMiddles[0] },
//				{ locsMiddlesFadeout[size-1], locsFadeout[0], locsMiddlesFadeout[0] }
//			);
//
//			SEGMENT_MEMBERS_THIEF;
//
//			lineDefine(0, 0, vertsIn, vertsInS, linesIn, vertsOutS[1], VERT_TYPE::IN, 1);
//			lineDefine(0, 0, vertsOut, vertsOutS, linesOut, vertsInS[1], VERT_TYPE::OUT, 0);
//
//			lineBetweenDefine(0, 0, 0, vertsIn.size() - 2, vertsOut.size() - 2, linesBetween,
//				(isVertsInSTriple ? vertsInS : vertsOutS)[isVertsInSTriple or isVertsOutSTriple], size + 1);
//
//			if (isVertsInSTriple) lineDefine(0, 1, vertsIn, vertsInS, linesIn, vertsOutS[0], VERT_TYPE::IN, 1);
//			if (isVertsOutSTriple) lineDefine(0, 1, vertsOut, vertsOutS, linesOut, vertsInS[0], VERT_TYPE::OUT, 0);
//
//			lineBetweenDefine(0, 1 + isVertsInSTriple, 1 + isVertsOutSTriple, vertsIn.size() - 1, vertsOut.size() - 1, linesBetween,
//				(isVertsInSTriple ? vertsInS : vertsOutS)[isVertsInSTriple or isVertsOutSTriple], 3);
//		}
//		else {
//			Segment<true> segment = Segment<true>(
//				{ nonCyclicLocStart, locsMiddles[0] },
//				{ nonCyclicLocFadeoutStart, locsMiddlesFadeout[0] }
//			);
//
//			SEGMENT_MEMBERS_THIEF;
//
//			lineDefine(0, 0, vertsIn, vertsInS, linesIn, vertsOutS[1], VERT_TYPE::IN, 1);
//			lineDefine(0, 0, vertsOut, vertsOutS, linesOut, vertsInS[1], VERT_TYPE::OUT, 0);
//			lineBetweenDefine(0, 0, 0, vertsIn.size() - 2, vertsOut.size() - 2, linesBetween, vertsInS[1], 0); // 0 coz we doesn't care about exp otherwise.
//			lineBetweenDefine(0, 1, 1, vertsIn.size() - 1, vertsOut.size() - 1, linesBetween, vertsInS[0], 3);
//		}
//
//		// Arc segments
//		for (uint8_t arcSegmentI = 1; arcSegmentI < size - 2*isCyclic + 1; arcSegmentI++) {
//			Segment<true> segment = Segment<true>(
//				{ locsMiddles[arcSegmentI - 1], locs[arcSegmentI - (not isCyclic)], locsMiddles[arcSegmentI]},
//				{ locsMiddlesFadeout[arcSegmentI - 1], locsFadeout[arcSegmentI - (not isCyclic)], locsMiddlesFadeout[arcSegmentI]}
//			);
//			
//			SEGMENT_MEMBERS_THIEF;
//
//			// Defining lines.
//			lineDefine(arcSegmentI, 0, vertsIn, vertsInS, linesIn, vertsOutS[1], VERT_TYPE::IN, 1);
//			if (isVertsInSTriple) lineDefine(arcSegmentI, 1, vertsIn, vertsInS, linesIn, vertsOutS[0], VERT_TYPE::IN, 1);
//
//			lineDefine(arcSegmentI, 0, vertsOut, vertsOutS, linesOut, vertsInS[1], VERT_TYPE::OUT, 0);
//			if (isVertsOutSTriple) lineDefine(arcSegmentI, 1, vertsOut, vertsOutS, linesOut, vertsInS[0], VERT_TYPE::OUT, 0);
//
//			lineBetweenDefine(arcSegmentI, 1 + isVertsInSTriple, 1 + isVertsOutSTriple, vertsIn.size() - 1, vertsOut.size() - 1, linesBetween,
//				(isVertsInSTriple ? vertsInS : vertsOutS)[isVertsInSTriple or isVertsOutSTriple], arcSegmentI + 3);
//		}
//
//		// Last segment.
//		if constexpr (isCyclic) {
//			Segment<true> segment = Segment<true>(
//				{ locsMiddles[size - 2], locs[size-1], locsMiddles[size - 1] },
//				{ locsMiddlesFadeout[size - 2], locsFadeout[size - 1], locsMiddlesFadeout[size - 1] }
//			);
//
//			SEGMENT_MEMBERS_THIEF;
//
//			lineDefine(size - 1, 0, vertsIn, vertsInS, linesIn, vertsOutS[1], VERT_TYPE::IN, 1);
//			if (isVertsInSTriple) lineDefine(size - 1, 1, vertsIn, vertsInS, linesIn, vertsOutS[0], VERT_TYPE::IN, 1);
//			lineDefine(size - 1, 0, vertsOut, vertsOutS, linesOut, vertsInS[1], VERT_TYPE::OUT, 0);
//			if (isVertsOutSTriple) lineDefine(size - 1, 1, vertsOut, vertsOutS, linesOut, vertsInS[0], VERT_TYPE::OUT, 0);
//		}
//		else {
//			Segment<true> segment = Segment<true>(
//				{ locsMiddles[size], nonCyclicLocEnd },
//				{ locsMiddlesFadeout[size], nonCyclicLocFadeoutEnd }
//			);
//
//			SEGMENT_MEMBERS_THIEF;
//
//			lineDefine(size+1, 0, vertsIn, vertsInS, linesIn, vertsOutS[1], VERT_TYPE::IN, 1);
//			lineDefine(size + 1, 0, vertsOut, vertsOutS, linesOut, vertsInS[1], VERT_TYPE::OUT, 0);
//			lineBetweenDefine(size + 1, 1, 1, vertsIn.size() - 1, vertsOut.size() - 1, linesBetween, vertsInS[0], 0); // 0 coz we doesn't care about exp otherwise.
//		}
//		////
//
//		int vertsOutSizeOffset = vertsIn.size();
//		int vertsInterSizeOffset = vertsOutSizeOffset + vertsOut.size();
//		int vertsSize = vertsInterSizeOffset + vertsInter.size();
//
//		int linesOutSizeOffset = linesIn.size();
//		int linesBetweenSizeOffset = linesOutSizeOffset + linesOut.size();
//		int linesSize = linesBetweenSizeOffset + linesBetween.size();
//
//		int linesMaxSize = 4 * size + (not isCyclic) * 7;
//		int vertsMaxSize = 3 * size + (not isCyclic) * 6;
//
//		int defaultExp = rightestVertType;
//
//		array<float2, vertsMaxSize> verts;
//		verts.reserve(vertsSize);
//		verts.insert(verts.end(), vertsIn.begin(), vertsIn.end());
//		verts.insert(verts.end(), vertsOut.begin(), vertsOut.end());
//		verts.insert(verts.end(), vertsInter.begin(), vertsInter.end());
//
//		int expIndexPerCheck[2 + linesMaxSize + vertsInterMaxSize] = { 0, 1 };
//
//		//// Filling up expIndexPerCheck with lines.
//		for (int i = 0; i < linesIn.size(); i++) {
//			lines[i][0] = linesIn[i].from + (linesIn[i].fromType == VERT_TYPE::INTER) * linesBetweenSizeOffset;
//			lines[i][1] = linesIn[i].to + (linesIn[i].toType == VERT_TYPE::INTER) * linesBetweenSizeOffset;
//			expIndexPerCheck[i + 2] = getProperExp(verts[lines[i][0]], verts[lines[i][1]], linesIn[i].otherVert, linesIn[i].expFits, linesIn[i].expOtherwise);
//		};
//		for (int i = 0; i < linesOut.size(); i++) {
//			int j = i + vertsOutSizeOffset;
//			lines[j][0] = linesOut[i].from + (linesOut[i].fromType == VERT_TYPE::OUT) * vertsOutSizeOffset + (linesOut[i].fromType == VERT_TYPE::INTER) * linesBetweenSizeOffset;
//			lines[j][1] = linesOut[i].to + (linesOut[i].toType == VERT_TYPE::OUT) * vertsOutSizeOffset + (linesOut[i].toType == VERT_TYPE::INTER) * linesBetweenSizeOffset;
//			expIndexPerCheck[j + 2] = getProperExp(verts[lines[j][0]], verts[lines[j][1]], linesIn[j].otherVert, linesIn[j].expFits, linesIn[j].expOtherwise);
//		};
//		for (int i = 0; i < linesBetween.size(); i++) {
//			int j = i + linesBetweenSizeOffset;
//			lines[j][0] = linesBetween[i].from + (linesBetween[i].fromType == VERT_TYPE::OUT) * vertsOutSizeOffset + (linesBetween[i].fromType == VERT_TYPE::INTER) * linesBetweenSizeOffset;
//			lines[j][1] = linesBetween[i].to + (linesBetween[i].toType == VERT_TYPE::OUT) * vertsOutSizeOffset + (linesBetween[i].toType == VERT_TYPE::INTER) * linesBetweenSizeOffset;
//			expIndexPerCheck[j + 2] = getProperExp(verts[lines[j][0]], verts[lines[j][1]], linesIn[j].otherVert, linesIn[j].expFits, linesIn[j].expOtherwise);
//		};
//		////
//
//		//// Filling up expIndexPerCheck with levels.
//		int levelsInterVertsIndices[vertsInter.size()];
//		for (int i = 0; i < vertsInter.size(); i++) {
//			levelsInterVertsIndices[i] = vertsInterSizeOffset + i;
//		}
//
//		// Sorting levels.from lower to higher.
//		for (int c = 0; c < vertsInter.size(); c++) {
//			for (int i = 0; i < vertsInter.size() - c - 1; i++) {
//				int sortTemp = levelsInterVertsIndices[i];
//				bool shouldSwitch = verts[levelsInterVertsIndices[i]] > verts[levelsInterVertsIndices[i + 1]];
//				levelsInterVertsIndices[i] = shouldSwitch ? levelsInterVertsIndices[i + 1] : levelsInterVertsIndices[i];
//				levelsInterVertsIndices[i + 1] = shouldSwitch ? levelsInterVertsIndices[i] : levelsInterVertsIndices[i + 1];
//			}
//		}
//
//		levels_exps = []
//		for i in range(len(levels_inter_verts_indices)) :
//				levels_exps.append(both_exps_per_inter_vert[levels_inter_verts_indices[i]][0])
//
//				default_exp = both_exps_per_inter_vert[levels_inter_verts_indices[-1]][1] if (len(levels_exps) > 0) else default_exp
//	}
//
//private:
//	bool isVertOnLeftOfLine(const float2& lineVert1, const float2& lineVert2, const float2& otherVert) const {
//		float2 fromTo = lineVert1.x < lineVert2.x ? lineVert2 - lineVert1 : lineVert1 - lineVert2;
//		if (fromTo.y > 0.00001) {
//			const float ctan = fromTo.x / fromTo.y;
//			const float mustLayX = ctan * (otherVert.y - lineVert1.y) + lineVert1.x;
//			return otherVert.x < mustLayX;
//		}
//		else return otherVert.x < lineVert1.x;
//	}
//
//	bool isVertHigherThanLine(const float2& lineVert1, const float2& lineVert2, const float2& otherVert) const {
//		float2 fromTo = lineVert1.x < lineVert2.x ? lineVert2 - lineVert1 : lineVert1 - lineVert2;
//		if (fromTo.x > 0.00001) {
//			const float tan = fromTo.y / fromTo.x;
//			const float mustLayY = tan * (otherVert.x - lineVert1.x) + lineVert1.y;
//			return otherVert.y > mustLayY;
//		}
//		else return otherVert.y > lineVert1.y;
//	}
//
//	int getProperExp(const float2& lineVert1, const float2& lineVert2, const float2& otherVert, const int expFits, const int expOtherwise) {
//		return isVertOnLeftOfLine(lineVert1, lineVert2, otherVert) ? expFits : expOtherwise;
//	}
//
//	float2 getIntersectionPoint(float2& from, float2& to) { // With the right wall
//		float2 d = to - from;
//		return float2(1, (d.y / d.x) * (1 - to.x) + to.y);
//	}
//
//	void lineDefine(int i, int k, vector<float2>& vertsRef, array<float2, 3>& vertsSRef, vector<array<line, 2>>& linesRef, float2 otherVert, VERT_TYPE vertType, VERT_TYPE expOtherwise) {
//		line newLine;
//		newLine.otherVert = otherVert;
//		newLine.expFits = i + 2;
//		newLine.expOtherwise = expOtherwise;
//
//		int vertsInterSize = vertsInter.size();
//		int vertsSize = vertsRef.size();
//
//		if ((vertsSRef[k].x > 1) and (vertsSRef[k + 1].x < 1) or (vertsSRef[k].x < 1) and (vertsSRef[k + 1].x > 1)) {
//			vertsInter.push_back(getIntersectionPoint(vertsSRef[k], vertsSRef[k + 1]));
//
//			bool isFromInterToNext = vertsSRef[k + 1].x <= 1;
//
//			if (isFromInterToNext) vertsRef.push_back(vertsSRef[k + 1]);
//			else vertsRef.push_back(vertsSRef[k]);
//
//			newLine.from = isFromInterToNext ? vertsInterSize - 1 : vertsSize - 1;
//			newLine.to = isFromInterToNext ? vertsSize - 1 : vertsInterSize - 1;
//			newLine.fromType = isFromInterToNext ? VERT_TYPE::INTER : vertType;
//			newLine.toType = isFromInterToNext ? vertType : VERT_TYPE::INTER;
//			newLine.fromArrRef = isFromInterToNext ? vertsInter : vertsRef;
//			newLine.toArrRef = isFromInterToNext ? vertsRef : vertsInter;
//
//			bool isOtherVertHigherThanLine = isVertHigherThanLine(newLine.fromArrRef[newLine.from], newLine.toArrRef[newLine.to], otherVert);
//
//			bothExpsPerInterVert.push_back(array<int, 2>{
//				isOtherVertHigherThanLine ? newLine.expOtherwise : newLine.expFits, // Lower
//				isOtherVertHigherThanLine ? newLine.expFits : newLine.expOtherwise // Higher
//			});
//		}
//		else if ((vertsSRef[k].x <= 1) and (vertsSRef[k + 1].x <= 1)) {
//			if (vertsSize == 0) {
//				vertsRef.push_back(vertsSRef[k]);
//
//				bool condition = (vertsSRef[k].x > rightestVertX);
//				rightestVertX = condition ? vertsSRef[k].x : rightestVertX;
//				rightestVertType = condition ? vertType : rightestVertType;
//			}
//
//			vertsRef.push_back(vertsSRef[k + 1]);
//
//			bool condition = (vertsSRef[k + 1].x > rightestVertX);
//			rightestVertX = condition ? vertsSRef[k + 1].x : rightestVertX;
//			rightestVertType = condition ? vertType : rightestVertType;
//
//
//			newLine.from = vertsSize - 2;
//			newLine.to = vertsSize - 1;
//			newLine.fromType = vertType;
//			newLine.toType = vertType;
//			newLine.fromArrRef = vertsRef;
//			newLine.toArrRef = vertsRef;
//		}
//		else return;
//
//		// Horizontal check.
//		if ((vertsSRef[k] - vertsSRef[k + 1]).y == 0) return; // TODO : It still adds the verts.Even if there's no need.
//
//		linesRef.push_back(newLine);
//	}
//
//	void lineBetweenDefine(int i, int iIn, int iOut, int iInReal, int iOutReal, array<float2, 3>& vertsInSRef, array<float2, 3>& vertsOutSRef, vector<array<line, 2>>& linesRef, float2 otherVert, VERT_TYPE expOtherwise) {
//		line newLine;
//		newLine.otherVert = otherVert;
//		newLine.expFits = i + 2;
//		newLine.expOtherwise = expOtherwise;
//
//		int vertsInterSize = vertsInter.size();
//
//		if ((vertsInSRef[iIn].x < 1) and (vertsOutSRef[iOut].x > 1) or (vertsInSRef[iIn].x > 1) and (vertsOutSRef[iOut].x < 1)) {
//			vertsInter.push_back(getIntersectionPoint(vertsInSRef[iIn], vertsOutSRef[iOut]));
//
//			bool isFromInterToNext = vertsOutSRef[iOut].x;
//
//			newLine.from = isFromInterToNext ? vertsInterSize - 1 : iInReal;
//			newLine.to = isFromInterToNext ? iOutReal : vertsInterSize - 1;
//			newLine.fromType = isFromInterToNext ? VERT_TYPE::INTER : VERT_TYPE::IN;
//			newLine.toType = isFromInterToNext ? VERT_TYPE::OUT : VERT_TYPE::INTER;
//			newLine.fromArrRef = isFromInterToNext ? vertsInter : vertsIn;
//			newLine.toArrRef = isFromInterToNext ? vertsOut : vertsInter;
//
//			bool isOtherVertHigherThanLine = isVertHigherThanLine(newLine.fromArrRef[newLine.from], newLine.toArrRef[newLine.to], otherVert);
//
//			bothExpsPerInterVert.push_back(array<int, 2>{
//				isOtherVertHigherThanLine ? newLine.expOtherwise : newLine.expFits, // Lower
//				isOtherVertHigherThanLine ? newLine.expFits : newLine.expOtherwise // Higher
//			});
//		}
//		else if ((vertsInSRef[iIn].x <= 1) and (vertsOutSRef[iOut].x <= 1)) {
//			newLine.from = iInReal;
//			newLine.to = iOutReal;
//			newLine.fromType = VERT_TYPE::IN;
//			newLine.toType = VERT_TYPE::OUT;
//			newLine.fromArrRef = vertsIn;
//			newLine.toArrRef = vertsOut;
//		}
//		else return;
//
//		// Horizontal check.
//		if ((vertsInSRef[iIn] - vertsOutSRef[iOut]).y == 0) return; // TODO : It still adds the verts.Even if there's no need.
//
//		linesRef.push_back(newLine);
//	}
//};