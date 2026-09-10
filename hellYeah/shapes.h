#pragma once
#include "float2.h"
#include "pureShape.h"
#include <string>
using namespace std;

static const int shapesSize = 1;

static const string shapesNames[shapesSize] = { "wat" };

static const int shapeWatVerticalSize = 1;

static const float shapeWatVerticalLayers[shapeWatVerticalSize] = { static_cast<float>(0.5) };

static shapeSizes shapeWatShapeSizes = { .verts = 12, .lines = 15, .expressions = 4, .vertsPrev = 0, .linesPrev = 0, .expressionsPrev = 0 };
static const int shapeWatVertical90HorizontalSize = 2;

static const float shapeWatVertical90HorizontalLayers[shapeWatVertical90HorizontalSize] = { static_cast<float>(0.0), static_cast<float>(1.0) };

static PureShape shapeWatVertical90Horizontal0PureShape = {
        .locs = {float2(static_cast<float>(0.2866116166114807), static_cast<float>(0.2794628143310547)), float2(static_cast<float>(0.4044627845287323), static_cast<float>(0.1616116464138031))},
        .locsMiddles = {float2(static_cast<float>(0.22768613696098328), static_cast<float>(0.2205372303724289)), float2(static_cast<float>(0.3455371856689453), static_cast<float>(0.2205372303724289)), float2(static_cast<float>(0.3455372750759125), static_cast<float>(0.1026860922574997))},
        .fadeoutScales = {static_cast<float>(3.000001832844834), static_cast<float>(2.999999966472392)},
        .isSubtract = false,
        .isCyclic = false,
        .doIgnore = false,
        .opacity = static_cast<float>(1.0),
        .fadeoutAngle = static_cast<float>(2.3561939673160284),
        .fadeoutLength = static_cast<float>(0.16666665611167716),
        .index = 0
};

static PureShape shapeWatVertical90Horizontal360PureShape = {
        .locs = {float2(static_cast<float>(0.4044628143310547), static_cast<float>(0.8383883237838745)), float2(static_cast<float>(0.2866116464138031), static_cast<float>(0.7205371856689453))},
        .locsMiddles = {float2(static_cast<float>(0.3455371558666229), static_cast<float>(0.8973139524459839)), float2(static_cast<float>(0.3455372750759125), static_cast<float>(0.7794628143310547)), float2(static_cast<float>(0.22768601775169373), static_cast<float>(0.7794628143310547))},
        .fadeoutScales = {static_cast<float>(2.9999995194375813), static_cast<float>(3.0000005252647552)},
        .isSubtract = false,
        .isCyclic = false,
        .doIgnore = false,
        .opacity = static_cast<float>(1.0),
        .fadeoutAngle = static_cast<float>(0.78539809621802),
        .fadeoutLength = static_cast<float>(0.16666667846341887),
        .index = 0
};

static PureShape* shapeWatVertical90HorizontalPureShapes[shapeWatVertical90HorizontalSize] = { &shapeWatVertical90Horizontal0PureShape, &shapeWatVertical90Horizontal360PureShape };

static PureShapeLayer<PureShape*> shapeWatVertical90HorizontalPureShapesWrapped = { .size = shapeWatVertical90HorizontalSize, .angles = shapeWatVertical90HorizontalLayers, .pureShapes = shapeWatVertical90HorizontalPureShapes };

static PureShapeLayer<PureShape*> shapeWatVerticalPureShapes[shapeWatVerticalSize] = { shapeWatVertical90HorizontalPureShapesWrapped };

static PureShapeLayer<PureShapeLayer<PureShape*>> shapeWatVerticalPureShapesWrapped = { .size = shapeWatVerticalSize, .angles = shapeWatVerticalLayers, .pureShapes = shapeWatVerticalPureShapes };

static PureShapeLayer<PureShapeLayer<PureShape*>> pureShapes[shapesSize] = { shapeWatVerticalPureShapesWrapped };

static shapeSizes shapeSizesPerShapeIndex[shapesSize] = { shapeWatShapeSizes };

static const int vertsSize = 12;
static const int linesSize = 15;
static const int expressionsSize = 4;