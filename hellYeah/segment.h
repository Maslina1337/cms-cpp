#pragma once
#include <cmath>
#include <array>
#include <string>

#include "float2.h"

using namespace std;

//enum EXPRESSION_SELECTION {
//	RAW,
//	QUADRATIC,
//	CONSTANT,
//	// Otherwise Linear
//};

//	NOTHING = [True, False, False]     # Coefficients : [0]
//	EVERYTHING = [True, False, False]  # Coefficients : [1]
//	QUADRATIC = [False, True, False]   # Coefficients : [b_x        b_y         b_s             c_x2    c_y2    c_xy  center_x    center_y    a_m_2   use_first_member]
//	CONSTANT = [False, False, True]    # Coefficients : [const_x    const_y     const_scalar]
//	LINEAR = [False, False, False]     # Coefficients : [b_x        b_y         b_s             c_x2    c_y2    c_xy  center_x    center_y]

template<bool isTriple>
class Segment {
public:
	float2 vog[2][2 + isTriple];
	float2 vc[2][2 + isTriple];
	float2 vh[2][2 + isTriple];
	float2 va[2][3 + isTriple];
	float2 center[2];

	float2 vertsIn[2 + isTriple];
	float2 vertsOut[2 + isTriple];

	bool isVertsInTriple;
	bool isVertsOutTriple;

	Segment(float2 v[2 + isTriple], float2 vf[2 + isTriple], vector<float>* expressionsCoefficientsPtr, vector<bool>* expressionsSelectionPtr) {
		int size = 2 + isTriple;

		// Straight case. // TODO: Can be copyed to const exp above.
		if constexpr (not isTriple)
		{
			vertsIn[0] = v[0];
			vertsIn[1] = v[size - 1];
			vertsOut[0] = vf[0];
			vertsOut[1] = vf[size - 1];

			isVertsInTriple = false;
			isVertsOutTriple = false;

			float constX = 0.0f, constY = 0.0f, constScalar = 0.0f;
			bool isMoreVerticalThanHorizontal = (v[size - 1].x - v[0].x == 0) or abs((v[size - 1].y - v[0].y) / (v[size - 1].x - v[0].x)) > 1;

			if (isMoreVerticalThanHorizontal) { // Vertical case.
				float ctan = (v[size - 1].x - v[0].x) / (v[size - 1].y - v[0].y);

				float a = ctan * (v[0].y - vf[0].y) + vf[0].x - v[0].x;

				float constScalar = (ctan * v[0].x - v[0].y) / a;
				float constX = -ctan / a;
				float constY = 1 / a;
			}
			else { // Horizontal case.
				float tan = (v[size - 1].y - v[0].y) / (v[size - 1].x - v[0].x);

				float a = tan * (v[0].x - vf[0].x) + vf[0].y - v[0].y;

				float constScalar = (tan * v[0].x - v[0].y) / a;
				float constX = -tan / a;
				float constY = 1 / a;
			}

			// CONSTANT
			expressionsSelectionPtr->push_back(false);
			expressionsSelectionPtr->push_back(false);
			expressionsSelectionPtr->push_back(true);

			expressionsCoefficientsPtr->push_back(constX);
			expressionsCoefficientsPtr->push_back(constY);
			expressionsCoefficientsPtr->push_back(constScalar);
			expressionsCoefficientsPtr->push_back(0.0f);
			expressionsCoefficientsPtr->push_back(0.0f);
			expressionsCoefficientsPtr->push_back(0.0f);
			expressionsCoefficientsPtr->push_back(0.0f);
			expressionsCoefficientsPtr->push_back(0.0f);
			expressionsCoefficientsPtr->push_back(0.0f);
			expressionsCoefficientsPtr->push_back(0.0f);

			return;
		}

		// Following Code is only for triple segments.

		vog[0][0] = v[0];
		vog[0][1] = v[1];
		vog[0][2] = v[2];
		vog[1][0] = vf[0];
		vog[1][1] = vf[1];
		vog[1][2] = vf[2];

		float2 v12 = v[1] - v[0];
		float2 v23 = v[2] - v[1];
		float2 v13 = v[2] - v[0];

		// TODO: Merge the reorder and pointsDefine methods.
		pointsDefine(v, false);
		pointsDefine(vf, true);
		
		// TODO: reorder can be moved before pointsDefine
		if (abs(v13.x) < abs(v12.x) * 0.05) reorder(1, 2, 3);
		else if (abs(v12.x) < abs(v23.x) * 0.05) reorder(2, 1, 0);

		float2 v1f1 = vog[1][0] - vog[0][0];
		bool isFadingLeft = v12.cross(v23) > 0;

		float cross_ = v12.cross(v23);
		bool itTurnsLeft = cross_ > 0;
		bool itTurnsRight = cross_ < 0;

		// Curved case.
		if (itTurnsLeft && isFadingLeft || itTurnsRight && !isFadingLeft)
		{
			vertsIn[0] = v[0];
			vertsIn[1] = v[1];
			vertsIn[2] = v[2];
			vertsOut[0] = vf[0];
			vertsOut[1] = vf[2];

			isVertsInTriple = true;
			isVertsOutTriple = false;
		}
		else
		{
			vertsIn[0] = v[0];
			vertsIn[1] = v[2];
			vertsOut[0] = vf[0];
			vertsOut[1] = vf[1];
			vertsOut[2] = vf[2];

			isVertsInTriple = false;
			isVertsOutTriple = true;
		}

		// Sheared ellipse coefficients define.
		const float A1 = -vc[0][0].x;
		const float B0 = -vc[0][1].x * (vc[0][1].y - vc[0][0].y) / (vc[0][1].x - vc[0][0].x) + vc[0][1].y;
		const float b = vc[0][0].y - B0;
		const float A0 = (-B0 * (vc[0][2].x - vc[0][1].x) / (-2 * B0) + vc[0][1].x);
		const float a = A0 - vc[0][1].x;

		// One coefficient for fadeout ellipse to define the relative scale.
		const float B0f = -vc[1][1].x * (vc[1][1].y - vc[1][0].y) / (vc[1][1].x - vc[1][0].x) + vc[1][1].y;

		const float s = B0f / B0;

		const float2 shift = center[0] - center[1];

		// TODO Optimize dis coefficients..
		const float U4 = 1 / (B0 * B0);
		const float U5 = 1 / (A0 * A0);

		const float U6 = b * b * U4 / (A1 * A1);
		const float U9 = a * a * U5 * U4;
		const float U8 = a * a * U5 * U6;

		const float U2 = 2 * a * U5 / B0;
		const float U7 = 2 * b * U4 / A1;
		const float U1 = 2 * b * U9 / A1;

		const float U3 = 2 * a * b * U5 / (B0 * A1);

		const float U11 = -s * (s - 2) - 1;
		const float U12 = 2 * (1 - s);

		// Shorting a 'lil
		const float U3558 = U5 + U8 + U3 + U6;
		const float U49 = U9 + U4;
		const float U127 = U2 + U1 + U7;

		const float a_ = shift.x * shift.x * U3558 + shift.y * shift.y * U49 + shift.x * shift.y * U127 + U11;

		// Final Coefficients for quadratic and linear cases.
		const float a_m_2 = a_ * 2;
		const float b_x = 2 * shift.x * U3558 + shift.y * U127;
		const float b_y = 2 * shift.y * U49 + shift.x * U127;
		const float b_s = U12;
		const float c_x2 = U3558;
		const float c_y2 = U49;
		const float c_xy = U127;

		expressionsCoefficientsPtr->push_back(b_x);
		expressionsCoefficientsPtr->push_back(b_y);
		expressionsCoefficientsPtr->push_back(b_s);
		expressionsCoefficientsPtr->push_back(c_x2);
		expressionsCoefficientsPtr->push_back(c_y2);
		expressionsCoefficientsPtr->push_back(c_xy);
		expressionsCoefficientsPtr->push_back(center[0].x);
		expressionsCoefficientsPtr->push_back(center[0].y);

		if (a_ != 0)
		{
			//Choose member.
			float b__ = vh[0][0].x * b_x + vh[0][0].y * b_y + b_s;
			float c__ = vh[0][0].x * vh[0][0].x * c_x2 + vh[0][0].y * vh[0][0].y * c_y2 + vh[0][0].x * vh[0][0].y * c_xy - 1;

			float D__ = sqrt(abs(b__ * b__ - 2 * a_m_2 * c__));

			float F1__ = (-b__ - D__) / a_m_2;
			float F2__ = (-b__ + D__) / a_m_2;

			// Is first member closer to zero factor (influence).
			bool useFirstMember = abs(F1__) < abs(F2__);

			// QUADRATIC
			expressionsSelectionPtr->push_back(false);
			expressionsSelectionPtr->push_back(true);
			expressionsSelectionPtr->push_back(false);

			expressionsCoefficientsPtr->push_back(a_m_2);
			expressionsCoefficientsPtr->push_back(useFirstMember);
		}
		else {
			// LINEAR
			expressionsSelectionPtr->push_back(false);
			expressionsSelectionPtr->push_back(false);
			expressionsSelectionPtr->push_back(false);

			expressionsCoefficientsPtr->push_back(0.0f);
			expressionsCoefficientsPtr->push_back(0.0f);
		}
	};

private:
	void reorder(const int order1, const int order2, const int order3) {
		vc[0][0] = va[0][order1];
		vc[0][1] = va[0][order2];
		vc[0][2] = va[0][order3];

		vc[1][0] = va[1][order1];
		vc[1][1] = va[1][order2];
		vc[1][2] = va[1][order3];

		vh[0][0] = vc[0][1] + (vc[0][0] - vc[0][1]) / 2;
		vh[0][1] = vc[0][1];
		vh[0][2] = vc[0][1] + (vc[0][2] - vc[0][1]) / 2;

		vh[1][0] = vc[1][1] + (vc[1][0] - vc[1][1]) / 2;
		vh[1][1] = vc[1][1];
		vh[1][2] = vc[1][1] + (vc[1][2] - vc[1][1]) / 2;
	};

	void pointsDefine(float2 v[3], const bool isFadeout) {
		const float2 center_ = v[0] + v[2] - v[1];
		center[isFadeout] = center_;

		const float2 vh0 = v[0] - center_;
		const float2 vh1 = v[1] - center_;
		const float2 vh2 = v[2] - center_;

		vh[isFadeout][0] = vh0;
		vh[isFadeout][1] = vh1;
		vh[isFadeout][2] = vh2;

		const float2 va0 = (vh0 - vh1) * 2 + vh1;
		const float2 va1 = vh1;
		const float2 va2 = (vh2 - vh1) * 2 + vh1;
		const float2 va3 = -vh1;

		va[isFadeout][0] = va0;
		va[isFadeout][1] = va1;
		va[isFadeout][2] = va2;
		va[isFadeout][3] = va3;

		vc[isFadeout][0] = va0;
		vc[isFadeout][1] = va1;
		vc[isFadeout][2] = va2;
	};
};