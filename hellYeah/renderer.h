#include "general.h"
#include "lodepng.h"
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

public:
	Renderer(
		float* vertsPtr, float* linesPtr, 
		float* expressionsCoefficientsPtr, float* expressionsSelectionsPtr, 
		float* opacityPerShapePtr, float* isSubtractPerShapePtr
	) {
		this->vertsPtr = vertsPtr;
		this->linesPtr = linesPtr;
		this->expressionsCoefficientsPtr = expressionsCoefficientsPtr;
		this->expressionsSelectionsPtr = expressionsSelectionsPtr;
		this->opacityPerShapePtr = opacityPerShapePtr;
		this->isSubtractPerShapePtr = isSubtractPerShapePtr;
	}

	float render(float2 xy) {
		float factor = 0.0f;

		for (int sIndex = 0; sIndex < shapesSize; sIndex++) {
			float shapeFactor;

			float2 suitableLine[2] = { float2(1,0), float2(1,1) };
			int suitableExpressionIndex = 0; // TODO: default index heere

			int linesPrevSize = shapeSizesPerShapeIndex[sIndex].linesPrev;
			int linesSize = shapeSizesPerShapeIndex[sIndex].lines;
			for (int lIndex = linesPrevSize; lIndex < linesPrevSize + linesSize; lIndex++) {
				float2 vf = vertsPtr[static_cast<int>(linesPtr[lIndex * 3 + 0])];
				float2 vt = vertsPtr[static_cast<int>(linesPtr[lIndex * 3 + 1])];
				int expIndex = vertsPtr[static_cast<int>(linesPtr[lIndex * 3 + 2])];

				bool shouldReplace =
					isIntersectsLineOnRight(vf, vt, xy) and
					isline1IntersectsLine2OnLeftUnsafe(suitableLine[0], suitableLine[1], vf, vt);

				if (shouldReplace) {
					suitableLine[0] = vf;
					suitableLine[1] = vt;
					suitableExpressionIndex = expIndex;
				}
			}

			if (expressionsSelectionsPtr[suitableExpressionIndex] == 0) {
				// Raw
				shapeFactor = expressionsCoefficientsPtr[suitableExpressionIndex * 10 + 0];
			}
			else if (expressionsSelectionsPtr[suitableExpressionIndex] == 1) {
				shapeFactor = quadraticExp(xy.x, xy.y, suitableExpressionIndex);
			}
			else if (expressionsSelectionsPtr[suitableExpressionIndex] == 2) {
				shapeFactor = constantExp(xy.x, xy.y, suitableExpressionIndex);
			}
			else shapeFactor = linearExp(xy.x, xy.y, suitableExpressionIndex);

			shapeFactor = 1 - shapeFactor;
			shapeFactor *= opacityPerShapePtr[sIndex];
			float a = isSubtractPerShapePtr[sIndex] ? 1 - factor : factor;
			float b = pow(clamp(static_cast<float>(pow(a, 2) + pow(shapeFactor, 2)), 0.0f, 1.0f), 1/2);
			factor = isSubtractPerShapePtr[sIndex] ? 1 - b : b;
		}

		return factor;
	}

	bool isIntersectsLineOnRight(float2 l1, float2 l2, float2 p) {
		return 
			(l1.y != l2.y) and 
			((l2.y <= p.y) and 
			(l1.y >= p.y) or 
			(l2.y >= p.y) and 
			(l1.y <= p.y)) and 
			(p.x < (p.y - l2.y) * (l1.x - l2.x) / (l1.y - l2.y) + l2.x);
	}

	bool isIntersectsLineOnLeft(float2 l1, float2 l2, float2 p) {
		return
			(l1.y != l2.y) and
			((l2.y <= p.y) and
			(l1.y >= p.y) or
			(l2.y >= p.y) and
			(l1.y <= p.y)) and
			(p.x > (p.y - l2.y) * (l1.x - l2.x) / (l1.y - l2.y) + l2.x);
	}


	bool isline1IntersectsLine2OnLeftUnsafe(float2 vf1, float2 vt1, float2 vf2, float2 vt2) {
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
		return clamp((-b + (-2 * useFirstMember + 1) * D) / am2, 0.0f, 1.0f);
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
		return clamp(-c / b, 0.0f, 1.0f);
	}
		

	float constantExp(float x, float y, int expressionIndex) const {
		const float constX = expressionsCoefficientsPtr[expressionIndex * 10 + 0];
		const float constY = expressionsCoefficientsPtr[expressionIndex * 10 + 1];
		const float constScalar = expressionsCoefficientsPtr[expressionIndex * 10 + 2];

		return clamp(constX * x + constY * y + constScalar, 0.0f, 1.0f);
	}
};

int main() {
	float* vertsPtr = new float[vertsSize * 2];
	float* linesPtr = new float[linesSize * 3];
	float* expressionsCoefficientsPtr = new float[(expressionsSize + 2) * 10];
	float* expressionsSelectionsPtr = new float[(expressionsSize + 2) * 3];
	float* opacityPerShapePtr = new float[shapesSize];
	float* isSubtractPerShapePtr = new float[shapesSize];

	CMS::tick(0.5f, 0.5f, vertsPtr, linesPtr, expressionsCoefficientsPtr, expressionsSelectionsPtr, opacityPerShapePtr, isSubtractPerShapePtr);

	//for (int i = 0; i < (expressionsSize + 2) * 10; i++) {
	//	if (i % 10 == 0) cout << endl << i / 10 << ". \t";
	//	cout << expressionsCoefficientsPtr[i] << " ";
	//}

	//cout << endl;

	//for (int i = 0; i < (expressionsSize + 2) * 3; i++) {
	//	if (i % 3 == 0) cout << endl << i / 3 << ". \t";
	//	cout << expressionsSelectionsPtr[i] << " ";
	//}

	//cout << endl;

	//for (int i = 0; i < vertsSize * 2; i++) {
	//	if (i % 2 == 0) cout << endl << i / 2 << ". \t";
	//	cout << vertsPtr[i] << " ";
	//}

	//cout << endl;

	//for (int i = 0; i < linesSize * 3; i++) {
	//	if (i % 3 == 0) cout << endl << i / 3 << ". \t";
	//	cout << linesPtr[i] << " ";
	//}

	// PNG
	int h = 256;
	int w = 256;

	Renderer renderer(vertsPtr, linesPtr, expressionsCoefficientsPtr, expressionsSelectionsPtr, opacityPerShapePtr, isSubtractPerShapePtr);

	vector<std::uint8_t> PngBuffer = {};
	PngBuffer.reserve(w * h);
	for (std::int32_t I = 0; I < h; ++I)
	{
		for (std::int32_t J = 0; J < w; ++J)
		{
			float renderedPixel = renderer.render(float2(J / w, I / h)) * 255;
			PngBuffer.push_back(renderedPixel);
			PngBuffer.push_back(renderedPixel);
			PngBuffer.push_back(renderedPixel);
			PngBuffer.push_back(255);
		}
	}

	vector<std::uint8_t> ImageBuffer;
	lodepng::encode(ImageBuffer, PngBuffer, w, h);
	lodepng::save_file(ImageBuffer, "C:/Users/Crite/Desktop/render.png");

	cout << "IMAGE SAVED" << endl;

	return 0;
}