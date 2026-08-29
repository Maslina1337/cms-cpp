//#include "pch.h"
#include "shape.h"

//template<typename type, int s1, int s2>
//void combine2Arrays(array<type, s1 + s2>& toArray, array<type, s1> a1, array<type, s2> a2) {
//	for (int i = 0; i < s1; i++) {
//		toArray[i] = a1[i];
//	}
//
//	for (int i = 0; i < s2; i++) {
//		toArray[i + s1] = a2[i];
//	}
//}
//
//template<typename type, int s1, int s2, int s3>
//void combine3Arrays(array<type, s1 + s2 + s3>& toArray, array<type, s1> a1, array<type, s2> a2, array<type, s3> a3) {
//	for (int i = 0; i < s1; i++) {
//		toArray[i] = a1[i];
//	}
//
//	for (int i = 0; i < s2; i++) {
//		toArray[i + s1] = a2[i];
//	}
//
//	for (int i = 0; i < s3; i++) {
//		toArray[i + s1 + s2] = a3[i];
//	}
//};


Shape::Shape(PureShape ps) {
	sourcePureShape = ps;

	const uint8_t locsSize = ps.locs.size();
	const uint8_t locsMiddlesSize = ps.locsMiddles.size();

	// Calculating locs fadeout
	const float2 shift = float2(cos(ps.fadeoutAngle), sin(ps.fadeoutAngle)) * ps.fadeoutLength;
	vector<float2> locsFadeout(locsSize);
	vector<float2> locsMiddlesFadeout(locsMiddlesSize);

	locsMiddlesFadeout[0] = locsMiddlesFadeout[0] + shift;

	//// Fadeout verts define.
	for (uint8_t i = 1; i < locsMiddlesSize - ps.isCyclic; i++) {
		locsMiddlesFadeout[i] = ((ps.locsMiddles[i] - ps.locsMiddles[i - 1])* ps.fadeoutScales[i - 1] + locsMiddlesFadeout[i - 1]);
	}

	if (ps.isCyclic) {
		locsFadeout[0] = (ps.locs[0] - ps.locsMiddles[locsSize - 1]) * ps.fadeoutScales[locsSize - 1] + locsMiddlesFadeout[locsSize - 1];
		for (uint8_t i = 1; i < locsSize; i++) {
			locsFadeout[i - 1] = (ps.locs[i - 1] - ps.locsMiddles[i]) * ps.fadeoutScales[i] + locsMiddlesFadeout[i];
		};
	}
	else {
		for (uint8_t i = 0; i < locsSize; i++) {
			locsFadeout[i] = (ps.locs[i] - ps.locsMiddles[i]) * ps.fadeoutScales[i] + locsMiddlesFadeout[i];
		};
	}

	float leftestVertX;

	//// Creating segments

	// First segment.
	if (not ps.isCyclic) {
		float2 v[2] = { (ps.locsMiddles[0] - ps.locs[0]).getNormalized() * 2 + ps.locs[0], ps.locsMiddles[0] };
		float2 vf[2] = { (locsMiddlesFadeout[0] - locsFadeout[0]).getNormalized() * 2 + locsFadeout[0], locsMiddlesFadeout[0] };
		Segment<false> s (v, vf);

		lineDefine(s.vertsIn[0], s.vertsIn[1], &vertsIn, linesIn, s.vertsOut[1], VERT_TYPE::IN, 2, 1, leftestVertX, defaultExpressionIndex, true);
		lineDefine(s.vertsOut[0], s.vertsOut[1], &vertsOut, linesOut, s.vertsIn[1], VERT_TYPE::OUT, 2, 0, leftestVertX, defaultExpressionIndex, true);
		lineBetweenDefine(vertsIn.size() - 2, vertsOut.size() - 2, &vertsIn, &vertsOut, linesBetween, s.vertsIn[1], 2, locsSize + 1);
		lineBetweenDefine(vertsIn.size() - 1, vertsOut.size() - 1, &vertsIn, &vertsOut, linesBetween, s.vertsIn[0], 2, 3);
	}

	// Arc segments
	for (uint8_t arcIndex = not ps.isCyclic; arcIndex < locsSize + (not ps.isCyclic); arcIndex++) {
		float2 v[3] = { ps.locsMiddles[arcIndex - 1], ps.locs[arcIndex - (not ps.isCyclic)], ps.locsMiddles[arcIndex] };
		float2 vf[3] = { locsMiddlesFadeout[arcIndex - 1], locsFadeout[arcIndex - (not ps.isCyclic)], locsMiddlesFadeout[arcIndex] };
		Segment<true> s (v, vf);

		// Defining lines.
		lineDefine(s.vertsIn[0], s.vertsIn[1], &vertsIn, linesIn, s.vertsOut[1], VERT_TYPE::IN, arcIndex + 2, 0, leftestVertX, defaultExpressionIndex, arcIndex == 0);
		if (s.isVertsInTriple) lineDefine(s.vertsIn[1], s.vertsIn[2], &vertsIn, linesIn, s.vertsOut[0], VERT_TYPE::IN, arcIndex + 2, 0, leftestVertX, defaultExpressionIndex, arcIndex == 0);

		lineDefine(s.vertsOut[0], s.vertsOut[1], &vertsOut, linesOut, s.vertsIn[1], VERT_TYPE::OUT, arcIndex + 2, 1, leftestVertX, defaultExpressionIndex, arcIndex == 0);
		if (s.isVertsOutTriple) lineDefine(s.vertsOut[1], s.vertsOut[2], &vertsOut, linesOut, s.vertsIn[0], VERT_TYPE::OUT, arcIndex + 2, 1, leftestVertX, defaultExpressionIndex, arcIndex == 0);

		lineBetweenDefine(vertsIn.size() - 1, vertsOut.size() - 1, &vertsIn, &vertsOut, linesBetween,
			(s.isVertsInTriple ? s.vertsIn : s.vertsOut)[1],
			arcIndex + 2, arcIndex + 3);
	}

	// Last segment.
	if (not ps.isCyclic) {
		float2 v[2] = { ps.locsMiddles[locsMiddlesSize - 1], (ps.locsMiddles[-1] - ps.locs[-1]).getNormalized() * 2 + ps.locs[locsSize - 1] };
		float2 vf[2] = { locsMiddlesFadeout[locsMiddlesSize - 1], (locsMiddlesFadeout[-1] - locsFadeout[-1]).getNormalized() * 2 + locsFadeout[locsSize - 1] };
		Segment<false> s (v, vf);

		lineDefine(s.vertsIn[0], s.vertsIn[1], &vertsIn, linesIn, s.vertsOut[1], VERT_TYPE::IN, locsSize + 3, 0, leftestVertX, defaultExpressionIndex);
		lineDefine(s.vertsOut[0], s.vertsOut[1], &vertsOut, linesOut, s.vertsIn[1], VERT_TYPE::OUT, locsSize + 3, 1, leftestVertX, defaultExpressionIndex);
		lineBetweenDefine(vertsIn.size() - 1, vertsOut.size() - 1, &vertsIn, &vertsOut, linesBetween, s.vertsIn[0], locsSize + 3, locsSize + 2); // 0 coz we doesn't care about exp otherwise.
	}
	////

	// If it's not then u're an idiot :)
	vertsSize = 3 * locsSize + (not ps.isCyclic) * 6;
	linesSize = 4 * locsSize + (not ps.isCyclic) * 7;
	expressionSize = locsSize + 2 + (not ps.isCyclic) * 2;

	if (vertsIn.size() + vertsOut.size() != vertsSize) cout << "PIZDA" << endl;
	//if (linesIn.size() + linesOut.size() + linesBetween.size() != linesSize) cout << "PIZDA" << endl;

	const int a = locsSize;

	vector<float2> verts = vertsIn;
	verts.reserve(vertsSize);
	verts.insert(verts.end(), vertsOut.begin(), vertsOut.end());

	vector<lineSided> linesRouglyGlued = linesIn;
	linesRouglyGlued.reserve(linesSize);
	linesRouglyGlued.insert(linesRouglyGlued.end(), linesOut.begin(), linesOut.end());
	linesRouglyGlued.insert(linesRouglyGlued.end(), linesBetween.begin(), linesBetween.end());

	vector<lineExpressioned> lines;
	lines.resize(linesSize);

	for (int i = 0; i < linesSize; i++) {
		lines[i] = {
			.from = linesRouglyGlued[i].from + (linesRouglyGlued[i].fromType == VERT_TYPE::OUT) * int(vertsIn.size()),
			.to = linesRouglyGlued[i].to + (linesRouglyGlued[i].toType == VERT_TYPE::OUT) * int(vertsIn.size()),
			.expressionIndex = getProperExp(verts[lines[i].from], verts[lines[i].to],
			linesRouglyGlued[i].sideVert, linesRouglyGlued[i].expressionIndexFit, linesRouglyGlued[i].expressionIndexOtherwise)
		};
	};
	
	cout << "expressionsCoefficients" << endl;
	for (uint8_t i = 0; i < expressionSize; i++) {
		cout << i << ". \t";
		for (int j = 0; j < 10; j++) cout << expressionsCoefficients[i][j] << " \t";
		cout << endl;
	}

	cout << "expressionsSelection" << endl;
	for (uint8_t i = 0; i < expressionSize; i++) {
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


uint8_t Shape::getProperExp(const float2& lineVert1, const float2& lineVert2, const float2& sideVert, const int expressionIndexFit, const int expressionIndexOtherwise) {
	return isVertOnLeftOfLine(lineVert1, lineVert2, sideVert) ? expressionIndexFit : expressionIndexOtherwise;
}

void Shape::lineDefine(
	float2& vert1,
	float2& vert2,
	vector<float2>* vertsPtr,
	vector<lineSided>& lines,
	float2 sideVert,
	VERT_TYPE vertType,
	uint8_t expressionIndexFit,
	uint8_t expressionIndexOtherwise,
	float& leftestVertX,
	bool& defaultExpressionIndex,
	bool isFirstSegment
) {
	uint8_t vertsSize = (*vertsPtr).size();

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
	uint8_t indexIn,
	uint8_t indexOut,
	vector<float2>* vertsInPtr,
	vector<float2>* vertsOutPtr,
	vector<lineSided>& lines,
	float2 sideVert,
	uint8_t expressionIndexFit,
	uint8_t expressionIndexOtherwise
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