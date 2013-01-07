#include "SwaptionVolCubeBuilder.h"
#include "EnumHelper.h"
#include "RecordHelper.h"

using namespace utilities;
typedef AbstractBuilder super;

void SwaptionVolCubeBuilder::init(Configuration* cfg){
	super::init(cfg);
	
	_market = Market(EnumHelper::getCcyEnum("USD"));
	_interpolAlgo = EnumHelper::getInterpolAlgo(cfg->getProperty("swaptionVolCube.usd.interpol",false,"LINEAR"));
}

SwaptionVolCube* SwaptionVolCubeBuilder::build(){
	SwaptionVolCube* svc = new SwaptionVolCube();
	RecordHelper::SwaptionVolMap volCubeMap = RecordHelper::getInstance()->getSwaptionVolMap();
	RecordHelper::SwaptionVolMap::iterator cubeIt;
	for (cubeIt=volCubeMap.begin();cubeIt!=volCubeMap.end();cubeIt++){
		int strikeDiffATM = (*cubeIt).first;
		RecordHelper::SwaptionSurfaceMap volSurfaceMap = (*cubeIt).second;
		RecordHelper::SwaptionSurfaceMap::iterator surfaceIt;
		for (surfaceIt=volSurfaceMap.begin();surfaceIt!=volSurfaceMap.end();cubeIt++){
			tuple<int, int> tenorExpiry = (*surfaceIt).first;
			double vol = (*surfaceIt).second;
		}
	}
	
	return svc;
}