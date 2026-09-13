#include "general.h"

#include "lodepng.h"
#include "gif.h"

#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

class Renderer {
public:
	float* vertsPtr;
	float* linesPtr;
	float* expressionsCoefficientsPtr;
	float* expressionsSelectionsPtr;
	float* opacityPerShapePtr;
	float* isSubtractPerShapePtr;
	float* borderPerShapePtr;

public:
	Renderer(
		float* vertsPtr, float* linesPtr, 
		float* expressionsCoefficientsPtr, float* expressionsSelectionsPtr, 
		float* opacityPerShapePtr, float* isSubtractPerShapePtr, float* borderPerShapePtr
	) {
		this->vertsPtr = vertsPtr;
		this->linesPtr = linesPtr;
		this->expressionsCoefficientsPtr = expressionsCoefficientsPtr;
		this->expressionsSelectionsPtr = expressionsSelectionsPtr;
		this->opacityPerShapePtr = opacityPerShapePtr;
		this->isSubtractPerShapePtr = isSubtractPerShapePtr;
		this->borderPerShapePtr = borderPerShapePtr;
	}

	float render(float2 xy, bool debug = false) {
		float factor = 0.0f;

		for (int sIndex = 0; sIndex < shapesSize; sIndex++) {
			if (debug) cout << "For Shape " << shapesNames[sIndex] << ":" << endl;
			float shapeFactor = 0.0f;

			float2 suitableLine[2] = { float2(1,-1), float2(1,2) }; // Y in theory can be equal to 0 and 1, but for safety reasons we take -1 and 2
			int suitableExpressionIndex = not borderPerShapePtr[sIndex * 3 + 2]; // Expression outside the border.
			bool isAnyLineSuitable = false;

			int linesPrevSize = shapeSizesPerShapeIndex[sIndex].linesPrev;
			int linesSize = shapeSizesPerShapeIndex[sIndex].lines;
			for (int lIndex = linesPrevSize; lIndex < linesPrevSize + linesSize; lIndex++) {
				int vf_ = static_cast<int>(linesPtr[lIndex * 3 + 0]); // Index of vert.
				int vt_ = static_cast<int>(linesPtr[lIndex * 3 + 1]); // Index of vert.
				float2 vf (vertsPtr[vf_ * 2], vertsPtr[vf_ * 2 + 1]);
				float2 vt (vertsPtr[vt_ * 2], vertsPtr[vt_ * 2 + 1]);
				int expIndex = static_cast<int>(linesPtr[lIndex * 3 + 2]);

				if (debug) cout << "For line " << vf.getString() << ", " << vt.getString() << ": " << endl;
				if (debug) cout << "exp: " << expIndex << endl;

				bool shouldReplace =
					isIntersectsLineOnRight(vf, vt, xy) and 
					(
					!isAnyLineSuitable or
					isline1IntersectsLine2OnLeft(suitableLine[0], suitableLine[1], vf, vt)
					);

				if (debug) cout << "Should Replace: " << shouldReplace << endl;
				if (debug) cout << "Is point " << xy.getString()
					<< " intersects line " << vf.getString() << vt.getString() << " on right: "
					<< isIntersectsLineOnRight(vf, vt, xy) << endl;
				if (debug) cout << "Is line " << suitableLine[0].getString() << ", " << suitableLine[1].getString() 
					<< " intersects line " << vf.getString() << ", " << vt.getString() << " on left: "
					<< isline1IntersectsLine2OnLeft(suitableLine[0], suitableLine[1], vf, vt) << endl;

				if (shouldReplace) {
					suitableLine[0] = vf;
					suitableLine[1] = vt;
					suitableExpressionIndex = expIndex;
				}

				// For border.
				isAnyLineSuitable = isAnyLineSuitable ? true : shouldReplace;

				if (debug) cout << endl;
			}

			// Border check.
			if (!isAnyLineSuitable and xy.y >= borderPerShapePtr[sIndex * 3 + 0] and xy.y <= borderPerShapePtr[sIndex * 3 + 1]) {
				suitableExpressionIndex = borderPerShapePtr[sIndex * 3 + 2];
			}

			if (debug) cout << "Suitable line is " << suitableLine[0].getString() << ", " << suitableLine[1].getString() << endl;
			
			if (expressionsSelectionsPtr[suitableExpressionIndex] == 0) {
				// Raw
				shapeFactor = expressionsCoefficientsPtr[suitableExpressionIndex * 10 + 0];
				if (debug) cout << "Suitable line exp is raw." << endl;
			}
			else if (expressionsSelectionsPtr[suitableExpressionIndex] == 1) {
				shapeFactor = quadraticExp(xy.x, xy.y, suitableExpressionIndex);
				if (debug) cout << "Suitable line exp is quadratic." << endl;
			}
			else if (expressionsSelectionsPtr[suitableExpressionIndex] == 2) {
				shapeFactor = constantExp(xy.x, xy.y, suitableExpressionIndex);
				if (debug) cout << "Suitable line exp is constant." << endl;
			}
			else {
				shapeFactor = linearExp(xy.x, xy.y, suitableExpressionIndex);
				if (debug) cout << "Suitable line exp is linear." << endl;
			}

			shapeFactor *= opacityPerShapePtr[sIndex];

			const int exponent = 2;

			float a = isSubtractPerShapePtr[sIndex] ? (1 - factor) : factor;
			float b = static_cast<float>(
				pow(
					clamp(
						pow(a, exponent) + pow(shapeFactor, exponent), 
						0.0, 
						1.0
					), 
					1.0f/static_cast<float>(exponent)
				)
			);
			factor = isSubtractPerShapePtr[sIndex] ? (1 - b) : b;

			if (debug) cout << endl;
		}

		if (debug) cout << endl << endl;

		const float exponent = 3;
		factor = pow(factor, exponent);

		return factor;
	}

	bool isIntersectsLineOnRight(float2 l1, float2 l2, float2 p) {
		return 
			!((l1.x == p.x) and (l1.y == p.y)) and !((l2.x == p.x) and (l2.y == p.y)) and
			(l1.y != l2.y) and 
			((l2.y <= p.y) and 
			(l1.y >= p.y) or 
			(l2.y >= p.y) and 
			(l1.y <= p.y)) and 
			(p.x < (p.y - l2.y) * (l1.x - l2.x) / (l1.y - l2.y) + l2.x);
	}

	bool isIntersectsLineOnLeft(float2 l1, float2 l2, float2 p) {
		return
			!((l1.x == p.x) and (l1.y == p.y)) and !((l2.x == p.x) and (l2.y == p.y)) and
			(l1.y != l2.y) and
			((l2.y <= p.y) and
			(l1.y >= p.y) or
			(l2.y >= p.y) and
			(l1.y <= p.y)) and
			(p.x > (p.y - l2.y) * (l1.x - l2.x) / (l1.y - l2.y) + l2.x);
	}


	bool isline1IntersectsLine2OnLeft(float2 vf1, float2 vt1, float2 vf2, float2 vt2) {
		return
			isIntersectsLineOnRight(vf1, vt1, vf2) or
			isIntersectsLineOnRight(vf1, vt1, vt2) or
			isIntersectsLineOnLeft(vf2, vt2, vf1) or
			isIntersectsLineOnLeft(vf2, vt2, vt1);
	}
	
	

	float quadraticExp(float x, float y, int expressionIndex) const {
		const float bx = expressionsCoefficientsPtr[expressionIndex * 10 + 0];
		const float by = expressionsCoefficientsPtr[expressionIndex * 10 + 1];
		const float bs = expressionsCoefficientsPtr[expressionIndex * 10 + 2];
		const float cx2 = expressionsCoefficientsPtr[expressionIndex * 10 + 3];
		const float cy2 = expressionsCoefficientsPtr[expressionIndex * 10 + 4];
		const float cxy = expressionsCoefficientsPtr[expressionIndex * 10 + 5];
		const float centerX = expressionsCoefficientsPtr[expressionIndex * 10 + 6];
		const float centerY = expressionsCoefficientsPtr[expressionIndex * 10 + 7];
		const float am2 = expressionsCoefficientsPtr[expressionIndex * 10 + 8];
		const float useFirstMember = expressionsCoefficientsPtr[expressionIndex * 10 + 9];

		x -= centerX;
		y -= centerY;

		float b = x * bx + y * by + bs;
		float c = x * x * cx2 + y * y * cy2 + x * y * cxy - 1;
		float D = sqrt(b * b - 2 * am2 * c);
		return 1.f - clamp((-b + (-2 * useFirstMember + 1) * D) / am2, 0.f, 1.f);
	}
		
	// TODO: Merge this with quadratic.
	float linearExp(float x, float y, int expressionIndex) const {
		const float bx = expressionsCoefficientsPtr[expressionIndex * 10 + 0];
		const float by = expressionsCoefficientsPtr[expressionIndex * 10 + 1];
		const float bs = expressionsCoefficientsPtr[expressionIndex * 10 + 2];
		const float cx2 = expressionsCoefficientsPtr[expressionIndex * 10 + 3];
		const float cy2 = expressionsCoefficientsPtr[expressionIndex * 10 + 4];
		const float cxy = expressionsCoefficientsPtr[expressionIndex * 10 + 5];
		const float centerX = expressionsCoefficientsPtr[expressionIndex * 10 + 6];
		const float centerY = expressionsCoefficientsPtr[expressionIndex * 10 + 7];

		x -= centerX;
		y -= centerY;

		float b = x * bx + y * by + bs;
		float c = x * x * cx2 + y * y * cy2 + x * y * cxy - 1;
		return 1.f - clamp(-c / b, 0.0f, 1.0f);
	}

	float constantExp(float x, float y, int expressionIndex) const {
		const float constX = expressionsCoefficientsPtr[expressionIndex * 10 + 0];
		const float constY = expressionsCoefficientsPtr[expressionIndex * 10 + 1];
		const float constScalar = expressionsCoefficientsPtr[expressionIndex * 10 + 2];

		return 1.f - clamp(constX * x + constY * y + constScalar, 0.0f, 1.0f);
	}
};

void fillImageBuffer(Renderer& renderer, vector<uint8_t>& buffer, int size) {
	buffer.reserve(size * size * 4);
	for (int32_t i = 0; i < size; i++)
	{
		for (int32_t j = 0; j < size; j++)
		{
			float renderResult = renderer.render(float2(
				static_cast<float>(j) / static_cast<float>(size),
				1 - static_cast<float>(i) / static_cast<float>(size) // reversing 'coz image buffer has coordinate origin at bottom right corner.
			));
			buffer.push_back(renderResult * 255.f);
			buffer.push_back(renderResult * 255.f);
			buffer.push_back(renderResult * 255.f);
			buffer.push_back(255);
		}
	}
}

void savePNG(Renderer& renderer, int size) {
	vector<uint8_t> buffer = {};
	
	fillImageBuffer(renderer, buffer, size);

	vector<uint8_t> ImageBuffer;
	lodepng::encode(ImageBuffer, buffer, size, size);
	lodepng::save_file(ImageBuffer, "C:/Users/Crite/Desktop/render.png");
}

void saveAnimation(Renderer& renderer, int size, float vFrom, float vTo, float hFrom, float hTo, int frames, int delay = 100) {
	auto fileName = "C:/Users/Crite/Desktop/render.gif";
	GifWriter g;
	GifBegin(&g, fileName, size, size, delay);

	for (int i = 0; i < frames; i++) {
		vector<uint8_t> buffer = {};
		CMS::tick(
			(vTo - vFrom) * (static_cast<float>(i) / static_cast<float>(frames)) + vFrom, 
			(hTo - hFrom) * (static_cast<float>(i) / static_cast<float>(frames)) + hFrom, 
			renderer.vertsPtr, renderer.linesPtr, renderer.expressionsCoefficientsPtr, renderer.expressionsSelectionsPtr, renderer.opacityPerShapePtr, renderer.isSubtractPerShapePtr, renderer.borderPerShapePtr);
		fillImageBuffer(renderer, buffer, size);
		GifWriteFrame(&g, buffer.data(), size, size, delay);
	}
	GifEnd(&g);
}

int main() {
	float* vertsPtr = new float[vertsSize * 2];
	float* linesPtr = new float[linesSize * 3];
	float* expressionsCoefficientsPtr = new float[(expressionsSize + 2) * 10];
	float* expressionsSelectionsPtr = new float[(expressionsSize + 2) * 3];
	float* opacityPerShapePtr = new float[shapesSize];
	float* isSubtractPerShapePtr = new float[shapesSize];
	float* borderPerShapePtr = new float[shapesSize * 3];

	const bool doPNG = 1;
	const bool doAnimation = 0;
	const bool doRenderPoint = 1; 
	//const float2 testRenderPoint(0.0f, 0.0f); // 0
	//const float2 testRenderPoint (0.5f, 0.5f); // 1
	//const float2 testRenderPoint(1.f, 1.f); // custom
	const float2 testRenderPoint((-2.58469f + 3.f) / 6.f, (0.309966f + 3.f) / 6.f); // blender export
	const bool debug = true; // Print additional info in console.

	CMS::tick(0.f, 2.f/3.f + 1.f/30.f, vertsPtr, linesPtr, expressionsCoefficientsPtr, expressionsSelectionsPtr, opacityPerShapePtr, isSubtractPerShapePtr, borderPerShapePtr, debug);

	Renderer renderer(vertsPtr, linesPtr, expressionsCoefficientsPtr, expressionsSelectionsPtr, opacityPerShapePtr, isSubtractPerShapePtr, borderPerShapePtr);
	if (doPNG) {
		const int size = 512;
		savePNG(renderer, size);
		cout << "PNG saved on desktop." << endl;
	}

	if (doAnimation) {
		const int size = 512;
		saveAnimation(renderer, size, 0, 1, 0, 1, 30, 5);
		cout << "GIF saved on desktop." << endl;
	}

	if (doRenderPoint) {
		float renderResult = renderer.render(testRenderPoint, true);
		if (debug) cout << "Test render at point " << testRenderPoint.getString() << ": \t" << renderResult;
	}

	return 0;
}