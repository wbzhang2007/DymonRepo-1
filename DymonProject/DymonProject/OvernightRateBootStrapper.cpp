//created by Wang Jianwei on 1 Dec 2012

#include "OvernightRateBootStrapper.h"
#include <iostream>
#include <cmath>
#include "YieldCurve.h"
#include "InterpolatorFactory.h"
#include "AbstractInterpolator.h"
#include "NumericalFactory.h"
#include "AbstractBootStrapper.h"
#include "dateUtil.h"
#include "RecordHelper.h"

using namespace utilities;

typedef AbstractBootStrapper super;

void OvernightRateBootStrapper::init(Configuration* cfg){
	super::init(cfg);
}

AbstractInterpolator* OvernightRateBootStrapper::bootStrap(){
	AbstractInterpolator* ai;
	enums::DayCountEnum dayCountCashConvention = _market.getDayCountCashConvention();
	double accrualFactor = dateUtil::getAccrualFactor(_cashFlow.getAccuralStartDate(),_cashFlow.getAccuralEndDate(), dayCountCashConvention);
	double discountFactor = 1/(1+accrualFactor*_depositRate);
	ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,discountFactor) , _interpolAlgo);
	return ai;
}

double OvernightRateBootStrapper::numericalFunc(double x){
	return 0;
}