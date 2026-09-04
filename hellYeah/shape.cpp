#include "shape.h"

Shape::Shape(PureShape ps, float* expressionsCoefficientsPtr, float* expressionsSelectionPtr, int& segmentsCompleted) {
	sourcePureShape = ps;

	// If it's not then u're an idiot :)
	int vertsSize = shapeSizesPerShapeIndex[ps.index].verts;
	int linesSize = shapeSizesPerShapeIndex[ps.index].lines;
	int expressionSize = shapeSizesPerShapeIndex[ps.index].expressions;

	const int locsSize = ps.locs.size();
	const int locsMiddlesSize = ps.locsMiddles.size();

	// Calculating locs fadeout
	const float2 shift = float2(cos(ps.fadeoutAngle), sin(ps.fadeoutAngle)) * ps.fadeoutLength;
	vector<float2> locsFadeout(locsSize);
	vector<float2> locsMiddlesFadeout(locsMiddlesSize);

	locsMiddlesFadeout[0] = ps.locsMiddles[0] + shift;

	//// Fadeout verts define.
	for (int i = 1; i < locsSize - ps.isCyclic + 1; i++) {
		locsMiddlesFadeout[i] = ((ps.locsMiddles[i] - ps.locsMiddles[i - 1])* ps.fadeoutScales[i - 1] + locsMiddlesFadeout[i - 1]);
	}

	if (ps.isCyclic) {
		for (int i = 0; i < locsSize; i++) {
			int j = (i - 1 + locsSize) % locsSize;
			locsFadeout[i] = (ps.locs[i] - ps.locsMiddles[j]) * ps.fadeoutScales[j] + locsMiddlesFadeout[j];
		};
	}
	else {
		for (int i = 0; i < locsSize; i++) {
			locsFadeout[i] = (ps.locs[i] - ps.locsMiddles[i]) * ps.fadeoutScales[i] + locsMiddlesFadeout[i];
		};
	}

	//cout << endl << "LOCS" << endl;
	//for (int i = 0; i < ps.locs.size(); i++) {
	//	cout << ps.locs[i].getString() << endl;
	//}
	//cout << endl << "LOCS MIDDLES" << endl;
	//for (int i = 0; i < ps.locsMiddles.size(); i++) {
	//	cout << ps.locsMiddles[i].getString() << endl;
	//}

	//cout << endl << "FADEOUT" << endl;
	//for (int i = 0; i < locsSize; i++) {
	//	cout << locsFadeout[i].getString() << endl;
	//}

	//cout << endl << "FADEOUT MIDDLE" << endl;
	//for (int i = 0; i < locsMiddlesSize; i++) {
	//	cout << locsMiddlesFadeout[i].getString() << endl;
	//}

	float leftestVertX;

	vector<float2> vertsIn;
	vector<float2> vertsOut;

	vector<lineSided> linesIn;
	vector<lineSided> linesOut;
	vector<lineSided> linesBetween;

	bool defaultExpressionIndex = 0;

	// First segment.
	if (not ps.isCyclic) {
		float2 v[2] = { (ps.locsMiddles[0] - ps.locs[0]).getNormalized() * 2 + ps.locs[0], ps.locsMiddles[0] };
		float2 vf[2] = { (locsMiddlesFadeout[0] - locsFadeout[0]).getNormalized() * 2 + locsFadeout[0], locsMiddlesFadeout[0] };
		Segment<false> s (v, vf, expressionsCoefficientsPtr, expressionsSelectionPtr, segmentsCompleted);

		vertsIn.push_back(s.vertsIn[0]);
		vertsOut.push_back(s.vertsOut[0]);

		lineDefine(s.vertsIn[1], &vertsIn, linesIn, s.vertsOut[1], VERT_TYPE::IN, 2, 1, leftestVertX, defaultExpressionIndex);
		lineDefine(s.vertsOut[1], &vertsOut, linesOut, s.vertsIn[1], VERT_TYPE::OUT, 2, 0, leftestVertX, defaultExpressionIndex);
		lineBetweenDefine(vertsIn.size() - 2, vertsOut.size() - 2, &vertsIn, &vertsOut, linesBetween, s.vertsIn[1], 2, locsSize + 1);
		lineBetweenDefine(vertsIn.size() - 1, vertsOut.size() - 1, &vertsIn, &vertsOut, linesBetween, s.vertsIn[0], 2, 3);
	}
	// Arc segments
	for (int arcIndex = not ps.isCyclic; arcIndex < locsSize + (not ps.isCyclic); arcIndex++) {
		int j = (arcIndex - 1 + locsSize) % locsSize;
		float2 v[3] = { ps.locsMiddles[j], ps.locs[arcIndex - (not ps.isCyclic)], ps.locsMiddles[arcIndex] };
		float2 vf[3] = { locsMiddlesFadeout[j], locsFadeout[arcIndex - (not ps.isCyclic)], locsMiddlesFadeout[arcIndex] };
		Segment<true> s(v, vf, expressionsCoefficientsPtr, expressionsSelectionPtr, segmentsCompleted);

		// Defining lines.
		lineDefine(s.vertsIn[1], &vertsIn, linesIn, s.vertsOut[1], VERT_TYPE::IN, arcIndex + 2, 0, leftestVertX, defaultExpressionIndex);
		if (s.isVertsInTriple) lineDefine(s.vertsIn[2], &vertsIn, linesIn, s.vertsOut[0], VERT_TYPE::IN, arcIndex + 2, 0, leftestVertX, defaultExpressionIndex);
		
		lineDefine(s.vertsOut[1], &vertsOut, linesOut, s.vertsIn[1], VERT_TYPE::OUT, arcIndex + 2, 1, leftestVertX, defaultExpressionIndex);
		if (s.isVertsOutTriple) lineDefine(s.vertsOut[2], &vertsOut, linesOut, s.vertsIn[0], VERT_TYPE::OUT, arcIndex + 2, 1, leftestVertX, defaultExpressionIndex);

		lineBetweenDefine(vertsIn.size() - 1, vertsOut.size() - 1, &vertsIn, &vertsOut, linesBetween,
			(s.isVertsInTriple ? s.vertsIn : s.vertsOut)[1],
			arcIndex + 2, arcIndex + 3);
	}

	// Last segment.
	if (not ps.isCyclic) {
		float2 v[2] = { ps.locsMiddles[locsMiddlesSize - 1], (ps.locsMiddles[locsMiddlesSize - 1] - ps.locs[locsSize - 1]).getNormalized() * 2 + ps.locs[locsSize - 1] };
		float2 vf[2] = { locsMiddlesFadeout[locsMiddlesSize - 1], (locsMiddlesFadeout[locsMiddlesSize - 1] - locsFadeout[locsSize - 1]).getNormalized() * 2 + locsFadeout[locsSize - 1] };
		Segment<false> s(v, vf, expressionsCoefficientsPtr, expressionsSelectionPtr, segmentsCompleted);

		lineDefine(s.vertsIn[1], &vertsIn, linesIn, s.vertsOut[1], VERT_TYPE::IN, locsSize + 3, 0, leftestVertX, defaultExpressionIndex);
		lineDefine(s.vertsOut[1], &vertsOut, linesOut, s.vertsIn[1], VERT_TYPE::OUT, locsSize + 3, 1, leftestVertX, defaultExpressionIndex);
		lineBetweenDefine(vertsIn.size() - 1, vertsOut.size() - 1, &vertsIn, &vertsOut, linesBetween, s.vertsIn[0], locsSize + 3, locsSize + 2);
	}

	if (ps.isCyclic) {
		// Fixing the wrong index of first added lines.
		linesIn[0].from = vertsIn.size() - 1;
		linesOut[0].from = vertsOut.size() - 1;

		// Flipping default. TODO: Discover why it's flipped.
		defaultExpressionIndex = 1 - defaultExpressionIndex;
	}

	if (vertsIn.size() + vertsOut.size() != vertsSize) cout << "PIZDA V " << vertsIn.size() << " " << vertsOut.size() << " " << vertsSize << endl;
	if (linesIn.size() + linesOut.size() + linesBetween.size() != linesSize) cout << "PIZDA L " << linesIn.size() << " " << linesOut.size() << " " << linesBetween.size() << " " << linesSize << endl;

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
			.from = linesRouglyGlued[i].from + (linesRouglyGlued[i].fromType == VERT_TYPE::OUT) * static_cast<int>(vertsIn.size()),
			.to = linesRouglyGlued[i].to + (linesRouglyGlued[i].toType == VERT_TYPE::OUT) * static_cast<int>(vertsIn.size()),
			.expressionIndex = getProperExp(verts[lines[i].from], verts[lines[i].to],
			linesRouglyGlued[i].sideVert, linesRouglyGlued[i].expressionIndexFit, linesRouglyGlued[i].expressionIndexOtherwise)
		};
	};
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
	float2& vert2,
	vector<float2>* vertsPtr,
	vector<lineSided>& lines,
	float2 sideVert,
	VERT_TYPE vertType,
	int expressionIndexFit,
	int expressionIndexOtherwise,
	float& leftestVertX,
	bool& defaultExpressionIndex
) {
	int vertsSize = vertsPtr->size();

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

	//if (isFirstSegment) vertsPtr->push_back(vert1);
	vertsPtr->push_back(vert2);

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
	int expressionIndexFit,
	int expressionIndexOtherwise
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