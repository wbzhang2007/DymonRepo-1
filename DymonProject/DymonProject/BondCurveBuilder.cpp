//created by Wang Jianwei on 1 Dec 2012
#include "BondCurveBuilder.h"
#include <iostream>
#include "BondCurve.h"
#include "BuilderCashFlowLeg.h"
#include "cashflow.h"
#include "cashflowLeg.h"
#include "EnumHelper.h"
#include "dateUtil.h"
#include "RecordHelper.h"
#include "Constants.h"

using namespace utilities;
typedef AbstractBuilder super;
typedef tuple<date, double> point;

void BondCurveBuilder::init(Configuration* cfg){
	super::init(cfg);
	
	_market = Market(EnumHelper::getCcyEnum("USD"));
	_curveStartDate = dateUtil::dayRollAdjust(dateUtil::getToday(),enums::Following,_market.getMarketEnum());
	_couponFreqency = std::stoi(cfg->getProperty("swap.usd.bond.couponfreq",false,"4"));
	_timeLineBuildDirection = std::stoi(cfg->getProperty("timeline.usd.builddirection",false,"1"));
	_rollAccuralDates =  cfg->getProperty("timeline.usd.rollaccuraldates",false,"0")=="0"?false:true;
	_interpolAlgo = EnumHelper::getInterpolAlgo(cfg->getProperty("BondCurve.usd.interpol",false,"CUBIC"));
	_numericalAlgo = EnumHelper::getNumericalAlgo(cfg->getProperty("BondCurve.usd.numerical",false,"BISECTION"));
	_bizDaysAfterSpot = _market.getBusinessDaysAfterSpot();
	_bizDaysAfterSpotDF = NaN;
}

BondCurve* BondCurveBuilder::build(Configuration* cfg){
	if (cfg!=NULL) init(cfg);
	BondCurve* bc = new BondCurve();
	return bc;
}
