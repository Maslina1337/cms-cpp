//#include "pch.h"
//#include "segment.h"
//
//template<bool isTriple>
//Segment<isTriple>::Segment(float2 v[2 + isTriple], float2 vf[2 + isTriple]) {
//	vog[0][0] = v[0];
//	vog[0][1] = v[1];
//	if constexpr (isTriple) { vog[0][2] = v[2]; }
//	vog[1][0] = vf[0];
//	vog[1][1] = vf[1];
//	if constexpr (isTriple) { vog[1][2] = vf[2]; }
//
//	float2 v12 = v[1] - v[0];
//	float2 v23 = v[2] - v[1];
//	float2 v13 = v[2] - v[0];
//
//	bool isStraight;
//	if constexpr (isTriple) { isStraight = true; }
//	else {
//		isStraight = abs(v12.x) < 0.0001f ?
//			(abs(v23.x) < 0.0001f * abs(v23.y / v12.x)) :
//			(abs(v[2].y - v12.y / v12.x * (v[2].x - v[0].x) - v[0].y) < 0.0001f);
//	}
//
//	// Straight case. // TODO: Can be copyed to const exp above.
//	if (isStraight)
//	{
//		vertsIn[0] = v[0];
//		vertsIn[1] = v[size - 1];
//		vertsOut[0] = vf[0];
//		vertsOut[1] = vf[size - 1];
//
//		isVertsInTriple = false;
//		isVertsOutTriple = false;
//
//		float constX = 0.0f, constY = 0.0f, constScalar = 0.0f;
//		bool isMoreVerticalThanHorizontal = (v[size - 1].x - v[0].x == 0) or abs((v[size - 1].y - v[0].y) / (v[size - 1].x - v[0].x)) > 1;
//
//		if (isMoreVerticalThanHorizontal) { // Vertical case.
//			float ctan = (v[size - 1].x - v[0].x) / (v[size - 1].y - v[0].y);
//
//			float a = ctan * (v[0].y - vf[0].y) + vf[0].x - v[0].x;
//
//			float constScalar = (ctan * v[0].x - v[0].y) / a;
//			float constX = -ctan / a;
//			float constY = 1 / a;
//		}
//		else { // Horizontal case.
//			float tan = (v[size - 1].y - v[0].y) / (v[size - 1].x - v[0].x);
//
//			float a = tan * (v[0].x - vf[0].x) + vf[0].y - v[0].y;
//
//			float constScalar = (tan * v[0].x - v[0].y) / a;
//			float constX = -tan / a;
//			float constY = 1 / a;
//		}
//
//		expressionSelection[EXPRESSION_SELECTION::CONSTANT] = true;
//		expressionCoefficients[0] = constX;
//		expressionCoefficients[1] = constY;
//		expressionCoefficients[2] = constScalar;
//		return;
//	}
//
//	// TODO: Merge the Reorder and PointsDefine methods.
//	PointsDefine(v, false); 
//	PointsDefine(vf, true);
//
//	if (abs(v13.x) < abs(v12.x) * 0.05) Reorder(1, 2, 3);
//	else if (abs(v12.x) < abs(v23.x) * 0.05) Reorder(2, 1, 0);
//
//	float2 v1f1 = vog[1][0] - vog[0][0];
//	bool isFadingLeft = v12.cross(v23) > 0;
//
//	float cross_ = v12.cross(v23);
//	bool itTurnsLeft = cross_ > 0;
//	bool itTurnsRight = cross_ < 0;
//
//	// Curved case.
//	if (itTurnsLeft && isFadingLeft || itTurnsRight && !isFadingLeft)
//	{
//		vertsIn[0] = v[0];
//		vertsIn[1] = v[1];
//		vertsIn[2] = v[2];
//		vertsOut[0] = vf[0];
//		vertsOut[1] = vf[2];
//
//		//vertsInSize = 3;
//		//vertsOutSize = 2;
//
//		isVertsInTriple = true;
//		isVertsOutTriple = false;
//	}
//	else
//	{
//		vertsIn[0] = v[0];
//		vertsIn[1] = v[2];
//		vertsOut[0] = vf[0];
//		vertsOut[1] = vf[1];
//		vertsOut[2] = vf[2];
//
//		//vertsInSize = 2;
//		//vertsOutSize = 3;
//
//		isVertsInTriple = false;
//		isVertsOutTriple = true;
//	}
//
//	// Sheared ellipse coefficients define.
//	const float A1 = -vc[0][0].x;
//	const float B0 = -vc[0][1].x * (vc[0][1].y - vc[0][0].y) / (vc[0][1].x - vc[0][0].x) + vc[0][1].y;
//	const float b = vc[0][0].y - B0;
//	const float A0 = (-B0 * (vc[0][2].x - vc[0][1].x) / (-2 * B0) + vc[0][1].x);
//	const float a = A0 - vc[0][1].x;
//
//	// One coefficient for fadeout ellipse to define the relative scale.
//	const float B0f = -vc[1][1].x * (vc[1][1].y - vc[1][0].y) / (vc[1][1].x - vc[1][0].x) + vc[1][1].y;
//
//	const float s = B0f / B0;
//	const float2 shift = center[0] - center[1];
//
//	// TODO Optimize dis coefficients..
//	const float U4 = 1 / (B0 * B0);
//	const float U5 = 1 / (A0 * A0);
//
//	const float U6 = b * b * U4 / (A1 * A1);
//	const float U9 = a * a * U5 * U4;
//	const float U8 = a * a * U5 * U6;
//
//	const float U2 = 2 * a * U5 / B0;
//	const float U7 = 2 * b * U4 / A1;
//	const float U1 = 2 * b * U9 / A1;
//
//	const float U3 = 2 * a * b * U5 / (B0 * A1);
//
//	const float U11 = -s * (s - 2) - 1;
//	const float U12 = 2 * (1 - s);
//
//	// Shorting a 'lil
//	const float U3558 = U5 + U8 + U3 + U6;
//	const float U49 = U9 + U4;
//	const float U127 = U2 + U1 + U7;
//
//	const float a_ = shift.x * shift.x * U3558 + shift.y * shift.y * U49 + shift.x * shift.y * U127 + U11;
//
//	// Final Coefficients for quadratic and linear cases.
//	const float a_m_2 = a_ * 2;
//	const float b_x = 2 * shift.x * U3558 + shift.y * U127;
//	const float b_y = 2 * shift.y * U49 + shift.x * U127;
//	const float b_s = U12;
//	const float c_x2 = U3558;
//	const float c_y2 = U49;
//	const float c_xy = U127;
//
//	expressionCoefficients[0] = b_x;
//	expressionCoefficients[1] = b_y;
//	expressionCoefficients[2] = b_s;
//	expressionCoefficients[3] = c_x2;
//	expressionCoefficients[4] = c_y2;
//	expressionCoefficients[5] = c_xy;
//	expressionCoefficients[6] = center[0].x;
//	expressionCoefficients[7] = center[0].y;
//
//	if (a_ != 0)
//	{
//		//Choose member.
//		float b__ = vh[0][0].x * b_x + vh[0][0].y * b_y + b_s;
//		float c__ = vh[0][0].x * vh[0][0].x * c_x2 + vh[0][0].y * vh[0][0].y * c_y2 + vh[0][0].x * vh[0][0].y * c_xy - 1;
//
//		float D__ = sqrt(abs(b__ * b__ - 2 * a_m_2 * c__));
//
//		float F1__ = (-b__ - D__) / a_m_2;
//		float F2__ = (-b__ + D__) / a_m_2;
//
//		// Is first member closer to zero factor (influence).
//		bool useFirstMember = abs(F1__) < abs(F2__);
//
//		expressionSelection[EXPRESSION_SELECTION::QUADRATIC] = true;
//
//		expressionCoefficients[8] = a_m_2;
//		expressionCoefficients[9] = useFirstMember ? 1 : 0;
//	}
//}
//
//template<bool isTriple>
//void Segment<isTriple>::Reorder(const int order1, const int order2, const int order3)
//{
//	vc[0][0] = va[0][0][order1];
//	vc[0][1] = va[0][1][order2];
//	vc[0][2] = va[0][2][order3];
//
//	vc[1][0] = va[1][0][order1];
//	vc[1][1] = va[1][1][order2];
//	vc[1][2] = va[1][2][order3];
//
//	vh[0][0] = vc[0][1] + (vc[0][0] - vc[0][1]) / 2;
//	vh[0][1] = vc[0][1];
//	vh[0][2] = vc[0][1] + (vc[0][2] - vc[0][1]) / 2;
//
//	vh[1][0] = vc[1][1] + (vc[1][0] - vc[1][1]) / 2;
//	vh[1][1] = vc[1][1];
//	vh[1][2] = vc[1][1] + (vc[1][2] - vc[1][1]) / 2;
//}
//
//
//template<bool isTriple>
//void Segment<isTriple>::PointsDefine(float2 *v, const bool isFadeout)
//{
//	const float2 center_ = v[1] + (v[0] - v[1]) + (v[2] - v[1]);
//	center[isFadeout] = center_;
//
//	const float2 vh0 = v[0] - center_;
//	const float2 vh1 = v[1] - center_;
//	const float2 vh2 = v[2] - center_;
//
//	vh[isFadeout][0] = vh0;
//	vh[isFadeout][1] = vh1;
//	vh[isFadeout][2] = vh2;
//
//	const float2 va0 = (vh0 - vh1) * 2 + vh1;
//	const float2 va1 = vh1;
//	const float2 va2 = (vh2 - vh1) * 2 + vh1;
//	const float2 va3 = -vh1;
//
//	va[isFadeout][0] = va0;
//	va[isFadeout][1] = va1;
//	va[isFadeout][2] = va2;
//	va[isFadeout][3] = va3;
//
//	vc[isFadeout][0] = va0;
//	vc[isFadeout][1] = va1;
//	vc[isFadeout][2] = va2;
//}