#include "float2.h"
#include "pureShape.h"
#include <string>
using namespace std;

const int shapesSize = 1;

const string shapesNames[shapesSize] = { "nose" };

const int shapeNoseVerticalSize = 2;

const float shapeNoseVerticalLayers[shapeNoseVerticalSize] = { 0.0, 1.0 };

const int shapeNoseVertical0HorizontalSize = 2;

const float shapeNoseVertical0HorizontalLayers[shapeNoseVertical0HorizontalSize] = { 0.0, 0.5 };

PureShape shapeNoseVertical0Horizontal0PureShape = {
        .locs = {float2(0.1666666716337204, 0.3333333432674408), float2(0.3333333432674408, 0.3333333432674408), float2(0.3333333432674408, 0.1666666716337204), float2(0.1666666716337204, 0.1666666716337204)},
        .locsMiddles = {float2(0.25, 0.3333333432674408), float2(0.3333333432674408, 0.25), float2(0.25, 0.1666666716337204), float2(0.1666666716337204, 0.25)},
        .fadeoutScales = {2.9999996870756642, 2.9999997597187757, 2.999999742954926, 2.9999997597187757},
        .isSubtract = false,
        .isCyclic = true,
        .doIgnore = false,
        .opacity = true,
        .fadeoutAngle = 1.5707963267948966,
        .fadeoutLength = 0.16666665611167716
};

PureShape shapeNoseVertical0Horizontal180PureShape = {
        .locs = {float2(0.1666666716337204, 0.8333333730697632), float2(0.3333333432674408, 0.8333333730697632), float2(0.3333333432674408, 0.6666666865348816), float2(0.1666666716337204, 0.6666666269302368)},
        .locsMiddles = {float2(0.25, 0.8333333730697632), float2(0.3333333432674408, 0.75), float2(0.25, 0.6666666269302368), float2(0.1666666716337204, 0.75)},
        .fadeoutScales = {2.999999670311981, 2.999998418614765, 2.9999998323620005, 2.999998580664642},
        .isSubtract = false,
        .isCyclic = true,
        .doIgnore = false,
        .opacity = true,
        .fadeoutAngle = 1.5707963267948966,
        .fadeoutLength = 0.1666666281719958
};

PureShape* shapeNoseVertical0HorizontalPureShapes[shapeNoseVertical0HorizontalSize] = { &shapeNoseVertical0Horizontal0PureShape, &shapeNoseVertical0Horizontal180PureShape };

PureShapeLayer<PureShape*> shapeNoseVertical0HorizontalPureShapesWrapped = { .size = shapeNoseVertical0HorizontalSize, .angles = shapeNoseVertical0HorizontalLayers, .pureShapes = shapeNoseVertical0HorizontalPureShapes };

const int shapeNoseVertical180HorizontalSize = 2;

const float shapeNoseVertical180HorizontalLayers[shapeNoseVertical180HorizontalSize] = { 0.0, 0.5 };

PureShape shapeNoseVertical180Horizontal0PureShape = {
        .locs = {float2(0.6666666269302368, 0.3333333432674408), float2(0.8333333730697632, 0.3333333432674408), float2(0.8333333730697632, 0.1666666716337204), float2(0.6666666865348816, 0.1666666716337204)},
        .locsMiddles = {float2(0.75, 0.3333333432674408), float2(0.8333333730697632, 0.25), float2(0.75, 0.1666666716337204), float2(0.6666666865348816, 0.25)},
        .fadeoutScales = {2.999999670311981, 3.00000081583813, 2.9999999050050676, 3.000000547617693},
        .isSubtract = false,
        .isCyclic = true,
        .doIgnore = false,
        .opacity = true,
        .fadeoutAngle = 1.5707963267948966,
        .fadeoutLength = 0.16666665611167716
};

PureShape shapeNoseVertical180Horizontal180PureShape = {
        .locs = {float2(0.6666666269302368, 0.8333333730697632), float2(0.8333333730697632, 0.8333333730697632), float2(0.8333333730697632, 0.6666666865348816), float2(0.6666666865348816, 0.6666666269302368)},
        .locsMiddles = {float2(0.75, 0.8333333730697632), float2(0.8333333730697632, 0.75), float2(0.75, 0.6666666269302368), float2(0.6666666269302368, 0.75)},
        .fadeoutScales = {2.9999985806654035, 2.9999985806654035, 2.9999985806654035, 2.9999985806654035},
        .isSubtract = false,
        .isCyclic = true,
        .doIgnore = false,
        .opacity = true,
        .fadeoutAngle = 1.5707963267948966,
        .fadeoutLength = 0.1666666281719958
};

PureShape* shapeNoseVertical180HorizontalPureShapes[shapeNoseVertical180HorizontalSize] = { &shapeNoseVertical180Horizontal0PureShape, &shapeNoseVertical180Horizontal180PureShape };

PureShapeLayer<PureShape*> shapeNoseVertical180HorizontalPureShapesWrapped = { .size = shapeNoseVertical180HorizontalSize, .angles = shapeNoseVertical180HorizontalLayers, .pureShapes = shapeNoseVertical180HorizontalPureShapes };

PureShapeLayer<PureShape*> shapeNoseVerticalPureShapes[shapeNoseVerticalSize] = { shapeNoseVertical0HorizontalPureShapesWrapped, shapeNoseVertical180HorizontalPureShapesWrapped };

PureShapeLayer<PureShapeLayer<PureShape*>> shapeNoseVerticalPureShapesWrapped = { .size = shapeNoseVerticalSize, .angles = shapeNoseVerticalLayers, .pureShapes = shapeNoseVerticalPureShapes };

PureShapeLayer<PureShapeLayer<PureShape*>> pureShapes[shapesSize] = { shapeNoseVerticalPureShapesWrapped };