#pragma once
#include "float2.h"
#include "pureShape.h"
#include <string>
using namespace std;

const int shapesSize = 1;

const string shapesNames[shapesSize] = { "nose" };

const int shapeNoseVerticalSize = 2;

const float shapeNoseVerticalLayers[shapeNoseVerticalSize] = { static_cast<float>(0.0), static_cast<float>(1.0) };

const int shapeNoseVertical0HorizontalSize = 2;

const float shapeNoseVertical0HorizontalLayers[shapeNoseVertical0HorizontalSize] = { static_cast<float>(0.0), static_cast<float>(0.5) };

PureShape shapeNoseVertical0Horizontal0PureShape = {
        .locs = {float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.3333333432674408)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.3333333432674408)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.1666666716337204)), float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.1666666716337204))},
        .locsMiddles = {float2(static_cast<float>(0.25), static_cast<float>(0.3333333432674408)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.25)), float2(static_cast<float>(0.25), static_cast<float>(0.1666666716337204)), float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.25))},
        .fadeoutScales = {static_cast<float>(2.9999996870756642), static_cast<float>(2.9999997597187757), static_cast<float>(2.999999742954926), static_cast<float>(2.9999997597187757)},
        .isSubtract = false,
        .isCyclic = true,
        .doIgnore = false,
        .opacity = static_cast<float>(1.0),
        .fadeoutAngle = static_cast<float>(1.5707963267948966),
        .fadeoutLength = static_cast<float>(0.16666665611167716)
};

PureShape shapeNoseVertical0Horizontal180PureShape = {
        .locs = {float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.6666666865348816)), float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.6666666269302368))},
        .locsMiddles = {float2(static_cast<float>(0.25), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.3333333432674408), static_cast<float>(0.75)), float2(static_cast<float>(0.25), static_cast<float>(0.6666666269302368)), float2(static_cast<float>(0.1666666716337204), static_cast<float>(0.75))},
        .fadeoutScales = {static_cast<float>(2.999999670311981), static_cast<float>(2.999998418614765), static_cast<float>(2.9999998323620005), static_cast<float>(2.999998580664642)},
        .isSubtract = false,
        .isCyclic = true,
        .doIgnore = false,
        .opacity = static_cast<float>(1.0),
        .fadeoutAngle = static_cast<float>(1.5707963267948966),
        .fadeoutLength = static_cast<float>(0.1666666281719958)
};

PureShape* shapeNoseVertical0HorizontalPureShapes[shapeNoseVertical0HorizontalSize] = { &shapeNoseVertical0Horizontal0PureShape, &shapeNoseVertical0Horizontal180PureShape };

PureShapeLayer<PureShape*> shapeNoseVertical0HorizontalPureShapesWrapped = { .size = shapeNoseVertical0HorizontalSize, .angles = shapeNoseVertical0HorizontalLayers, .pureShapes = shapeNoseVertical0HorizontalPureShapes };

const int shapeNoseVertical180HorizontalSize = 2;

const float shapeNoseVertical180HorizontalLayers[shapeNoseVertical180HorizontalSize] = { static_cast<float>(0.0), static_cast<float>(0.5) };

PureShape shapeNoseVertical180Horizontal0PureShape = {
        .locs = {float2(static_cast<float>(0.6666666269302368), static_cast<float>(0.3333333432674408)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.3333333432674408)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.1666666716337204)), float2(static_cast<float>(0.6666666865348816), static_cast<float>(0.1666666716337204))},
        .locsMiddles = {float2(static_cast<float>(0.75), static_cast<float>(0.3333333432674408)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.25)), float2(static_cast<float>(0.75), static_cast<float>(0.1666666716337204)), float2(static_cast<float>(0.6666666865348816), static_cast<float>(0.25))},
        .fadeoutScales = {static_cast<float>(2.999999670311981), static_cast<float>(3.00000081583813), static_cast<float>(2.9999999050050676), static_cast<float>(3.000000547617693)},
        .isSubtract = false,
        .isCyclic = true,
        .doIgnore = false,
        .opacity = static_cast<float>(1.0),
        .fadeoutAngle = static_cast<float>(1.5707963267948966),
        .fadeoutLength = static_cast<float>(0.16666665611167716)
};

PureShape shapeNoseVertical180Horizontal180PureShape = {
        .locs = {float2(static_cast<float>(0.6666666269302368), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.6666666865348816)), float2(static_cast<float>(0.6666666865348816), static_cast<float>(0.6666666269302368))},
        .locsMiddles = {float2(static_cast<float>(0.75), static_cast<float>(0.8333333730697632)), float2(static_cast<float>(0.8333333730697632), static_cast<float>(0.75)), float2(static_cast<float>(0.75), static_cast<float>(0.6666666269302368)), float2(static_cast<float>(0.6666666269302368), static_cast<float>(0.75))},
        .fadeoutScales = {static_cast<float>(2.9999985806654035), static_cast<float>(2.9999985806654035), static_cast<float>(2.9999985806654035), static_cast<float>(2.9999985806654035)},
        .isSubtract = false,
        .isCyclic = true,
        .doIgnore = false,
        .opacity = static_cast<float>(1.0),
        .fadeoutAngle = static_cast<float>(1.5707963267948966),
        .fadeoutLength = static_cast<float>(0.1666666281719958)
};

PureShape* shapeNoseVertical180HorizontalPureShapes[shapeNoseVertical180HorizontalSize] = { &shapeNoseVertical180Horizontal0PureShape, &shapeNoseVertical180Horizontal180PureShape };

PureShapeLayer<PureShape*> shapeNoseVertical180HorizontalPureShapesWrapped = { .size = shapeNoseVertical180HorizontalSize, .angles = shapeNoseVertical180HorizontalLayers, .pureShapes = shapeNoseVertical180HorizontalPureShapes };

PureShapeLayer<PureShape*> shapeNoseVerticalPureShapes[shapeNoseVerticalSize] = { shapeNoseVertical0HorizontalPureShapesWrapped, shapeNoseVertical180HorizontalPureShapesWrapped };

PureShapeLayer<PureShapeLayer<PureShape*>> shapeNoseVerticalPureShapesWrapped = { .size = shapeNoseVerticalSize, .angles = shapeNoseVerticalLayers, .pureShapes = shapeNoseVerticalPureShapes };

PureShapeLayer<PureShapeLayer<PureShape*>> pureShapes[shapesSize] = { shapeNoseVerticalPureShapesWrapped };