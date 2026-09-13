#pragma once
#include "float2.h"
#include "pureShape.h"
#include <string>
using namespace std;

static const int shapesSize = 3;

static const string shapesNames[shapesSize] = { "hh", "ww", "tt" };

static const int shapeHhVerticalSize = 1;

static const float shapeHhVerticalLayers[shapeHhVerticalSize] = { static_cast<float>(0.0) };

static shapeSizes shapeHhShapeSizes = { .verts = 39, .lines = 52, .expressions = 13, .vertsPrev = 0, .linesPrev = 0, .expressionsPrev = 0 };
static const int shapeHhVertical0HorizontalSize = 1;

static const float shapeHhVertical0HorizontalLayers[shapeHhVertical0HorizontalSize] = { static_cast<float>(0.0) };

static PureShape shapeHhVertical0Horizontal0PureShape = {
	.locs = {float2(static_cast<float>(0.22133658826351166), static_cast<float>(0.7327658534049988)), float2(static_cast<float>(0.5081959962844849), static_cast<float>(0.6139241456985474)), float2(static_cast<float>(0.5983518362045288), static_cast<float>(0.8789275884628296)), float2(static_cast<float>(0.6598216891288757), static_cast<float>(0.8201896548271179)), float2(static_cast<float>(0.627037763595581), static_cast<float>(0.7341318130493164)), float2(static_cast<float>(0.786859393119812), static_cast<float>(0.691785991191864)), float2(static_cast<float>(0.6967036128044128), static_cast<float>(0.5852381587028503)), float2(static_cast<float>(0.9125311374664307), static_cast<float>(0.5251343250274658)), float2(static_cast<float>(0.7882254123687744), static_cast<float>(0.34482264518737793)), float2(static_cast<float>(0.6202077865600586), static_cast<float>(0.44590646028518677)), float2(static_cast<float>(0.44672608375549316), static_cast<float>(0.235542893409729)), float2(static_cast<float>(0.23499654233455658), static_cast<float>(0.39399856328964233)), float2(static_cast<float>(0.2978324294090271), static_cast<float>(0.5087423324584961))},
	.locsMiddles = {float2(static_cast<float>(0.3696408271789551), static_cast<float>(0.6713255643844604)), float2(static_cast<float>(0.5857576131820679), static_cast<float>(0.8419082164764404)), float2(static_cast<float>(0.6299536824226379), static_cast<float>(0.848730206489563)), float2(static_cast<float>(0.6492047905921936), static_cast<float>(0.7923202514648438)), float2(static_cast<float>(0.7101274132728577), static_cast<float>(0.7121166586875916)), float2(static_cast<float>(0.7418614625930786), static_cast<float>(0.6386065483093262)), float2(static_cast<float>(0.8584328293800354), static_cast<float>(0.5401996374130249)), float2(static_cast<float>(0.8840774893760681), static_cast<float>(0.48386090993881226)), float2(static_cast<float>(0.7373204827308655), static_cast<float>(0.3754483759403229)), float2(static_cast<float>(0.5341847538948059), static_cast<float>(0.3415951132774353)), float2(static_cast<float>(0.3355352580547333), static_cast<float>(0.31875666975975037)), float2(static_cast<float>(0.2661963999271393), static_cast<float>(0.45097219944000244)), float2(static_cast<float>(0.2424815595149994), static_cast<float>(0.6708412766456604))},
	.fadeoutScales = {static_cast<float>(0.706131021283703), static_cast<float>(2.348224599372142), static_cast<float>(1.7002699972640454), static_cast<float>(0.3842053744037972), static_cast<float>(1.754166645930767), static_cast<float>(0.6162168176907957), static_cast<float>(1.80127334218611), static_cast<float>(1.3629267744210298), static_cast<float>(0.4381320945753514), static_cast<float>(1.6506864338364338), static_cast<float>(1.743777899602491), static_cast<float>(1.1370314881582024), static_cast<float>(2.1908149768000147)},
	.isSubtract = false,
	.isCyclic = true,
	.opacity = static_cast<float>(1),
	.fadeoutAngle = static_cast<float>(1.0322852139662613),
	.fadeoutLength = static_cast<float>(0.06818067831812442),
	.fadeoutShift = float2(static_cast<float>(0.03496703505516052), static_cast<float>(0.05853128433227539)),
	.index = 0
};

static PureShape* shapeHhVertical0HorizontalPureShapes[shapeHhVertical0HorizontalSize] = { &shapeHhVertical0Horizontal0PureShape };

static PureShapeLayer<PureShape*> shapeHhVertical0HorizontalPureShapesWrapped = { .size = shapeHhVertical0HorizontalSize, .angles = shapeHhVertical0HorizontalLayers, .pureShapes = shapeHhVertical0HorizontalPureShapes };

static PureShapeLayer<PureShape*> shapeHhVerticalPureShapes[shapeHhVerticalSize] = { shapeHhVertical0HorizontalPureShapesWrapped };

static PureShapeLayer<PureShapeLayer<PureShape*>> shapeHhVerticalPureShapesWrapped = { .size = shapeHhVerticalSize, .angles = shapeHhVerticalLayers, .pureShapes = shapeHhVerticalPureShapes };

static const int shapeWwVerticalSize = 1;

static const float shapeWwVerticalLayers[shapeWwVerticalSize] = { static_cast<float>(0.0) };

static shapeSizes shapeWwShapeSizes = { .verts = 39, .lines = 52, .expressions = 13, .vertsPrev = 39, .linesPrev = 52, .expressionsPrev = 13 };
static const int shapeWwVertical0HorizontalSize = 1;

static const float shapeWwVertical0HorizontalLayers[shapeWwVertical0HorizontalSize] = { static_cast<float>(0.0) };

static PureShape shapeWwVertical0Horizontal0PureShape = {
	.locs = {float2(static_cast<float>(-0.03690004348754883), static_cast<float>(0.5067879557609558)), float2(static_cast<float>(0.1459590643644333), static_cast<float>(0.4310320317745209)), float2(static_cast<float>(0.20342902839183807), static_cast<float>(0.5999590158462524)), float2(static_cast<float>(0.2426130771636963), static_cast<float>(0.5625163912773132)), float2(static_cast<float>(0.22171489894390106), static_cast<float>(0.5076587200164795)), float2(static_cast<float>(0.3235935568809509), static_cast<float>(0.4806651771068573)), float2(static_cast<float>(0.26612353324890137), static_cast<float>(0.4127461314201355)), float2(static_cast<float>(0.4037031829357147), static_cast<float>(0.3744328022003174)), float2(static_cast<float>(0.32446426153182983), static_cast<float>(0.2594928443431854)), float2(static_cast<float>(0.21736109256744385), static_cast<float>(0.3239288926124573)), float2(static_cast<float>(0.10677497088909149), static_cast<float>(0.18983227014541626)), float2(static_cast<float>(-0.028192441910505295), static_cast<float>(0.29084011912345886)), float2(static_cast<float>(0.011862397193908691), static_cast<float>(0.36398372054100037))},
	.locsMiddles = {float2(static_cast<float>(0.05763678997755051), static_cast<float>(0.46762269735336304)), float2(static_cast<float>(0.19540080428123474), static_cast<float>(0.5763609409332275)), float2(static_cast<float>(0.2235736846923828), static_cast<float>(0.5807096362113953)), float2(static_cast<float>(0.23584531247615814), static_cast<float>(0.544750988483429)), float2(static_cast<float>(0.27468055486679077), static_cast<float>(0.49362504482269287)), float2(static_cast<float>(0.2949094772338867), static_cast<float>(0.44676586985588074)), float2(static_cast<float>(0.3692181706428528), static_cast<float>(0.38403621315956116)), float2(static_cast<float>(0.3855653703212738), static_cast<float>(0.3481230139732361)), float2(static_cast<float>(0.29201486706733704), static_cast<float>(0.2790152430534363)), float2(static_cast<float>(0.16252557933330536), static_cast<float>(0.2574353814125061)), float2(static_cast<float>(0.0358961820602417), static_cast<float>(0.2428770214319229)), float2(static_cast<float>(-0.008304029703140259), static_cast<float>(0.3271580934524536)), float2(static_cast<float>(-0.023421108722686768), static_cast<float>(0.4673139452934265))},
	.fadeoutScales = {static_cast<float>(0.7061309559766494), static_cast<float>(2.348221635074309), static_cast<float>(1.7002681364852845), static_cast<float>(0.38420601878937477), static_cast<float>(1.7541677283945964), static_cast<float>(0.6162163231004468), static_cast<float>(1.8012732488113135), static_cast<float>(1.3629250069440222), static_cast<float>(0.4381325591427306), static_cast<float>(1.6506879805628196), static_cast<float>(1.743775024531419), static_cast<float>(1.1370322127662635), static_cast<float>(2.1908159546096404)},
	.isSubtract = true,
	.isCyclic = true,
	.opacity = static_cast<float>(1),
	.fadeoutAngle = static_cast<float>(1.0322850751042776),
	.fadeoutLength = static_cast<float>(0.04346192860064699),
	.fadeoutShift = float2(static_cast<float>(0.02228982001543045), static_cast<float>(0.037310898303985596)),
	.index = 1
};

static PureShape* shapeWwVertical0HorizontalPureShapes[shapeWwVertical0HorizontalSize] = { &shapeWwVertical0Horizontal0PureShape };

static PureShapeLayer<PureShape*> shapeWwVertical0HorizontalPureShapesWrapped = { .size = shapeWwVertical0HorizontalSize, .angles = shapeWwVertical0HorizontalLayers, .pureShapes = shapeWwVertical0HorizontalPureShapes };

static PureShapeLayer<PureShape*> shapeWwVerticalPureShapes[shapeWwVerticalSize] = { shapeWwVertical0HorizontalPureShapesWrapped };

static PureShapeLayer<PureShapeLayer<PureShape*>> shapeWwVerticalPureShapesWrapped = { .size = shapeWwVerticalSize, .angles = shapeWwVerticalLayers, .pureShapes = shapeWwVerticalPureShapes };

static const int shapeTtVerticalSize = 1;

static const float shapeTtVerticalLayers[shapeTtVerticalSize] = { static_cast<float>(0.0) };

static shapeSizes shapeTtShapeSizes = { .verts = 39, .lines = 52, .expressions = 13, .vertsPrev = 78, .linesPrev = 104, .expressionsPrev = 26 };
static const int shapeTtVertical0HorizontalSize = 1;

static const float shapeTtVertical0HorizontalLayers[shapeTtVertical0HorizontalSize] = { static_cast<float>(0.0) };

static PureShape shapeTtVertical0Horizontal0PureShape = {
	.locs = {float2(static_cast<float>(0.4472421109676361), static_cast<float>(0.5952136516571045)), float2(static_cast<float>(0.5615696907043457), static_cast<float>(0.5478493571281433)), float2(static_cast<float>(0.5975011587142944), static_cast<float>(0.6534662246704102)), float2(static_cast<float>(0.6219999194145203), static_cast<float>(0.6300563216209412)), float2(static_cast<float>(0.6089339256286621), static_cast<float>(0.5957580804824829)), float2(static_cast<float>(0.6726306676864624), static_cast<float>(0.5788811445236206)), float2(static_cast<float>(0.6366991996765137), static_cast<float>(0.5364166498184204)), float2(static_cast<float>(0.7227169871330261), static_cast<float>(0.5124622583389282)), float2(static_cast<float>(0.6731750965118408), static_cast<float>(0.440599262714386)), float2(static_cast<float>(0.6062118411064148), static_cast<float>(0.4808860719203949)), float2(static_cast<float>(0.5370709300041199), static_cast<float>(0.39704591035842896)), float2(static_cast<float>(0.45268628001213074), static_cast<float>(0.4601982533931732)), float2(static_cast<float>(0.4777294993400574), static_cast<float>(0.5059292316436768))},
	.locsMiddles = {float2(static_cast<float>(0.5063486099243164), static_cast<float>(0.5707266330718994)), float2(static_cast<float>(0.5924817323684692), static_cast<float>(0.6387121677398682)), float2(static_cast<float>(0.6100960969924927), static_cast<float>(0.6414310932159424)), float2(static_cast<float>(0.6177685856819153), static_cast<float>(0.6189489960670471)), float2(static_cast<float>(0.642049252986908), static_cast<float>(0.5869839191436768)), float2(static_cast<float>(0.6546967625617981), static_cast<float>(0.5576865077018738)), float2(static_cast<float>(0.7011561989784241), static_cast<float>(0.5184665322303772)), float2(static_cast<float>(0.7113768458366394), static_cast<float>(0.4960128366947174)), float2(static_cast<float>(0.6528870463371277), static_cast<float>(0.4528050720691681)), float2(static_cast<float>(0.5719274878501892), static_cast<float>(0.4393129050731659)), float2(static_cast<float>(0.4927558898925781), static_cast<float>(0.4302107095718384)), float2(static_cast<float>(0.46512097120285034), static_cast<float>(0.4829050302505493)), float2(static_cast<float>(0.45566943287849426), static_cast<float>(0.5705336332321167))},
	.fadeoutScales = {static_cast<float>(0.7061313039871239), static_cast<float>(2.3482099814897963), static_cast<float>(1.7002762718143087), static_cast<float>(0.38420291391017913), static_cast<float>(1.7541673100603463), static_cast<float>(0.6162173500516949), static_cast<float>(1.8012758020670647), static_cast<float>(1.3629260112356592), static_cast<float>(0.43813259229755636), static_cast<float>(1.6506867698587675), static_cast<float>(1.7437786005375815), static_cast<float>(1.1370316511205785), static_cast<float>(2.1908179187378787)},
	.isSubtract = true,
	.isCyclic = true,
	.opacity = static_cast<float>(1),
	.fadeoutAngle = static_cast<float>(1.0322825755865992),
	.fadeoutLength = static_cast<float>(0.02717338863092248),
	.fadeoutShift = float2(static_cast<float>(0.013936161994934082), static_cast<float>(0.02332758903503418)),
	.index = 2
};

static PureShape* shapeTtVertical0HorizontalPureShapes[shapeTtVertical0HorizontalSize] = { &shapeTtVertical0Horizontal0PureShape };

static PureShapeLayer<PureShape*> shapeTtVertical0HorizontalPureShapesWrapped = { .size = shapeTtVertical0HorizontalSize, .angles = shapeTtVertical0HorizontalLayers, .pureShapes = shapeTtVertical0HorizontalPureShapes };

static PureShapeLayer<PureShape*> shapeTtVerticalPureShapes[shapeTtVerticalSize] = { shapeTtVertical0HorizontalPureShapesWrapped };

static PureShapeLayer<PureShapeLayer<PureShape*>> shapeTtVerticalPureShapesWrapped = { .size = shapeTtVerticalSize, .angles = shapeTtVerticalLayers, .pureShapes = shapeTtVerticalPureShapes };

static PureShapeLayer<PureShapeLayer<PureShape*>> pureShapes[shapesSize] = { shapeHhVerticalPureShapesWrapped, shapeWwVerticalPureShapesWrapped, shapeTtVerticalPureShapesWrapped };

static shapeSizes shapeSizesPerShapeIndex[shapesSize] = { shapeHhShapeSizes, shapeWwShapeSizes, shapeTtShapeSizes };

static const int vertsSize = 117;
static const int linesSize = 156;
static const int expressionsSize = 39;

