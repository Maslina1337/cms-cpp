#pragma once
#include "float2.h"
#include "pureShape.h"
#include <string>
using namespace std;

static const int shapesSize = 2;

static const string shapesNames[shapesSize] = { "nose", "wat" };

static const int shapeNoseVerticalSize = 2;

static const float shapeNoseVerticalLayers[shapeNoseVerticalSize] = { static_cast<float>(0.0), static_cast<float>(1.0) };

static shapeSizes shapeNoseShapeSizes = { .verts = 12, .lines = 16, .expressions = 4, .vertsPrev = 0, .linesPrev = 0, .expressionsPrev = 0 };
static const int shapeNoseVertical0HorizontalSize = 2;

static const float shapeNoseVertical0HorizontalLayers[shapeNoseVertical0HorizontalSize] = { static_cast<float>(0.0), static_cast<float>(1.0) };

static PureShape shapeNoseVertical0Horizontal0PureShape = {
	.locs = {float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.3333333432674408)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.3333333432674408)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.1666666716337204)), float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.1666666716337204))},
	.locsMiddles = {float2(static_cast<float>(0.25), static_cast<float>(0.3333333432674408)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.25)), float2(static_cast<float>(0.25), static_cast<float>(0.1666666716337204)), float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.25))},
	.fadeoutScales = {static_cast<float>(2.9999996870756642), static_cast<float>(2.9999997597187757), static_cast<float>(2.999999742954926), static_cast<float>(2.9999997597187757)},
	.isSubtract = false,
	.isCyclic = true,
	.opacity = static_cast<float>(1),
	.fadeoutAngle = static_cast<float>(1.5707963267948966),
	.fadeoutLength = static_cast<float>(0.16666665611167716),
	.fadeoutShift = float2(static_cast<float>(0.0), static_cast<float>(0.1666666567325592)),
	.index = 0
};

static PureShape shapeNoseVertical0Horizontal360PureShape = {
	.locs = {float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.6666666865348816)), float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.6666666269302368))},
	.locsMiddles = {float2(static_cast<float>(0.25), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.75)), float2(static_cast<float>(0.25), static_cast<float>(0.6666666269302368)), float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.75))},
	.fadeoutScales = {static_cast<float>(2.999999670311981), static_cast<float>(2.999998418614765), static_cast<float>(2.9999998323620005), static_cast<float>(2.999998580664642)},
	.isSubtract = false,
	.isCyclic = true,
	.opacity = static_cast<float>(1),
	.fadeoutAngle = static_cast<float>(1.5707963267948966),
	.fadeoutLength = static_cast<float>(0.1666666281719958),
	.fadeoutShift = float2(static_cast<float>(0.0), static_cast<float>(0.16666662693023682)),
	.index = 0
};

static PureShape* shapeNoseVertical0HorizontalPureShapes[shapeNoseVertical0HorizontalSize] = { &shapeNoseVertical0Horizontal0PureShape, &shapeNoseVertical0Horizontal360PureShape };

static PureShapeLayer<PureShape*> shapeNoseVertical0HorizontalPureShapesWrapped = { .size = shapeNoseVertical0HorizontalSize, .angles = shapeNoseVertical0HorizontalLayers, .pureShapes = shapeNoseVertical0HorizontalPureShapes };

static const int shapeNoseVertical180HorizontalSize = 2;

static const float shapeNoseVertical180HorizontalLayers[shapeNoseVertical180HorizontalSize] = { static_cast<float>(0.0), static_cast<float>(1.0) };

static PureShape shapeNoseVertical180Horizontal0PureShape = {
	.locs = {float2(static_cast<float>(0.6666666269302368), static_cast<float>(0.3333333432674408)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.3333333432674408)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.1666666716337204)), float2(static_cast<float>(0.6666666865348816), static_cast<float>(0.1666666716337204))},
	.locsMiddles = {float2(static_cast<float>(0.75), static_cast<float>(0.3333333432674408)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.25)), float2(static_cast<float>(0.75), static_cast<float>(0.1666666716337204)), float2(static_cast<float>(0.6666666865348816), static_cast<float>(0.25))},
	.fadeoutScales = {static_cast<float>(2.999999670311981), static_cast<float>(3.00000081583813), static_cast<float>(2.9999999050050676), static_cast<float>(3.000000547617693)},
	.isSubtract = false,
	.isCyclic = true,
	.opacity = static_cast<float>(1),
	.fadeoutAngle = static_cast<float>(1.5707963267948966),
	.fadeoutLength = static_cast<float>(0.16666665611167716),
	.fadeoutShift = float2(static_cast<float>(0.0), static_cast<float>(0.1666666567325592)),
	.index = 0
};

static PureShape shapeNoseVertical180Horizontal360PureShape = {
	.locs = {float2(static_cast<float>(0.6666666269302368), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.6666666865348816)), float2(static_cast<float>(0.6666666865348816), static_cast<float>(0.6666666269302368))},
	.locsMiddles = {float2(static_cast<float>(0.75), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.75)), float2(static_cast<float>(0.75), static_cast<float>(0.6666666269302368)), float2(static_cast<float>(0.6666666269302368), static_cast<float>(0.75))},
	.fadeoutScales = {static_cast<float>(2.9999985806654035), static_cast<float>(2.9999985806654035), static_cast<float>(2.9999985806654035), static_cast<float>(2.9999985806654035)},
	.isSubtract = false,
	.isCyclic = true,
	.opacity = static_cast<float>(1),
	.fadeoutAngle = static_cast<float>(1.5707963267948966),
	.fadeoutLength = static_cast<float>(0.1666666281719958),
	.fadeoutShift = float2(static_cast<float>(0.0), static_cast<float>(0.16666662693023682)),
	.index = 0
};

static PureShape* shapeNoseVertical180HorizontalPureShapes[shapeNoseVertical180HorizontalSize] = { &shapeNoseVertical180Horizontal0PureShape, &shapeNoseVertical180Horizontal360PureShape };

static PureShapeLayer<PureShape*> shapeNoseVertical180HorizontalPureShapesWrapped = { .size = shapeNoseVertical180HorizontalSize, .angles = shapeNoseVertical180HorizontalLayers, .pureShapes = shapeNoseVertical180HorizontalPureShapes };

static PureShapeLayer<PureShape*> shapeNoseVerticalPureShapes[shapeNoseVerticalSize] = { shapeNoseVertical0HorizontalPureShapesWrapped, shapeNoseVertical180HorizontalPureShapesWrapped };

static PureShapeLayer<PureShapeLayer<PureShape*>> shapeNoseVerticalPureShapesWrapped = { .size = shapeNoseVerticalSize, .angles = shapeNoseVerticalLayers, .pureShapes = shapeNoseVerticalPureShapes };

static const int shapeWatVerticalSize = 1;

static const float shapeWatVerticalLayers[shapeWatVerticalSize] = { static_cast<float>(0.5) };

static shapeSizes shapeWatShapeSizes = { .verts = 12, .lines = 15, .expressions = 4, .vertsPrev = 12, .linesPrev = 16, .expressionsPrev = 4 };
static const int shapeWatVertical90HorizontalSize = 5;

static const float shapeWatVertical90HorizontalLayers[shapeWatVertical90HorizontalSize] = { static_cast<float>(0.0), static_cast<float>(0.25), static_cast<float>(0.5), static_cast<float>(0.75), static_cast<float>(1.0) };

static PureShape shapeWatVertical90Horizontal0PureShape = {
	.locs = {float2(static_cast<float>(0.2866116166114807), static_cast<float>(0.2794628143310547)), float2(static_cast<float>(0.4044627845287323), static_cast<float>(0.1616116464138031))},
	.locsMiddles = {float2(static_cast<float>(0.22768613696098328), static_cast<float>(0.2205372303724289)), float2(static_cast<float>(0.3455371856689453), static_cast<float>(0.2205372303724289)), float2(static_cast<float>(0.3455372750759125), static_cast<float>(0.1026860922574997))},
	.fadeoutScales = {static_cast<float>(3.000001832844834), static_cast<float>(2.999999966472392)},
	.isSubtract = false,
	.isCyclic = false,
	.opacity = static_cast<float>(1),
	.fadeoutAngle = static_cast<float>(2.3561939673160284),
	.fadeoutLength = static_cast<float>(0.16666665611167716),
	.fadeoutShift = float2(static_cast<float>(-0.11785106360912323), static_cast<float>(0.11785118281841278)),
	.index = 1
};

static PureShape shapeWatVertical90Horizontal90PureShape = {
	.locs = {float2(static_cast<float>(0.4044628143310547), static_cast<float>(0.8383883237838745)), float2(static_cast<float>(0.2866116464138031), static_cast<float>(0.7205371856689453))},
	.locsMiddles = {float2(static_cast<float>(0.3455371558666229), static_cast<float>(0.8973139524459839)), float2(static_cast<float>(0.3455372750759125), static_cast<float>(0.7794628143310547)), float2(static_cast<float>(0.18333332240581512), static_cast<float>(0.7666666507720947))},
	.fadeoutScales = {static_cast<float>(2.9999995194375813), static_cast<float>(2.2481878408280123)},
	.isSubtract = false,
	.isCyclic = false,
	.opacity = static_cast<float>(1),
	.fadeoutAngle = static_cast<float>(0.78539809621802),
	.fadeoutLength = static_cast<float>(0.16666667846341887),
	.fadeoutShift = float2(static_cast<float>(0.1178511381149292), static_cast<float>(0.1178511381149292)),
	.index = 1
};

static PureShape shapeWatVertical90Horizontal180PureShape = {
	.locs = {float2(static_cast<float>(0.7355601191520691), static_cast<float>(0.6551413536071777)), float2(static_cast<float>(0.6318273544311523), static_cast<float>(0.7855918407440186))},
	.locsMiddles = {float2(static_cast<float>(0.8007852435112), static_cast<float>(0.7070080041885376)), float2(static_cast<float>(0.6836938261985779), static_cast<float>(0.7203664779663086)), float2(static_cast<float>(0.6970525979995728), static_cast<float>(0.8374583125114441))},
	.fadeoutScales = {static_cast<float>(3.000005085380829), static_cast<float>(3.0000030186916877)},
	.isSubtract = false,
	.isCyclic = false,
	.opacity = static_cast<float>(1),
	.fadeoutAngle = static_cast<float>(5.384189226464705),
	.fadeoutLength = static_cast<float>(0.16666661699612195),
	.fadeoutShift = float2(static_cast<float>(0.1037326455116272), static_cast<float>(-0.13045036792755127)),
	.index = 1
};

static PureShape shapeWatVertical90Horizontal270PureShape = {
	.locs = {float2(static_cast<float>(0.5943492650985718), static_cast<float>(0.3036460280418396)), float2(static_cast<float>(0.7086625099182129), static_cast<float>(0.42493200302124023))},
	.locsMiddles = {float2(static_cast<float>(0.6549922823905945), static_cast<float>(0.24648964405059814)), float2(static_cast<float>(0.6515058279037476), static_cast<float>(0.36428892612457275)), float2(static_cast<float>(0.7693055868148804), static_cast<float>(0.36777544021606445))},
	.fadeoutScales = {static_cast<float>(3.000007577297766), static_cast<float>(2.9999994300544324)},
	.isSubtract = false,
	.isCyclic = false,
	.opacity = static_cast<float>(1),
	.fadeoutAngle = static_cast<float>(3.956576697039343),
	.fadeoutLength = static_cast<float>(0.1666666281719958),
	.fadeoutShift = float2(static_cast<float>(-0.11431330442428589), static_cast<float>(-0.12128575146198273)),
	.index = 1
};

static PureShape shapeWatVertical90Horizontal360PureShape = {
	.locs = {float2(static_cast<float>(0.2866116166114807), static_cast<float>(0.2794628143310547)), float2(static_cast<float>(0.4044627845287323), static_cast<float>(0.1616116464138031))},
	.locsMiddles = {float2(static_cast<float>(0.22768613696098328), static_cast<float>(0.2205372303724289)), float2(static_cast<float>(0.3455371856689453), static_cast<float>(0.2205372303724289)), float2(static_cast<float>(0.3455372750759125), static_cast<float>(0.1026860922574997))},
	.fadeoutScales = {static_cast<float>(3.000001832844834), static_cast<float>(2.999999966472392)},
	.isSubtract = false,
	.isCyclic = false,
	.opacity = static_cast<float>(1),
	.fadeoutAngle = static_cast<float>(2.3561939673160284),
	.fadeoutLength = static_cast<float>(0.16666665611167716),
	.fadeoutShift = float2(static_cast<float>(-0.11785106360912323), static_cast<float>(0.11785118281841278)),
	.index = 1
};

static PureShape* shapeWatVertical90HorizontalPureShapes[shapeWatVertical90HorizontalSize] = { &shapeWatVertical90Horizontal0PureShape, &shapeWatVertical90Horizontal90PureShape, &shapeWatVertical90Horizontal180PureShape, &shapeWatVertical90Horizontal270PureShape, &shapeWatVertical90Horizontal360PureShape };

static PureShapeLayer<PureShape*> shapeWatVertical90HorizontalPureShapesWrapped = { .size = shapeWatVertical90HorizontalSize, .angles = shapeWatVertical90HorizontalLayers, .pureShapes = shapeWatVertical90HorizontalPureShapes };

static PureShapeLayer<PureShape*> shapeWatVerticalPureShapes[shapeWatVerticalSize] = { shapeWatVertical90HorizontalPureShapesWrapped };

static PureShapeLayer<PureShapeLayer<PureShape*>> shapeWatVerticalPureShapesWrapped = { .size = shapeWatVerticalSize, .angles = shapeWatVerticalLayers, .pureShapes = shapeWatVerticalPureShapes };

static PureShapeLayer<PureShapeLayer<PureShape*>> pureShapes[shapesSize] = { shapeNoseVerticalPureShapesWrapped, shapeWatVerticalPureShapesWrapped };

static shapeSizes shapeSizesPerShapeIndex[shapesSize] = { shapeNoseShapeSizes, shapeWatShapeSizes };

static const int vertsSize = 24;
static const int linesSize = 31;
static const int expressionsSize = 8;

