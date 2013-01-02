#include "SwaptionVolCubeBuilder.h"
#include "EnumHelper.h"

using namespace utilities;
typedef AbstractBuilder super;

void SwaptionVolCubeBuilder::init(Configuration* cfg){
	super::init(cfg);
	
	_market = currency(EnumHelper::getCcyEnum("USD"));
	_interpolAlgo = EnumHelper::getInterpolAlgo(cfg->getProperty("swaptionvolsurface.usd.interpol",false,"LINEAR"));
}

SwaptionVolCube* SwaptionVolCubeBuilder::build(){
	SwaptionVolCube* svc = new SwaptionVolCube();
	return svc;
}