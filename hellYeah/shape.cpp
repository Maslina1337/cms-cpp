#include "shape.h"

Shape::Shape(PureShape ps, float* vertsPtr, float* linesPtr, float* expressionsCoefficientsPtr, float* expressionsSelectionsPtr, float* borderPerShapePtr, int& segmentsCompleted, bool debug) {
	sourcePureShape = ps;

	this->vertsPtr = vertsPtr;
	this->linesPtr = linesPtr;

	// If it's not then u're an idiot :)
	vertsSize = shapeSizesPerShapeIndex[ps.index].verts;
	linesSize = shapeSizesPerShapeIndex[ps.index].lines;
	expressionSize = shapeSizesPerShapeIndex[ps.index].expressions;
	vertsPrevSize = shapeSizesPerShapeIndex[ps.index].vertsPrev;
	linesPrevSize = shapeSizesPerShapeIndex[ps.index].linesPrev;
	expressionPrevSize = shapeSizesPerShapeIndex[ps.index].expressionsPrev;

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

	if (debug) {
		cout << "For shape " << shapesNames[ps.index] << endl; 
		cout << endl << "LOCS" << endl;
		for (int i = 0; i < ps.locs.size(); i++) {
			cout << ps.locs[i].getString() << endl;
		}
		cout << endl << "LOCS MIDDLES" << endl;
		for (int i = 0; i < ps.locsMiddles.size(); i++) {
			cout << ps.locsMiddles[i].getString() << endl;
		}

		cout << endl << "FADEOUT" << endl;
		for (int i = 0; i < locsSize; i++) {
			cout << locsFadeout[i].getString() << endl;
		}

		cout << endl << "FADEOUT MIDDLE" << endl;
		for (int i = 0; i < locsMiddlesSize; i++) {
			cout << locsMiddlesFadeout[i].getString() << endl;
		}
	}

	float leftestVertX;

	// The behaviour may be unexpected if start and end is equal.
	border rightBorder = { .bottom = 0.f, .top = 1.f, .expressionIndex = 0 };

	// First segment.
	if (not ps.isCyclic) {
		float2 v[2] = { (ps.locsMiddles[0] - ps.locs[0]).getNormalized() * 2 + ps.locs[0], ps.locsMiddles[0] };
		float2 vf[2] = { (locsMiddlesFadeout[0] - locsFadeout[0]).getNormalized() * 2 + locsFadeout[0], locsMiddlesFadeout[0] };
		Segment<false> s(v, vf, expressionsCoefficientsPtr, expressionsSelectionsPtr, segmentsCompleted);

		vertsIn.push_back(s.vertsIn[0]);
		vertsOut.push_back(s.vertsOut[0]);

		lineDefine(s.vertsIn[1], &vertsIn, linesIn, s.vertsOut[1], VERT_TYPE::IN, 2, 1, leftestVertX, rightBorder.expressionIndex);
		lineDefine(s.vertsOut[1], &vertsOut, linesOut, s.vertsIn[1], VERT_TYPE::OUT, 2, 0, leftestVertX, rightBorder.expressionIndex);
		lineBetweenDefine(vertsIn.size() - 2, vertsOut.size() - 2, &vertsIn, &vertsOut, linesBetween, s.vertsIn[1], 2, locsSize + 1);
		lineBetweenDefine(vertsIn.size() - 1, vertsOut.size() - 1, &vertsIn, &vertsOut, linesBetween, s.vertsIn[0], 2, 3);
	}
	// Arc segments
	for (int arcIndex = not ps.isCyclic; arcIndex < locsSize + (not ps.isCyclic); arcIndex++) {
		int j = (arcIndex - 1 + locsSize) % locsSize;
		float2 v[3] = { ps.locsMiddles[j], ps.locs[arcIndex - (not ps.isCyclic)], ps.locsMiddles[arcIndex] };
		float2 vf[3] = { locsMiddlesFadeout[j], locsFadeout[arcIndex - (not ps.isCyclic)], locsMiddlesFadeout[arcIndex] };
		Segment<true> s(v, vf, expressionsCoefficientsPtr, expressionsSelectionsPtr, segmentsCompleted);

		// Defining lines.
		lineDefine(s.vertsIn[1], &vertsIn, linesIn, s.vertsOut[1], VERT_TYPE::IN, arcIndex + 2, 1, leftestVertX, rightBorder.expressionIndex);
		if (s.isVertsInTriple) lineDefine(s.vertsIn[2], &vertsIn, linesIn, s.vertsOut[0], VERT_TYPE::IN, arcIndex + 2, 1, leftestVertX, rightBorder.expressionIndex);
		
		lineDefine(s.vertsOut[1], &vertsOut, linesOut, s.vertsIn[1], VERT_TYPE::OUT, arcIndex + 2, 0, leftestVertX, rightBorder.expressionIndex);
		if (s.isVertsOutTriple) lineDefine(s.vertsOut[2], &vertsOut, linesOut, s.vertsIn[0], VERT_TYPE::OUT, arcIndex + 2, 0, leftestVertX, rightBorder.expressionIndex);

		lineBetweenDefine(vertsIn.size() - 1, vertsOut.size() - 1, &vertsIn, &vertsOut, linesBetween,
			(s.isVertsInTriple ? s.vertsIn : s.vertsOut)[1],
			arcIndex + 2, arcIndex + 3);
	}

	// Last segment.
	if (not ps.isCyclic) {
		float2 v[2] = { ps.locsMiddles[locsMiddlesSize - 1], (ps.locsMiddles[locsMiddlesSize - 1] - ps.locs[locsSize - 1]).getNormalized() * 2 + ps.locs[locsSize - 1] };
		float2 vf[2] = { locsMiddlesFadeout[locsMiddlesSize - 1], (locsMiddlesFadeout[locsMiddlesSize - 1] - locsFadeout[locsSize - 1]).getNormalized() * 2 + locsFadeout[locsSize - 1] };
		Segment<false> s(v, vf, expressionsCoefficientsPtr, expressionsSelectionsPtr, segmentsCompleted);

		lineDefine(s.vertsIn[1], &vertsIn, linesIn, s.vertsOut[1], VERT_TYPE::IN, locsSize + 3, 1, leftestVertX, rightBorder.expressionIndex);
		lineDefine(s.vertsOut[1], &vertsOut, linesOut, s.vertsIn[1], VERT_TYPE::OUT, locsSize + 3, 0, leftestVertX, rightBorder.expressionIndex);
		lineBetweenDefine(vertsIn.size() - 1, vertsOut.size() - 1, &vertsIn, &vertsOut, linesBetween, s.vertsIn[0], locsSize + 3, locsSize + 2);
	}

	if (ps.isCyclic) {
		// Fixing the wrong index of first added lines.
		 linesIn[0].from = static_cast<int>(vertsIn.size()) - 1;
		 linesOut[0].from = static_cast<int>(vertsOut.size()) - 1;
	}
	else {
		//float2 eIn00 = vertsIn[0];
		//float2 eIn01 = vertsIn[1];

		//float2 eIn10 = vertsIn[vertsIn.size() - 1];
		//float2 eIn11 = vertsIn[vertsIn.size() - 2];

		//float2 eIn0 = eIn00 - eIn01;
		//float2 eIn1 = eIn10 - eIn11;

		//// Is both ends intersect the right wall?
		//if (eIn0.x > 0 and eIn1.x > 0) {
		//	float2 eOut00 = vertsOut[0];
		//	float2 eOut01 = vertsOut[1];

		//	float2 eOut10 = vertsOut[vertsOut.size() - 1];
		//	float2 eOut11 = vertsOut[vertsOut.size() - 2];

		//	float2 eOut0 = eOut00 - eOut01;
		//	float2 eOut1 = eOut10 - eOut11;

		//	float2 eIn0Intersect = float2::getIntersectionPoint(eIn00, eIn01, float2(1, 0), float2(1, 1));
		//	float2 eIn1Intersect = float2::getIntersectionPoint(eIn10, eIn11, float2(1, 0), float2(1, 1));

		//	float2 eOut0Intersect = float2::getIntersectionPoint(eOut00, eOut01, float2(1, 0), float2(1, 1));
		//	float2 eOut1Intersect = float2::getIntersectionPoint(eOut10, eOut11, float2(1, 0), float2(1, 1));

		//	// Is IN intersects closer to each other than the OUT intersects
		//	if ((eIn0Intersect - eIn1Intersect).getLength() < (eOut0Intersect - eOut1Intersect).getLength()) {
		//		rightBorder.start = eIn0Intersect.y;
		//		rightBorder.end = eIn1Intersect.y;
		//		rightBorder.expressionIndex = 1;
		//	}
		//	else {
		//		rightBorder.start = eOut0Intersect.y;
		//		rightBorder.end = eOut1Intersect.y;
		//		rightBorder.expressionIndex = 0;
		//	}
		//}
		//else if (eIn0.x > 0) {
		//	
		//}
	}

	if (vertsIn.size() + vertsOut.size() != vertsSize) { cout << "PIZDA V " << vertsIn.size() << " " << vertsOut.size() << " " << vertsSize << endl; return; }
	if (linesIn.size() + linesOut.size() + linesBetween.size() != linesSize) { cout << "PIZDA L " << linesIn.size() << " " << linesOut.size() << " " << linesBetween.size() << " " << linesSize << endl; return; }

	// Verts Push
	vertsPush(0, vertsIn);
	vertsPush(vertsIn.size(), vertsOut);

	// Lines Push
	linesPush(0, linesIn);
	linesPush(linesIn.size(), linesOut);
	linesPush(linesIn.size() + linesOut.size(), linesBetween);

	borderPerShapePtr[ps.index * 3 + 0] = rightBorder.bottom;
	borderPerShapePtr[ps.index * 3 + 1] = rightBorder.top;
	borderPerShapePtr[ps.index * 3 + 2] = rightBorder.expressionIndex;
	
};

void Shape::vertsPush(int offset, vector<float2>& verts) {
	for (int i = 0; i < verts.size(); i++) {
		int j = (vertsPrevSize + offset + i) * 2;
		vertsPtr[j] = verts[i].x;
		vertsPtr[j + 1] = verts[i].y;
	}
}

void Shape::linesPush(int offset, vector<lineSided>& lines) {
	for (int i = 0; i < lines.size(); i++) {
		int j = (linesPrevSize + offset + i) * 3;

		const int vertFromIndex = lines[i].from + (lines[i].fromType == VERT_TYPE::OUT) * static_cast<int>(vertsIn.size()) + vertsPrevSize;
		const int vertToIndex = lines[i].to + (lines[i].toType == VERT_TYPE::OUT) * static_cast<int>(vertsIn.size()) + vertsPrevSize;
		
		cout << "LINE PUSH ";

		linesPtr[j] = vertFromIndex;
		linesPtr[j + 1] = vertToIndex;
		cout << float2(vertsPtr[vertFromIndex * 2], vertsPtr[vertFromIndex * 2 + 1]).getString() << " " <<
			float2(vertsPtr[vertToIndex * 2], vertsPtr[vertToIndex * 2 + 1]).getString() << " " << lines[i].sideVert.getString() <<
			lines[i].expressionIndexFit << " " << lines[i].expressionIndexOtherwise;
		linesPtr[j + 2] = getProperExp(
			float2(vertsPtr[vertFromIndex * 2], vertsPtr[vertFromIndex * 2 + 1]),
			float2(vertsPtr[vertToIndex * 2], vertsPtr[vertToIndex * 2 + 1]),
			lines[i].sideVert, lines[i].expressionIndexFit, lines[i].expressionIndexOtherwise
		) + expressionPrevSize;

		cout << " RESULT: " << linesPtr[j + 2] << endl;
	}
}

bool Shape::isVertOnLeftOfLine(const float2& lineVert1, const float2& lineVert2, const float2& sideVert) const {
	float2 fromTo = (lineVert1.x < lineVert2.x) ? lineVert2 - lineVert1 : lineVert1 - lineVert2;
	if (abs(fromTo.y) > .00001f) {
		const float ctan = fromTo.x / fromTo.y;
		const float mustLayX = ctan * (sideVert.y - lineVert1.y) + lineVert1.x;
		return sideVert.x < mustLayX;
	}
	else return sideVert.x < lineVert1.x;
}


//bool Shape::isVertHigherThanLine(const float2& lineVert1, const float2& lineVert2, const float2& sideVert) const {
//	float2 fromTo = (lineVert1.x < lineVert2.x) ? lineVert2 - lineVert1 : lineVert1 - lineVert2;
//	if (fromTo.x > .00001f) {
//		const float tan = fromTo.y / fromTo.x;
//		const float mustLayY = tan * (sideVert.x - lineVert1.x) + lineVert1.y;
//		return sideVert.y > mustLayY;
//	}
//	else return sideVert.y > lineVert1.y;
//}


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
	bool& borderOutsideExpressionIndex
) {
	int vertsSize = vertsPtr->size();

	lineSided newLine = {
		.from = vertsSize - 1,
		.to = vertsSize,
		.fromType = vertType,
		.toType = vertType,
		.fromArrPtr = vertsPtr,
		.toArrPtr = vertsPtr,
		.sideVert = sideVert,
		.expressionIndexFit = expressionIndexFit,
		.expressionIndexOtherwise = expressionIndexOtherwise
	};

	vertsPtr->push_back(vert2);

	if (vert2.x < leftestVertX) {
		leftestVertX = vert2.x;
		borderOutsideExpressionIndex = vertType == VERT_TYPE::IN ? 1 : 0;
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