//#pragma once
#include <cmath>
#include <array>

#include "float2.h"

using namespace std;

enum EXPRESSION_SELECTION {
	RAW,
	QUADRATIC,
	CONSTANT,
	// Otherwise Linear
};

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
	float2 va[2][2 + isTriple];
	float2 center[2];

	float2 vertsIn[2 + isTriple];
	float2 vertsOut[2 + isTriple];

	bool isVertsInTriple;
	bool isVertsOutTriple;

	array<bool, 3> expressionSelection = { false, false, false }; // Raw, Quadratic, Constant, otherwise Linear
	array<float, 10> expressionCoefficients = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

	Segment(float2 v[2 + isTriple], float2 vf[2 + isTriple]);

private:
	void Reorder(const int order1, const int order2, const int order3);
	void PointsDefine(float2* v, const bool isFadeout);
};