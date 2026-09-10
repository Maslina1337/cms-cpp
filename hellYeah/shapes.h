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
        .doIgnore = false,
        .opacity = static_cast<float>(1.0),
        .fadeoutAngle = static_cast<float>(1.5707963267948966),
        .fadeoutLength = static_cast<float>(0.16666665611167716),
        .index = 0
};

static PureShape shapeNoseVertical0Horizontal360PureShape = {
        .locs = {float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.6666666865348816)), float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.6666666269302368))},
        .locsMiddles = {float2(static_cast<float>(0.25), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.75)), float2(static_cast<float>(0.25), static_cast<float>(0.6666666269302368)), float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.75))},
        .fadeoutScales = {static_cast<float>(2.999999670311981), static_cast<float>(2.999998418614765), static_cast<float>(2.9999998323620005), static_cast<float>(2.999998580664642)},
        .isSubtract = false,
        .isCyclic = true,
        .doIgnore = false,
        .opacity = static_cast<float>(1.0),
        .fadeoutAngle = static_cast<float>(1.5707963267948966),
        .fadeoutLength = static_cast<float>(0.1666666281719958),
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
        .doIgnore = false,
        .opacity = static_cast<float>(1.0),
        .fadeoutAngle = static_cast<float>(1.5707963267948966),
        .fadeoutLength = static_cast<float>(0.16666665611167716),
        .index = 0
};

static PureShape shapeNoseVertical180Horizontal360PureShape = {
        .locs = {float2(static_cast<float>(0.6666666269302368), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.6666666865348816)), float2(static_cast<float>(0.6666666865348816), static_cast<float>(0.6666666269302368))},
        .locsMiddles = {float2(static_cast<float>(0.75), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.75)), float2(static_cast<float>(0.75), static_cast<float>(0.6666666269302368)), float2(static_cast<float>(0.6666666269302368), static_cast<float>(0.75))},
        .fadeoutScales = {static_cast<float>(2.9999985806654035), static_cast<float>(2.9999985806654035), static_cast<float>(2.9999985806654035), static_cast<float>(2.9999985806654035)},
        .isSubtract = false,
        .isCyclic = true,
        .doIgnore = false,
        .opacity = static_cast<float>(1.0),
        .fadeoutAngle = static_cast<float>(1.5707963267948966),
        .fadeoutLength = static_cast<float>(0.1666666281719958),
        .index = 0
};

static PureShape* shapeNoseVertical180HorizontalPureShapes[shapeNoseVertical180HorizontalSize] = { &shapeNoseVertical180Horizontal0PureShape, &shapeNoseVertical180Horizontal360PureShape };

static PureShapeLayer<PureShape*> shapeNoseVertical180HorizontalPureShapesWrapped = { .size = shapeNoseVertical180HorizontalSize, .angles = shapeNoseVertical180HorizontalLayers, .pureShapes = shapeNoseVertical180HorizontalPureShapes };

static PureShapeLayer<PureShape*> shapeNoseVerticalPureShapes[shapeNoseVerticalSize] = { shapeNoseVertical0HorizontalPureShapesWrapped, shapeNoseVertical180HorizontalPureShapesWrapped };

static PureShapeLayer<PureShapeLayer<PureShape*>> shapeNoseVerticalPureShapesWrapped = { .size = shapeNoseVerticalSize, .angles = shapeNoseVerticalLayers, .pureShapes = shapeNoseVerticalPureShapes };

static const int shapeWatVerticalSize = 1;

static const float shapeWatVerticalLayers[shapeWatVerticalSize] = { static_cast<float>(0.0) };

static shapeSizes shapeWatShapeSizes = { .verts = 12, .lines = 15, .expressions = 4, .vertsPrev = 12, .linesPrev = 16, .expressionsPrev = 4 };
static const int shapeWatVertical0HorizontalSize = 2;

static const float shapeWatVertical0HorizontalLayers[shapeWatVertical0HorizontalSize] = { static_cast<float>(0.0), static_cast<float>(1.0) };

static PureShape shapeWatVertical0Horizontal0PureShape = {
        .locs = {float2(static_cast<float>(0.2866116166114807), static_cast<float>(0.2794628143310547)), float2(static_cast<float>(0.4044627845287323), static_cast<float>(0.1616116464138031))},
        .locsMiddles = {float2(static_cast<float>(0.22768613696098328), static_cast<float>(0.2205372303724289)), float2(static_cast<float>(0.3455371856689453), static_cast<float>(0.2205372303724289)), float2(static_cast<float>(0.3455372750759125), static_cast<float>(0.1026860922574997))},
        .fadeoutScales = {static_cast<float>(3.000001832844834), static_cast<float>(2.999999966472392)},
        .isSubtract = false,
        .isCyclic = false,
        .doIgnore = false,
        .opacity = static_cast<float>(1.0),
        .fadeoutAngle = static_cast<float>(2.3561939673160284),
        .fadeoutLength = static_cast<float>(0.16666665611167716),
        .index = 1
};

static PureShape shapeWatVertical0Horizontal360PureShape = {
        .locs = {float2(static_cast<float>(0.4044628143310547), static_cast<float>(0.8383883237838745)), float2(static_cast<float>(0.2866116464138031), static_cast<float>(0.7205371856689453))},
        .locsMiddles = {float2(static_cast<float>(0.3455371558666229), static_cast<float>(0.8973139524459839)), float2(static_cast<float>(0.3455372750759125), static_cast<float>(0.7794628143310547)), float2(static_cast<float>(0.22768601775169373), static_cast<float>(0.7794628143310547))},
        .fadeoutScales = {static_cast<float>(2.9999995194375813), static_cast<float>(3.0000005252647552)},
        .isSubtract = false,
        .isCyclic = false,
        .doIgnore = false,
        .opacity = static_cast<float>(1.0),
        .fadeoutAngle = static_cast<float>(0.78539809621802),
        .fadeoutLength = static_cast<float>(0.16666667846341887),
        .index = 1
};

static PureShape* shapeWatVertical0HorizontalPureShapes[shapeWatVertical0HorizontalSize] = { &shapeWatVertical0Horizontal0PureShape, &shapeWatVertical0Horizontal360PureShape };

static PureShapeLayer<PureShape*> shapeWatVertical0HorizontalPureShapesWrapped = { .size = shapeWatVertical0HorizontalSize, .angles = shapeWatVertical0HorizontalLayers, .pureShapes = shapeWatVertical0HorizontalPureShapes };

static PureShapeLayer<PureShape*> shapeWatVerticalPureShapes[shapeWatVerticalSize] = { shapeWatVertical0HorizontalPureShapesWrapped };

static PureShapeLayer<PureShapeLayer<PureShape*>> shapeWatVerticalPureShapesWrapped = { .size = shapeWatVerticalSize, .angles = shapeWatVerticalLayers, .pureShapes = shapeWatVerticalPureShapes };

static PureShapeLayer<PureShapeLayer<PureShape*>> pureShapes[shapesSize] = { shapeNoseVerticalPureShapesWrapped, shapeWatVerticalPureShapesWrapped };

static shapeSizes shapeSizesPerShapeIndex[shapesSize] = { shapeNoseShapeSizes, shapeWatShapeSizes };

static const int vertsSize = 24;
static const int linesSize = 31;
static const int expressionsSize = 8;