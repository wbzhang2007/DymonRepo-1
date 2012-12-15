//created by Wang Jianwei on 1 Dec 2012

#include "YieldCurveBuilder.h"
#include <iostream>
#include "YieldCurve.h"

using namespace utilities;
typedef AbstractBuilder super;

void YieldCurveBuilder::init(Configuration* cfg){
	super::init(cfg);
}

YieldCurve* YieldCurveBuilder::buildCurve(){



	return new YieldCurve();
}