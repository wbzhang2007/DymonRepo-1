#include "SwaptionVolSurfaceBuilder.h"
#include "EnumHelper.h"

using namespace utilities;
typedef AbstractBuilder super;

void SwaptionVolSurfaceBuilder::init(Configuration* cfg){
	super::init(cfg);
	
	_market = currency(EnumHelper::getCcyEnum("USD"));
	_interpolAlgo = EnumHelper::getInterpolAlgo(cfg->getProperty("swaptionvolsurface.usd.interpol",false,"LINEAR"));
}

SwaptionVolSurface* SwaptionVolSurfaceBuilder::build(){
	SwaptionVolSurface* svs = new SwaptionVolSurface();
	return svs;
}