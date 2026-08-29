//#include "pch.h"
#include "shape.h"
#include <iostream>

////
#define SEGMENT_MEMBERS_THIEF \
expressionsSelection.push_back(segment.expressionSelection); \
expressionsCoefficients.push_back(segment.expressionCoefficients); \
array<float2, int(3)> vertsInS = segment.vertsIn; \
array<float2, 3> vertsOutS = segment.vertsOut;
////

template<typename type, int s1, int s2>
void combine2Arrays(array<type, s1 + s2>& toArray, array<type, s1> a1, array<type, s2> a2) {
	for (int i = 0; i < s1; i++) {
		toArray[i] = a1[i];
	}

	for (int i = 0; i < s2; i++) {
		toArray[i + s1] = a2[i];
	}
}

template<typename type, int s1, int s2, int s3>
void combine3Arrays(array<type, s1 + s2 + s3>& toArray, array<type, s1> a1, array<type, s2> a2, array<type, s3> a3) {
	for (int i = 0; i < s1; i++) {
		toArray[i] = a1[i];
	}

	for (int i = 0; i < s2; i++) {
		toArray[i + s1] = a2[i];
	}

	for (int i = 0; i < s3; i++) {
		toArray[i + s1 + s2] = a3[i];
	}
};


Shape::Shape(const PureShape ps) {
	sourcePureShape = ps;

	const int locsSize = ps.locs.size();
	const int locsMiddlesSize = ps.locsMiddles.size();

	// Calculating locs fadeout
	const float2 shift = float2(cos(ps.fadeoutAngle), sin(ps.fadeoutAngle)) * ps.fadeoutLength;
	vector<float2> locsFadeout(locsSize);
	vector<float2> locsMiddlesFadeout(locsMiddlesSize);

	locsMiddlesFadeout[0] = locsMiddlesFadeout[0] + shift;

	//// Fadeout verts define.
	for (int i = 1; i < locsMiddlesSize - ps.isCyclic; i++) {
		locsMiddlesFadeout[i] = ((ps.locsMiddles[i] - ps.locsMiddles[i - 1])* ps.fadeoutScales[i - 1] + locsMiddlesFadeout[i - 1]);
	}

	if (ps.isCyclic) {
		locsFadeout[0] = (ps.locs[0] - ps.locsMiddles[locsSize - 1]) * ps.fadeoutScales[locsSize - 1] + locsMiddlesFadeout[locsSize - 1];
		for (int i = 1; i < locsSize; i++) {
			locsFadeout[i - 1] = (ps.locs[i - 1] - ps.locsMiddles[i]) * ps.fadeoutScales[i] + locsMiddlesFadeout[i];
		};
	}
	else {
		for (int i = 0; i < locsSize; i++) {
			locsFadeout[i] = (ps.locs[i] - ps.locsMiddles[i]) * ps.fadeoutScales[i] + locsMiddlesFadeout[i];
		};
	}

	vector<lineSided> linesIn = {};
	vector<lineSided> linesOut = {};
	vector<lineSided> linesBetween = {};

	float leftestVertX;

	//// Creating segments

	// First segment.
	if (not ps.isCyclic) {
		Segment<false> s = {
			{ (ps.locsMiddles[0] - ps.locs[0]).getNormalized() * 2 + ps.locs[0], ps.locsMiddles[0] },
			{ (locsMiddlesFadeout[0] - locsFadeout[0]).getNormalized() * 2 + locsFadeout[0], locsMiddlesFadeout[0] }
		};

		//SEGMENT_MEMBERS_THIEF;

		lineDefine(s.vertsIn[0], vertsInS[1], &vertsIn, linesIn, vertsOutS[1], VERT_TYPE::IN, 2, 1, leftestVertX, defaultExpressionIndex, true);
		lineDefine(s.vertsOut[0], vertsOutS[1], &vertsOut, linesOut, vertsInS[1], VERT_TYPE::OUT, 2, 0, leftestVertX, defaultExpressionIndex, true);
		lineBetweenDefine(vertsIn.size() - 2, vertsOut.size() - 2, &vertsIn, &vertsOut, linesBetween, vertsInS[1], 2, locsSize + 1);
		lineBetweenDefine(vertsIn.size() - 1, vertsOut.size() - 1, &vertsIn, &vertsOut, linesBetween, vertsInS[0], 2, 3);
	}

	// Arc segments
	for (uint8_t arcIndex = not ps.isCyclic; arcIndex < locsSize + (not ps.isCyclic); arcIndex++) {
		Segment<true> segment = Segment<true>(
			{ ps.locsMiddles[arcIndex - 1], ps.locs[arcIndex - (not ps.isCyclic)], ps.locsMiddles[arcIndex] },
			{ locsMiddlesFadeout[arcIndex - 1], locsFadeout[arcIndex - (not ps.isCyclic)], locsMiddlesFadeout[arcIndex] }
		);

		SEGMENT_MEMBERS_THIEF;

		bool isVertsInSTriple = segment.isVertsInTriple;
		bool isVertsOutSTriple = segment.isVertsOutTriple;

		// Defining lines.
		lineDefine(vertsInS[0], vertsInS[1], &vertsIn, linesIn, vertsOutS[1], VERT_TYPE::IN, arcIndex + 2, 0, leftestVertX, defaultExpressionIndex, arcIndex == 0);
		if (isVertsInSTriple) lineDefine(vertsInS[1], vertsInS[2], &vertsIn, linesIn, vertsOutS[0], VERT_TYPE::IN, arcIndex + 2, 0, leftestVertX, defaultExpressionIndex, arcIndex == 0);

		lineDefine(vertsOutS[0], vertsOutS[1], &vertsOut, linesOut, vertsInS[1], VERT_TYPE::OUT, arcIndex + 2, 1, leftestVertX, defaultExpressionIndex, arcIndex == 0);
		if (isVertsOutSTriple) lineDefine(vertsOutS[1], vertsOutS[2], &vertsOut, linesOut, vertsInS[0], VERT_TYPE::OUT, arcIndex + 2, 1, leftestVertX, defaultExpressionIndex, arcIndex == 0);

		lineBetweenDefine(vertsIn.size() - 1, vertsOut.size() - 1, *vertsIn, *vertsOut, linesBetween,
			(isVertsInSTriple ? vertsInS : vertsOutS)[1],
			arcIndex + 2, arcIndex + 3);
	}

	// Last segment.
	if constexpr (not ps.isCyclic) {
		Segment<true> segment = Segment<true>(
			{ ps.locsMiddles[locsMiddlesSize - 1], (ps.locsMiddles[-1] - ps.locs[-1]).getNormalized() * 2 + ps.locs[locsSize - 1] },
			{ locsMiddlesFadeout[locsMiddlesSize - 1], (locsMiddlesFadeout[-1] - locsFadeout[-1]).getNormalized() * 2 + locsFadeout[locsSize - 1] }
		);

		SEGMENT_MEMBERS_THIEF;

		lineDefine(vertsInS[0], vertsInS[1], &vertsIn, linesIn, vertsOutS[1], VERT_TYPE::IN, locsSize + 3, 0, leftestVertX, defaultExpressionIndex);
		lineDefine(vertsOutS[0], vertsOutS[1], &vertsOut, linesOut, vertsInS[1], VERT_TYPE::OUT, locsSize + 3, 1, leftestVertX, defaultExpressionIndex);
		lineBetweenDefine(vertsIn.size() - 1, vertsOut.size() - 1, *vertsIn, *vertsOut, linesBetween, vertsInS[0], locsSize + 3, locsSize + 2); // 0 coz we doesn't care about exp otherwise.
	}
	////

	// If it's not then u're an idiot :)
	vertsSize = 3 * locsSize + (not ps.isCyclic) * 6;
	linesSize = 4 * locsSize + (not ps.isCyclic) * 7;
	expressionSize = locsSize + 2 + (not ps.isCyclic) * 2;

	array<float2, vertsSize> verts;
	combine2Arrays<float2, vertsIn.size(), vertsOut.size()>(verts, vertsIn, vertsOut);

	// TODO: Rewrite me.
	array<lineSided, linesSize> linesRouglyGlued;
	combine3Arrays<lineSided, linesIn.size(), linesOut.size(), linesBetween.size()>(linesRouglyGlued, linesIn, linesOut, linesBetween);

	array<line<int>, linesSize> lines;
	array<int, linesSize> expressionIndexPerLine;

	for (int i = 0; i < linesSize; i++) {
		lines[i] = {
			.from = linesRouglyGlued[i].from + (linesRouglyGlued[i].fromType == VERT_TYPE::OUT) * vertsIn.size(),
			.to = linesRouglyGlued[i].to + (linesRouglyGlued[i].toType == VERT_TYPE::OUT) * vertsIn.size()
		};

		expressionIndexPerLine[i] = getProperExp(verts[lines[i].from], verts[lines[i].to],
			linesRouglyGlued[i].sideVert, linesRouglyGlued[i].expressionIndexFit, linesRouglyGlued[i].expressionIndexOtherwise);
	};

	cout << "expressionIndexPerLine" << endl;
	for (int i = 0; i < linesSize; i++) {
		cout << i << ". \t" << expressionIndexPerLine[i] << endl;
	}
	
	cout << "expressionsCoefficients" << endl;
	for (int i = 0; i < expressionSize; i++) {
		cout << i << ". \t";
		for (int j = 0; j < 10; j++) cout << expressionsCoefficients[i][j] << " \t";
		cout << endl;
	}

	cout << "expressionsSelection" << endl;
	for (int i = 0; i < expressionSize; i++) {
		cout << i << ". \t";
		for (int j = 0; j < 10; j++) cout << expressionsSelection[i][j] << " \t";
		cout << endl;
	}
};


bool Shape::isVertOnLeftOfLine(const float2& lineVert1, const float2& lineVert2, const float2& sideVert) const {
	float2 fromTo = lineVert1.x < lineVert2.x ? lineVert2 - lineVert1 : lineVert1 - lineVert2;
	if (fromTo.y > 0.00001) {
		const float ctan = fromTo.x / fromTo.y;
		const float mustLayX = ctan * (sideVert.y - lineVert1.y) + lineVert1.x;
		return sideVert.x < mustLayX;
	}
	else return sideVert.x < lineVert1.x;
}


bool Shape::isVertHigherThanLine(const float2& lineVert1, const float2& lineVert2, const float2& sideVert) const {
	float2 fromTo = lineVert1.x < lineVert2.x ? lineVert2 - lineVert1 : lineVert1 - lineVert2;
	if (fromTo.x > 0.00001) {
		const float tan = fromTo.y / fromTo.x;
		const float mustLayY = tan * (sideVert.x - lineVert1.x) + lineVert1.y;
		return sideVert.y > mustLayY;
	}
	else return sideVert.y > lineVert1.y;
}


int Shape::getProperExp(const float2& lineVert1, const float2& lineVert2, const float2& sideVert, const int expressionIndexFit, const int expressionIndexOtherwise) {
	return isVertOnLeftOfLine(lineVert1, lineVert2, sideVert) ? expressionIndexFit : expressionIndexOtherwise;
}

void Shape::lineDefine(
	float2& vert1,
	float2& vert2,
	vector<float2>* vertsPtr,
	vector<lineSided>& lines,
	float2 sideVert,
	VERT_TYPE vertType,
	int expressionIndexFit,
	int expressionIndexOtherwise,
	float& leftestVertX,
	bool& defaultExpressionIndex,
	bool isFirstSegment
) {
	int vertsSize = (*vertsPtr).size();

	lineSided newLine = {
		.from = vertsSize - 2,
		.to = vertsSize - 1,
		.fromType = vertType,
		.toType = vertType,
		.fromArrPtr = vertsPtr,
		.toArrPtr = vertsPtr,
		.sideVert = sideVert,
		.expressionIndexFit = expressionIndexFit,
		.expressionIndexOtherwise = expressionIndexOtherwise
	};

	if (isFirstSegment) (*vertsPtr).push_back(vert1);
	(*vertsPtr).push_back(vert2);

	if (vert2.x < leftestVertX) {
		leftestVertX = vert2.x;
		defaultExpressionIndex = vertType == VERT_TYPE::IN ? 1 : 0;
	}

	lines.push_back(newLine);
}


void Shape::lineBetweenDefine(
	int indexIn,
	int indexOut,
	vector<float2>* vertsInPtr,
	vector<float2>* vertsOutPtr,
	vector<lineSided>& lines,
	float2 sideVert,
	VERT_TYPE expressionIndexFit,
	VERT_TYPE expressionIndexOtherwise
) {
	lineSided newLine;

	newLine.from = indexIn;
	newLine.to = indexOut;
	newLine.fromType = VERT_TYPE::IN;
	newLine.toType = VERT_TYPE::OUT;
	newLine.fromArrPtr = vertsInPtr;
	newLine.toArrPtr = vertsOutPtr;
	newLine.sideVert = sideVert;
	newLine.expressionIndexFit = expressionIndexFit;
	newLine.expressionIndexOtherwise = expressionIndexOtherwise;

	lines.push_back(newLine);
}