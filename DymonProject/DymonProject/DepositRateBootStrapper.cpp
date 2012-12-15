//created by Wang Jianwei on 1 Dec 2012

#include "DepositRateBootStrapper.h"
#include <iostream>
#include <cmath>
#include "YieldCurve.h"
#include "InterpolatorFactory.h"
#include "AbstractInterpolator.h"
#include "NumericalFactory.h"
#include "dateUtil.h"

using namespace utilities;

AbstractInterpolator* DepositRateBootStrapper::bootStrap(){
	
	double accrualFactor = dateUtil::getAccrualFactor(_timeLine[0],_endDate, _dayCount);
	double cashPointValue = log(1+accrualFactor*_depositRate);

	AbstractInterpolator* ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,cashPointValue) , _interpolAlgo);
	return ai;

}