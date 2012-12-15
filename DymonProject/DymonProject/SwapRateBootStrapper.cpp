//created by Wang Jianwei on 1 Dec 2012

#include "SwapRateBootStrapper.h"
#include <iostream>
#include "YieldCurve.h"
#include "InterpolatorFactory.h"
#include "AbstractInterpolator.h"
#include "NumericalFactory.h"
#include "dateUtil.h"
#include <cmath>

using namespace utilities;

AbstractInterpolator* SwapRateBootStrapper::bootStrap(){
	
	targetFuncT numericalFunc;
		
	_startIndex = findElementIndex(std::get<0>(_startPoint));
	_endIndex = findElementIndex(_endDate);

	AbstractNumerical* an = NumericalFactory::getInstance()->getNumerical(&numericalFunc,_numericAlgo);
	double swapPointValue = an->findRoot(0,0,0,0);

	AbstractInterpolator* ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,swapPointValue) , _interpolAlgo);
	return ai;
}

double SwapRateBootStrapper::numericalFunc(double x){
	
	AbstractInterpolator* ai = InterpolatorFactory::getInstance()->getInterpolator(_startPoint, point(_endDate,x) , _interpolAlgo);

	double numerator = 1 - exp(-x);
	double denominator = 0;

	for( unsigned int i=0; i<=_startIndex; i++){
		denominator = denominator + dateUtil::getAccrualFactor(_timeLine[0],_timeLine[i],_dayCount)*(*_curve).getDiscountFactor(_timeLine[i]);
	}
	for( unsigned int i=_startIndex+1; i<=_endIndex; i++){
		denominator = denominator + dateUtil::getAccrualFactor(_timeLine[0],_timeLine[i],_dayCount)*std::get<1>((*ai).interpolate(_timeLine[i]));
	}

	return numerator/denominator - _swapRate;
}

unsigned int SwapRateBootStrapper::findElementIndex(date date0){
	for(unsigned int i = 0; i < _timeLine.size(); i++)
	{
		if ( _timeLine[i].getJudianDayNumber() == date0.getJudianDayNumber()){
			return i;
		}
	}
	throw "Date not found in time line: " + date0.getJudianDayNumber();
}