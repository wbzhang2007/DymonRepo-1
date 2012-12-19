//created by Wang Jianwei on 1 Dec 2012

#include "DepositRateBootStrapper.h"
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

void DepositRateBootStrapper::init(Configuration* cfg){
	super::init(cfg);
}

AbstractInterpolator* DepositRateBootStrapper::bootStrap(){
	AbstractInterpolator* ai;
	enums::DayCountEnum dayCountCashConvention = _market.getDayCountCashConvention();
	double accrualFactor = dateUtil::getAccrualFactor(_cashFlow.getAccuralStartDate(),_cashFlow.getAccuralEndDate(), dayCountCashConvention);
	double cashPointValue = log(1+accrualFactor*_depositRate)/accrualFactor;
	ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,cashPointValue) , _interpolAlgo);
	return ai;
}

double DepositRateBootStrapper::numericalFunc(double x){
	return 0;
}